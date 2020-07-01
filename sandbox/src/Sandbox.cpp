#include <Engine.h>
#include <string>
#include <iostream>

class Sandbox : public Engine::Application {
public:
    Sandbox() : Engine::Application("My Sandbox app") {}

    void init() override {
        Application::init();
        std::cout << "My sandbox app initialized" << std::endl;

    }

    void update() override {
        Application::update();
    }

    void clean() override {
        Application::clean();
    }

    ~Sandbox() override = default;
};

Engine::Application* Engine::CreateApplication() {
    return new Sandbox();
}