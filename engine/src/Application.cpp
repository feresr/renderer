#include "Application.h"
#include "ecs.h"
#include "RenderSystem.h"
#include <utility>

Engine::Application::Application(std::string name) : appName{std::move(name)} {

}

void Engine::Application::init() {
    currentScene = new Scene();
    currentScene->registerSystem(new RenderSystem(800, 600));
}

bool Engine::Application::isRunning() {
    return true;
}

bool Engine::Application::handleEvents() {
    return false;
}

void Engine::Application::update() {
    currentScene->update();
}

void Engine::Application::clean() {

}

Engine::Application::~Application() {
    delete currentScene;
}

void Engine::Application::setScene(Scene* scene) {
    delete this->currentScene;
    this->currentScene = scene;
}

Scene* Engine::Application::getScene() {
    return currentScene;
};
