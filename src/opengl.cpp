#include "opengl.hpp"

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
    glMapNamedBufferRange(m_id, offset, length, access);
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

} // namespace gl


