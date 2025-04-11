#include "QtGentlBufferUtil.h"
#include <cstring>
#include <QDebug>

size_t QtGentlBufferUtil::sizeOf(GentlInfoType type, const void* data) {
    switch (type) {
    case GentlInfoType::Unknown: return 0;
    case GentlInfoType::String: return std::strlen(static_cast<const char*>(data)) + 1;
    case GentlInfoType::StringList: {
        const char* s = static_cast<const char*>(data);
        const char* start = s;
        while (s[0] != '\0') s += std::strlen(s) + 1;
        return s - start;
    }
    case GentlInfoType::Int16:
    case GentlInfoType::UInt16: return 2;
    case GentlInfoType::Int32:
    case GentlInfoType::UInt32: return 4;
    case GentlInfoType::Int64:
    case GentlInfoType::UInt64:
    case GentlInfoType::Float64: return 8;
    case GentlInfoType::Pointer: return sizeof(void*);
    case GentlInfoType::Bool8: return 1;
    case GentlInfoType::SizeT: return sizeof(size_t);
    case GentlInfoType::Buffer: return 0;
    case GentlInfoType::PtrDiff: return sizeof(ptrdiff_t);
    default: return 0;
    }
}

bool QtGentlBufferUtil::convertToBuffer(GentlInfoType type, void* dst, const void* src, size_t* size, GentlInfoType* resultType) {
    if (!size) return false;
    if (resultType) *resultType = type;

    size_t srcSize = sizeOf(type, src);
    if (!dst) {
        *size = srcSize;
        return true;
    }

    if (srcSize > *size) return false;
    *size = srcSize;

    switch (type) {
    case GentlInfoType::Unknown:
        qWarning() << "[BufferUtil] Unsupported type: Unknown";
        return false;

    case GentlInfoType::String:
        std::strcpy(static_cast<char*>(dst), static_cast<const char*>(src));
        break;

    case GentlInfoType::Int16:
        *static_cast<int16_t*>(dst) = *static_cast<const int16_t*>(src);
        break;
    case GentlInfoType::UInt16:
        *static_cast<uint16_t*>(dst) = *static_cast<const uint16_t*>(src);
        break;
    case GentlInfoType::Int32:
        *static_cast<int32_t*>(dst) = *static_cast<const int32_t*>(src);
        break;
    case GentlInfoType::UInt32:
        *static_cast<uint32_t*>(dst) = *static_cast<const uint32_t*>(src);
        break;
    case GentlInfoType::Int64:
        *static_cast<int64_t*>(dst) = *static_cast<const int64_t*>(src);
        break;
    case GentlInfoType::UInt64:
        *static_cast<uint64_t*>(dst) = *static_cast<const uint64_t*>(src);
        break;
    case GentlInfoType::Float64:
        *static_cast<double*>(dst) = *static_cast<const double*>(src);
        break;
    case GentlInfoType::Pointer:
        *static_cast<void**>(dst) = const_cast<void*>(src);
        break;
    case GentlInfoType::Bool8:
        *static_cast<char*>(dst) = *static_cast<const char*>(src);
        break;
    case GentlInfoType::SizeT:
        *static_cast<size_t*>(dst) = *static_cast<const size_t*>(src);
        break;
    case GentlInfoType::PtrDiff:
        *static_cast<ptrdiff_t*>(dst) = *static_cast<const ptrdiff_t*>(src);
        break;
    case GentlInfoType::StringList:
    case GentlInfoType::Buffer:
    default:
        qWarning() << "[BufferUtil] Type not implemented for buffer copy:" << static_cast<int>(type);
        return false;
    }
    return true;
}
