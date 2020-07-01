#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Application.h"

int main() {
    if (!glfwInit()) return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    Engine::Application* application = Engine::CreateApplication();
    GLFWwindow* window = glfwCreateWindow(800, 600, application->appName.c_str(), NULL, NULL);
    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGL()) std::cout << "Failed to initialize GLAD" << std::endl;

    application->init();
    while (!glfwWindowShouldClose(window)) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }

        if (!application->isRunning()) break;
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        application->update();
        application->handleEvents();//??
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    application->clean();
    delete application;
    return 0;
}
