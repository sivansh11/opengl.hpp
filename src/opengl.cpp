#include "opengl.hpp"

#include <vector>

namespace gl {

Buffer::Buffer(GLuint id) : m_id(id) {}

Buffer Buffer::createBuffer() {
    GLuint id;
    glCreateBuffers(1, &id);
    return {id};
}

void Buffer::deleteBuffer(Buffer& buffer) {
    glDeleteBuffers(1, &buffer.m_id);
    buffer.m_id = 0;
}

void Buffer::copySubData(Buffer& readBuffer, Buffer& writeBuffer, size_t readOffset, size_t writeOffset, size_t size) {
    glCopyNamedBufferSubData(readBuffer.m_id, writeBuffer.m_id, readOffset, writeOffset, size);
}

void Buffer::storage(size_t size, const void *data, BufferStorage flags) {
    glNamedBufferStorage(m_id, size, data, flags);
}

void Buffer::data(size_t size, const void *data, BufferUsage usage) {
    glNamedBufferData(m_id, size, data, usage);
}

void Buffer::subData(size_t offset, size_t size, const void *data) {
    glNamedBufferSubData(m_id, offset, size, data);
}

void Buffer::getSubData(size_t offset, size_t size, void *data) {
    glGetNamedBufferSubData(m_id, offset, size, data);
}

void *Buffer::mapRange(size_t offset, size_t length, BufferMap access) {
    return glMapNamedBufferRange(m_id, offset, length, access);
}

void Buffer::flushRange(size_t offset, size_t length) {
    glFlushMappedNamedBufferRange(m_id, offset, length);
}

void Buffer::unmap() {
    glUnmapNamedBuffer(m_id);
}

void Buffer::invalidateData() {
    glInvalidateBufferData(m_id);
}

void Buffer::invalidateSubData(size_t offset, size_t length) {
    glInvalidateBufferSubData(m_id, offset, length);
}

VertexArray::VertexArray(GLuint id) : m_id(id) {}

VertexArray VertexArray::createVertexArray() {
    GLuint id;
    glCreateVertexArrays(1, &id);
    return {id};
}

void VertexArray::deleteVertexArray(VertexArray& vertexArray) {
    glDeleteVertexArrays(1, &vertexArray.m_id);
    vertexArray.m_id = 0;
}

void VertexArray::unbind() {
    glBindVertexArray(0);
}

void VertexArray::bind() {
    glBindVertexArray(m_id);
}

void VertexArray::enableAttrib(uint32_t index) {
    glEnableVertexArrayAttrib(m_id, index);
}

void VertexArray::disableAttrib(uint32_t index) {
    glDisableVertexArrayAttrib(m_id, index);
}

void VertexArray::attribBinding(uint32_t attribIndex, uint32_t bindingIndex) {
    glVertexArrayAttribBinding(m_id, attribIndex, bindingIndex);
}

void VertexArray::attribFormat(uint32_t attribIndex, int32_t size, Type type, bool normalised, uint32_t relativeOffset) {
    glVertexArrayAttribFormat(m_id, attribIndex, size, static_cast<GLenum>(type), normalised, relativeOffset);
}

void VertexArray::vertexBuffer(uint32_t bindingIndex, Buffer& buffer, size_t offset, size_t stride) {
    glVertexArrayVertexBuffer(m_id, bindingIndex, buffer.m_id, offset, stride);
}

void VertexArray::elementBuffer(Buffer& buffer) {
    glVertexArrayElementBuffer(m_id, buffer.m_id);
}

Shader::Shader(GLuint id) : m_id(id) {}

Shader Shader::createShader(ShaderType type) {
    return {glCreateShader(static_cast<GLenum>(type))};
}

void Shader::deleteShader(Shader& shader) {
    glDeleteShader(shader.m_id);
    shader.m_id = 0;
}

void Shader::source(size_t count, const char *const string, const int *length) {
    glShaderSource(m_id, count, &string, length);
}

void Shader::compile() {
    glCompileShader(m_id);
}

int Shader::getiv(ShaderIV pname) {
    int params;
    glGetShaderiv(m_id, static_cast<GLenum>(pname), &params);
    return params;
}

std::string Shader::getInfoLog() {
    int infoLength = getiv(ShaderIV::eInfoLogLength);
    std::vector<char> infoBuff(infoLength);
    glGetShaderInfoLog(m_id, infoLength, NULL, infoBuff.data());
    return std::string(infoBuff.begin(), infoBuff.end());
}

Program::Program(GLuint id) : m_id(id) {}

Program Program::createProgram() {
    return {glCreateProgram()};
}

void Program::deleteProgram(Program& program) {
    glDeleteProgram(program.m_id);
    program.m_id = 0;
}

void Program::useNone() {
    glUseProgram(0);
}

void Program::use() {
    glUseProgram(m_id);
}

void Program::attachShader(Shader& shader) {
    glAttachShader(m_id, shader.m_id);
} 

void Program::link() {
    glLinkProgram(m_id);
}

int Program::getiv(ProgramIV pname) {
    int params;
    glGetProgramiv(m_id, static_cast<GLenum>(pname), &params);
    return params;
}

std::string Program::getInfoLog() {
    int infoLogLength = getiv(ProgramIV::eIngoLogLength);
    std::vector<char> infoBuff(infoLogLength);
    glGetProgramInfoLog(m_id, infoLogLength, NULL, infoBuff.data());
    return std::string(infoBuff.begin(), infoBuff.end());
}

void clearColor(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}

void clear(ClearBufferBits mask) {
    glClear(mask);
}

void enable(Capabilities capability) {
    glEnable(static_cast<GLenum>(capability));
}
void disable(Capabilities capability) {
    glDisable(static_cast<GLenum>(capability));
}

void drawArrays(Primitive mode, int32_t first, size_t count) {
    glDrawArrays(static_cast<GLenum>(mode), first, count);
}

void drawElements(Primitive mode, size_t count, Type type, const void *indices) {
    glDrawElements(static_cast<GLenum>(mode), count, static_cast<GLenum>(type), indices);
}

} // namespace gl


