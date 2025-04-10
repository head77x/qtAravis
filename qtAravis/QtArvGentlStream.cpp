// QtArvGentlStream.cpp - Implementation for GenTL stream wrapper
#include "QtArvGentlStream.h"
#include "QtArvGentlDevice.h"
#include "QtArvBuffer.h"
#include <QDebug>

// Hypothetical external GenTL C API
extern "C" {
    void* gentl_create_stream(void* device);
    void gentl_destroy_stream(void* stream);
    bool gentl_start_stream(void* stream);
    void gentl_stop_stream(void* stream);
    bool gentl_push_buffer(void* stream, void* buffer);
    void* gentl_pop_buffer(void* stream);
}

class StreamThread : public QThread {
public:
    StreamThread(QtArvGentlStream* stream) : m_stream(stream) {}
    void run() override { m_stream->streamLoop(); }
private:
    QtArvGentlStream* m_stream;
};

QtArvGentlStream::QtArvGentlStream(QtArvGentlDevice* device, QObject* parent)
    : QObject(parent), m_device(device), m_thread(new StreamThread(this)) {
}

QtArvGentlStream::~QtArvGentlStream() {
    stop();
    delete m_thread;
    qDeleteAll(m_buffers);
    m_buffers.clear();
}

bool QtArvGentlStream::start() {
    QMutexLocker locker(&m_mutex);
    if (m_running) return false;
    m_running = true;
    m_thread->start();
    return true;
}

void QtArvGentlStream::stop() {
    QMutexLocker locker(&m_mutex);
    if (!m_running) return;
    m_running = false;
    m_cond.wakeAll();
    m_thread->wait();
}

bool QtArvGentlStream::createBuffers(int count, size_t size) {
    QMutexLocker locker(&m_mutex);
    qDeleteAll(m_buffers);
    m_buffers.clear();

    for (int i = 0; i < count; ++i) {
        QtArvBuffer* buf = new QtArvBuffer(size);
        m_buffers.append(buf);
    }
    return true;
}

void QtArvGentlStream::streamLoop() {
    void* rawStream = gentl_create_stream(m_device);
    if (!rawStream) {
        qWarning() << "[QtArvGentlStream] Failed to create stream.";
        return;
    }

    for (auto* buf : m_buffers) {
        gentl_push_buffer(rawStream, buf->rawPointer());
    }

    if (!gentl_start_stream(rawStream)) {
        qWarning() << "[QtArvGentlStream] Failed to start stream.";
        gentl_destroy_stream(rawStream);
        return;
    }

    while (true) {
        {
            QMutexLocker locker(&m_mutex);
            if (!m_running) break;
        }

        void* raw = gentl_pop_buffer(rawStream);
        if (raw) {
            for (auto* buf : m_buffers) {
                if (buf->rawPointer() == raw) {
                    emit frameReady(buf);
                    gentl_push_buffer(rawStream, raw);
                    break;
                }
            }
        }
    }

    gentl_stop_stream(rawStream);
    gentl_destroy_stream(rawStream);
}
