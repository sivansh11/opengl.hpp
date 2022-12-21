#ifndef OPENGL_HPP
#define OPENGL_HPP

#include "types.hpp"

namespace gl {

class Buffer {
public:
    Buffer() = delete;
    static Buffer createBuffer();
    static void deleteBuffer(Buffer& buffer);
    static void copySubData(Buffer& readBuffer, Buffer& writeBuffer, size_t readOffset, size_t writeOffset, size_t size);

    void storage(size_t size, const void *data, BufferStorage flags);
    void data(size_t size, const void *data, BufferUsage usage);
    void subData(size_t offset, size_t size, const void *data);
    void getSubData(size_t offset, size_t size, void *data);
    void *mapRange(size_t offset, size_t length, BufferMap access);
    void flushRange(size_t offset, size_t length);
    void unmap();
    void invalidateData();
    void invalidateSubData(size_t offset, size_t length);

    friend class VertexArray;

private:
    Buffer(GLuint id);

private:
    GLuint m_id;
};

class VertexArray {
public:
    VertexArray() = delete;
    static VertexArray createVertexArray();
    static void deleteVertexArray(VertexArray& vertexArray);
    static void unbind();

    void bind();
    void enableAttrib(uint32_t index);
    void disableAttrib(uint32_t index);
    void attribBinding(uint32_t location, uint32_t bindingIndex);
    void attribFormat(uint32_t location, int32_t size, Type type, bool normalised, uint32_t relativeOffset);
    void vertexBuffer(uint32_t bindingIndex, Buffer& buffer, size_t offset, size_t stride);
    void elementBuffer(Buffer& buffer);

private:
    VertexArray(GLuint id);

private:
    GLuint m_id;
};

class Shader {
public:
    static Shader createShader(ShaderType type);
    static void deleteShader(Shader& shader); 

    void source(size_t count, const char *const string, const int *length);
    void compile();
    int getiv(ShaderIV pname);
    std::string getInfoLog();

    friend class Program;

private:
    Shader(GLuint id);

private:
    GLuint m_id;
};

class Program {
public:
    static Program createProgram();
    static void deleteProgram(Program& program);
    static void useNone();  // unbind program

    void use();
    void attachShader(Shader& shader);
    void link();
    int getiv(ProgramIV pname);
    std::string getInfoLog();

public:
    Program(GLuint id);

private:
    GLuint m_id;
};

void clearColor(float r, float g, float b, float a);
void clear(ClearBufferBits mask);
void enable(Capabilities capability);
void disable(Capabilities capability);
void drawArrays(Primitive mode, int32_t first, size_t count);
void drawElements(Primitive mode, size_t count, Type type, const void *indices);

} // namespace gl

#endif