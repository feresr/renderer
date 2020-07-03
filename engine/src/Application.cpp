#include "Application.h"

Engine::Application* Engine::Application::instance = nullptr;

Engine::Application::Application(std::string name) : appName{std::move(name)} {
    window = std::make_unique<Window>(appName, WINDOW_WIDTH, WINDOW_HEIGHT);
    instance = this;
};

Engine::Application::~Application() = default;

void Engine::Application::run() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    scene->registerSystem(new RenderSystem(WINDOW_WIDTH, WINDOW_HEIGHT));

    while (!glfwWindowShouldClose(window->get())) {
        if (glfwGetKey(window->get(), GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window->get(), true);
        //if (!application->isRunning()) break;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        handleEvents();
        scene->update();
        glfwSwapBuffers(window->get());
        glfwPollEvents();
    }
}

void Engine::Application::handleEvents() {}