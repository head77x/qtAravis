#pragma once

#include <cstddef>
#include <cstdint>
#include <QString>
#include <QByteArray>
#include <QVariant>

enum class GentlInfoType {
    Unknown,
    String,
    StringList,
    Int16,
    UInt16,
    Int32,
    UInt32,
    Int64,
    UInt64,
    Float64,
    Pointer,
    Bool8,
    SizeT,
    Buffer,
    PtrDiff
};

class QtGentlBufferUtil {
public:
    static size_t sizeOf(GentlInfoType type, const void* data);
    static bool convertToBuffer(GentlInfoType type, void* dst, const void* src, size_t* size, GentlInfoType* resultType = nullptr);
};
