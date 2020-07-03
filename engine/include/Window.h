#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>

class Window {

public:
    Window(const std::string& title, int width, int height);

    ~Window();

    GLFWwindow* get();

private:
    GLFWwindow* window;
};