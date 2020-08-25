#include "Application.h"

Engine::Application* Engine::Application::instance = nullptr;

Engine::Application::Application(std::string name) : appName{std::move(name)} {
    window = std::make_unique<Window>(appName, WINDOW_WIDTH, WINDOW_HEIGHT);
    instance = this;
};

Engine::Application::~Application() = default;

void Engine::Application::run() {
    scene->registerSystem(new RenderSystem(WINDOW_WIDTH, WINDOW_HEIGHT));

    while (!glfwWindowShouldClose(window->get())) {
        glfwPollEvents();
        if (glfwGetKey(window->get(), GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window->get(), true);
        if (!isRunning()) break;
        handleEvents();
        scene->update();
        glfwSwapBuffers(window->get());
    }
}