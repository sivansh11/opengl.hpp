#ifndef TYPES_HPP
#define TYPES_HPP

#include <glad/glad.h>

#include <iostream>

namespace gl {

template <typename T>
class BaseFlag {
public:
    T flags;
    BaseFlag() = default;
    BaseFlag(T flag) : flags(flag) {}
    constexpr bool operator==(T other) {
        return flags == other.flags;
    }
    constexpr bool operator!=(T other) {
        return flags != other.flags;
    }
    constexpr explicit operator bool() {
        return flags != 0;
    }
    constexpr explicit operator T() {
        return flags;
    }
    constexpr BaseFlag operator|(T other) {
        return {flags | other.flags};
    }
    constexpr BaseFlag operator&(T other) {
        return {flags & other.flags};
    }
    constexpr BaseFlag operator^(T other) {
        return {flags ^ other.flags};
    }
    constexpr BaseFlag operator~() {
        return {~flags};
    }
    constexpr BaseFlag& operator|=(T other) {
        flags |= other.flags;
        return *this;
    }
    constexpr BaseFlag& operator&=(T other) {
        flags &= other.flags;
        return *this;
    }
    constexpr BaseFlag& operator^=(T other) {
        flags ^= other.flags;
        return *this;
    }
};

class BufferUsage : virtual public BaseFlag<GLenum> {
public: 
    BufferUsage() = default;
    BufferUsage(GLbitfield flag) : BaseFlag(flag) {}
    operator GLenum() {
        return flags;
    }
    static constexpr GLenum eStreamDraw = GL_STREAM_DRAW;
    static constexpr GLenum eStreamCopy = GL_STREAM_COPY;
    static constexpr GLenum eStreamRead = GL_STREAM_READ;

    static constexpr GLenum eStaticDraw = GL_STATIC_DRAW;
    static constexpr GLenum eStaticCopy = GL_STATIC_COPY;
    static constexpr GLenum eStaticRead = GL_STATIC_READ;

    static constexpr GLenum eDynamicDraw = GL_DYNAMIC_DRAW;
    static constexpr GLenum eDynamicCopy = GL_DYNAMIC_COPY;
    static constexpr GLenum eDynamicRead = GL_DYNAMIC_READ;
};

class BufferMap : virtual public BaseFlag<GLbitfield> {
public:
    BufferMap() = default;
    BufferMap(GLbitfield flag) : BaseFlag(flag) {}
    operator GLbitfield() {
        return flags;
    }
    static constexpr GLbitfield eRead = GL_MAP_READ_BIT;
    static constexpr GLbitfield eWrite = GL_MAP_WRITE_BIT;
    static constexpr GLbitfield ePersistent = GL_MAP_PERSISTENT_BIT;
    static constexpr GLbitfield eCoherent = GL_MAP_COHERENT_BIT;
    static constexpr GLbitfield eInvalidateRange = GL_MAP_INVALIDATE_RANGE_BIT;
    static constexpr GLbitfield eInvalidate = GL_MAP_INVALIDATE_BUFFER_BIT;
    static constexpr GLbitfield eFlushExplicit = GL_MAP_FLUSH_EXPLICIT_BIT;
    static constexpr GLbitfield eUnsynchronized = GL_MAP_UNSYNCHRONIZED_BIT;

};

class BufferStorage : virtual public BufferMap {
public:
    BufferStorage() = default;
    BufferStorage(GLbitfield flag) : BaseFlag(flag) {}
    operator GLbitfield() {
        return flags;
    }
    static constexpr GLbitfield eDynamic = GL_DYNAMIC_STORAGE_BIT;
    static constexpr GLbitfield eClient = GL_CLIENT_STORAGE_BIT;
    static constexpr GLbitfield eNone = GL_NONE;
};


// enum class TextureType : GLint {
//     e1D = GL_TEXTURE_1D,
//     e2D = GL_TEXTURE_2D,
//     e3D = GL_TEXTURE_3D,
//     e1DArray = GL_TEXTURE_1D_ARRAY,
//     e2DArray = GL_TEXTURE_2D_ARRAY,
//     eCubeMap = GL_TEXTURE_CUBE_MAP,
//     eCubeMapArray = GL_TEXTURE_CUBE_MAP_ARRAY,
//     e2DMultiSample = GL_TEXTURE_2D_MULTISAMPLE,
//     e2DMultiSampleArray = GL_TEXTURE_2D_MULTISAMPLE_ARRAY,
// };

// enum class InternalFormat : GLint {
//     eR8 = GL_R8,
//     eR8snorm = GL_R8_SNORM,
//     eR16 = GL_R16,
//     eR16snorm = GL_R16_SNORM,

//     eR8G8 = GL_RG8,
//     eR8G8snorm = GL_RG8_SNORM,
//     eR16G16 = GL_RG16,
//     eR16G16snorm = GL_RG16_SNORM,

//     eR8G8B8 = GL_RGB8,
//     eR8G8B8snorm = GL_RGB8_SNORM,
//     eR16G16B16 = GL_RGB16,
//     eR16G16B16snorm = GL_RGB16_SNORM,

//     eD32 = GL_DEPTH_COMPONENT32,
//     eD32Float = GL_DEPTH_COMPONENT32F,
//     eD24 = GL_DEPTH_COMPONENT24,
//     eD16 = GL_DEPTH_COMPONENT16,
//     eD32FS8 = GL_DEPTH32F_STENCIL8,
//     eD24S8 = GL_DEPTH32F_STENCIL8,
//     // todo: add all formats
// };

// enum class SampleCount : uint8_t {

// };

// enum class Format : GLuint {
//     eR = GL_RED,
//     eRG = GL_RG,
//     eRGB = GL_RGB,
//     eRGBA = GL_RGBA,
//     eBGRA = GL_BGRA,

//     //todo: add all formats  
// };

// enum class Type : GLuint {
//     eUByte = GL_UNSIGNED_BYTE,
//     eSByte = GL_BYTE,
//     eUInt = GL_UNSIGNED_INT,
//     // todo: all all types
// };

// enum class Filter : GLuint {
//     eNearest = GL_NEAREST,
//     eLinear = GL_LINEAR,
//     eNone = GL_NONE,
// };

} // namespace gl

#endif