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
    
private:
    Buffer(GLuint id);

private:
    GLuint m_id;
};

} // namespace gl

#endif