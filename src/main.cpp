#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "opengl.hpp"
#include "types.hpp"

void init() {
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
}

int main() {

    init();

    struct SomeData {
        int i;
        float j;
    } someData {1, 2.0f};

    gl::Buffer buffer = gl::Buffer::createBuffer();

    buffer.data(sizeof(SomeData), &someData, gl::BufferUsage::eStaticDraw);

    gl::Buffer::deleteBuffer(buffer);

    return 0;
}