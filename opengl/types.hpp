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

enum class Type : GLenum {
    eByte = GL_BYTE,
    eUnsignedByte = GL_UNSIGNED_BYTE,
    eShort = GL_SHORT,
    eUnsignedShort = GL_UNSIGNED_SHORT,
    eInt = GL_INT,
    eUnsignedInt = GL_UNSIGNED_INT,
    eFloat = GL_FLOAT,
    eDouble = GL_DOUBLE,
};

enum class ShaderType : GLenum{
    eVertex = GL_VERTEX_SHADER,
    eFragment = GL_FRAGMENT_SHADER,
    eGeometry = GL_GEOMETRY_SHADER,
    eCompute = GL_COMPUTE_SHADER,
    eTessControl = GL_TESS_CONTROL_SHADER,
    eTessEvaluation = GL_TESS_EVALUATION_SHADER,
};

enum class ShaderIV : GLenum {
    eType = GL_SHADER_TYPE,
    eDeleteStatus = GL_DELETE_STATUS,
    eCompileStatus = GL_COMPILE_STATUS,
    eInfoLogLength = GL_INFO_LOG_LENGTH,
    eShaderSourceLength = GL_SHADER_SOURCE_LENGTH,
};

enum class ProgramIV : GLenum {
    eDeleteStatus = GL_DELETE_STATUS,
    eLinkStatus = GL_LINK_STATUS,
    eValidateStatus = GL_VALIDATE_STATUS,
    eIngoLogLength = GL_INFO_LOG_LENGTH,
    eAttachedShaders = GL_ATTACHED_SHADERS,
    eActiveAttributes = GL_ACTIVE_ATTRIBUTES,
    eActiveAttributeMaxLength = GL_ACTIVE_ATTRIBUTE_MAX_LENGTH,
    eActiveUniforms = GL_ACTIVE_UNIFORMS,
    eActiveUniformMaxLength = GL_ACTIVE_UNIFORM_MAX_LENGTH,
};

enum class Capabilities : GLenum {
    eColorLogicOP = GL_COLOR_LOGIC_OP,
    eColorTable = GL_COLOR_TABLE,
    eConvolution1D = GL_CONVOLUTION_1D,
    eConvolution2D = GL_CONVOLUTION_2D,
    eCullFace = GL_CULL_FACE,
    eDepthTest = GL_DEPTH_TEST,
    eDither = GL_DITHER,
    eHistogram = GL_HISTOGRAM,
    eLineSmooth = GL_LINE_SMOOTH,
    eMinMax = GL_MINMAX,
    eMultiSample = GL_MULTISAMPLE,
    ePolygonOffsetFill = GL_POLYGON_OFFSET_FILL,
    ePolygonOffsetLine = GL_POLYGON_OFFSET_LINE,
    ePolygonOffsetPoint = GL_POLYGON_OFFSET_POINT,
    ePolygonSmooth = GL_POLYGON_SMOOTH,
    ePostColorMatrixColorTable = GL_POST_COLOR_MATRIX_COLOR_TABLE,
    ePostConvolutionColorTable = GL_POST_CONVOLUTION_COLOR_TABLE,
    eSampleAlphaToCoverage = GL_SAMPLE_ALPHA_TO_COVERAGE,
    eSampleAlphaToOne = GL_SAMPLE_ALPHA_TO_ONE,
    eSampleCoverage = GL_SAMPLE_COVERAGE,
    eSeparable2D = GL_SEPARABLE_2D,
    eScissorTest = GL_SCISSOR_TEST,
    eStencilTest = GL_STENCIL_TEST,
    eTexture1D = GL_TEXTURE_1D,
    eTexture2D = GL_TEXTURE_2D,
    eTexture3D = GL_TEXTURE_3D,
    eTextureCubeMap = GL_TEXTURE_CUBE_MAP,
    eVertexProgramPointSize = GL_VERTEX_PROGRAM_POINT_SIZE,
};

enum class Primitive : GLenum {
    ePoints = GL_POINTS,
    eLineStrip = GL_LINE_STRIP,
    eLineLoop = GL_LINE_LOOP,
    eLines = GL_LINES,
    eLineStripAdjacency = GL_LINE_STRIP_ADJACENCY,
    eLinesAdjacency = GL_LINES_ADJACENCY,
    eTriangleStrip = GL_TRIANGLE_STRIP,
    eTriangleFan = GL_TRIANGLE_FAN,
    eTriangles = GL_TRIANGLES,
    eTriangleStripAdjacency = GL_TRIANGLE_STRIP_ADJACENCY,
    eTrianglesAdjacency = GL_TRIANGLES_ADJACENCY,
    ePatches = GL_PATCHES,
};

class ClearBufferBits : public BaseFlag<GLbitfield> {
public:
    ClearBufferBits() = default;
    ClearBufferBits(GLbitfield flag) : BaseFlag(flag) {}
    operator GLbitfield() {
        return flags;
    }
    constexpr static GLbitfield eColor = GL_COLOR_BUFFER_BIT;
    constexpr static GLbitfield eDepth = GL_DEPTH_BUFFER_BIT;
    constexpr static GLbitfield eStencil = GL_STENCIL_BUFFER_BIT;
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