#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "opengl/opengl.hpp"
#include "opengl/types.hpp"

#include <fstream>

const std::string readFile(const char *filePath) {
    std::ifstream ifs(filePath);
    if (!ifs.is_open()) {
        throw std::runtime_error("Failed to read file!");
    }
    return std::string((std::istreambuf_iterator<char>(ifs)),
                  (std::istreambuf_iterator<char>()));
} 

void debugMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                  const GLchar *message, const void *userParam)
{
    auto const src_str = [source]() {
		switch (source)
		{
		case GL_DEBUG_SOURCE_API: return "API";
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM: return "WINDOW SYSTEM";
		case GL_DEBUG_SOURCE_SHADER_COMPILER: return "SHADER COMPILER";
		case GL_DEBUG_SOURCE_THIRD_PARTY: return "THIRD PARTY";
		case GL_DEBUG_SOURCE_APPLICATION: return "APPLICATION";
		case GL_DEBUG_SOURCE_OTHER: return "OTHER";
		}
        throw std::runtime_error("Unknown Source!");
	}();

	auto const type_str = [type]() {
		switch (type)
		{
		case GL_DEBUG_TYPE_ERROR: return "ERROR";
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "DEPRECATED_BEHAVIOR";
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: return "UNDEFINED_BEHAVIOR";
		case GL_DEBUG_TYPE_PORTABILITY: return "PORTABILITY";
		case GL_DEBUG_TYPE_PERFORMANCE: return "PERFORMANCE";
		case GL_DEBUG_TYPE_MARKER: return "MARKER";
		case GL_DEBUG_TYPE_OTHER: return "OTHER";
		}
        throw std::runtime_error("Unknown Type!");
	}();

	auto const severity_str = [severity]() {
		switch (severity) {
		case GL_DEBUG_SEVERITY_NOTIFICATION: return "NOTIFICATION";
		case GL_DEBUG_SEVERITY_LOW: return "LOW";
		case GL_DEBUG_SEVERITY_MEDIUM: return "MEDIUM";
		case GL_DEBUG_SEVERITY_HIGH: return "HIGH";
		}
        throw std::runtime_error("Unknown Severity!");
	}();
	std::cout << src_str << ", " << type_str << ", " << severity_str << ", " << id << ": " << message << '\n';
    if (severity != GL_DEBUG_SEVERITY_NOTIFICATION) {
        // throw std::runtime_error("");
    } 
}    


int main() {

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(640,
                                640, 
                                "Test",
                                NULL,
                                NULL);
    if (!window) {
        throw std::runtime_error("Failed to create window!");
    }    

    glfwMakeContextCurrent(window);                     

    gladLoadGL();

    gl::Shader vertShader = gl::Shader::createShader(gl::ShaderType::eVertex);
    vertShader.source(1, readFile("../../shaders/test.vert").c_str(), NULL);
    gl::Shader fragShader = gl::Shader::createShader(gl::ShaderType::eFragment);
    fragShader.source(1, readFile("../../shaders/test.frag").c_str(), NULL);
    
    std::cout << vertShader.getInfoLog() << '\n';
    std::cout << fragShader.getInfoLog() << '\n';

    gl::Program program = gl::Program::createProgram();
    program.attachShader(vertShader);
    program.attachShader(fragShader);
    program.link();

    std::cout << program.getInfoLog() << '\n';

    gl::Shader::deleteShader(vertShader);
    gl::Shader::deleteShader(fragShader);

    struct vec2 {
        float x;
        float y;
    };

    struct Vertex {
        vec2 pos;
    } vertex[3];

    gl::Buffer buffer = gl::Buffer::createBuffer(); 
    vertex[0].pos = {-0.5f, -0.5f};
    vertex[1].pos = { 0.5f, -0.5f};
    vertex[2].pos = { 0.0f,  0.5f};
    buffer.data(sizeof(Vertex) * 3, vertex, gl::BufferUsage::eStaticDraw);
    gl::VertexArray vertexArray = gl::VertexArray::createVertexArray();
    vertexArray.enableAttrib(0);
    vertexArray.attribBinding(0, 0);
    vertexArray.attribFormat(0, 2, gl::Type::eFloat, false, offsetof(Vertex, pos));
    vertexArray.vertexBuffer(0, buffer, 0, sizeof(Vertex));

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        gl::clear(gl::ClearBufferBits::eColor | gl::ClearBufferBits::eStencil | gl::ClearBufferBits::eDepth);
        gl::clearColor(0, 0, 0, 1);

        gl::enable(gl::Capabilities::eDepthTest);
        program.use();
        vertexArray.bind();
        gl::drawArrays(gl::Primitive::eTriangles, 0, 3);

        glfwSwapBuffers(window);
    }

    return 0;
}