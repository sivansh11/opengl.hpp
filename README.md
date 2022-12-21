# opengl.hpp
this is inspired by vulkan.hpp 

NOTE: this opengl bindings currently only impliments opengl dsa

Buffer Example 

this
```
GLuint id;
glCreateBuffer(1, id);
GLbitfield flags = ...;
glNamedBufferData(id, sizeof(Data), &data, flags);
```

becomes
```
gl::Buffer buffer = gl::Buffer::createBuffer();
gl::BufferUsage flags = ...;
buffer.data(sizeof(Data), &data, flags);
```

opengl.hpp not only reduces loc (tho marginally), it converts runtime errors to compile time errors. It does this by forcing the user to use the correct flags. For example

glNamedBufferStorage may take in combination of many opengl enums, this may be error prone, </br>opengl.hpp combines all similar flags/enums together under a common type
for example all buffer storage flags are grouped under BufferStorage

all flags follow a common transformation
for example 
GL_STATIC_DRAW is a buffer usage flag
this gets converted to gl::BufferUsage::eStaticDraw

