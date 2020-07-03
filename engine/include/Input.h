#pragma once
#include "Application.h"

namespace Engine {
    class Input {

    public:

        static bool isKeyPressed(Engine::KeyCode&& key) {
            return glfwGetKey(Application::get().getWindow().get(), (int)key) == GLFW_PRESS;
        }

        static void getMousePosition(double& xpos, double& ypos) {
            glfwGetCursorPos(Application::get().getWindow().get(), &xpos, &ypos);
        }

    };
}
