// QtArvRealtime.cpp - Ported from arvrealtime.c
#include "QtArvRealtime.h"
#include <QDebug>
#ifdef Q_OS_WIN
#include <windows.h>
#else
#include <sched.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>
#endif

namespace QtArvRealtime {

#ifdef Q_OS_WIN

    bool makeThreadRealtime(int priority) {
        SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
        if (!SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL)) {
            qWarning() << "SetThreadPriority failed:" << GetLastError();
            return false;
        }
        qInfo() << "Thread made realtime.";
        return true;
    }

    bool makeThreadHighPriority(int priority) {
        if (!SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST)) {
            qWarning() << "SetThreadPriority (HIGH) failed:" << GetLastError();
            return false;
        }
        qInfo() << "Thread made high-priority.";
        return true;
    }

#else

    static pid_t gettid() {
        return static_cast<pid_t>(syscall(SYS_gettid));
    }

    bool makeThreadRealtime(int priority) {
        struct sched_param param;
        param.sched_priority = priority;

        if (sched_setscheduler(gettid(), SCHED_RR | SCHED_RESET_ON_FORK, &param) < 0) {
            perror("sched_setscheduler failed");
            return false;
        }

        qInfo() << "Realtime priority set for thread" << gettid();
        return true;
    }

    bool makeThreadHighPriority(int niceLevel) {
        int ret = setpriority(PRIO_PROCESS, gettid(), niceLevel);
        if (ret < 0) {
            perror("setpriority failed");
            return false;
        }
        qInfo() << "Nice level set to" << niceLevel;
        return true;
    }

#endif

} // namespace QtArvRealtime
