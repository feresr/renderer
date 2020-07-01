#include "ecs.h"

Entity* Scene::create() {
    auto* e = new Entity();
    entities.push_back(e);
    return e;
}

void Scene::destroy(Entity* entity) {
    if (!entity) return;
    entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
    delete entity;
}
//TODO: Use unique_ptr to make the fact that WORLD owns the system pointers (and is in charge of clearing them)
void Scene::registerSystem(System* system) {
    systems.push_back(system);
    system->onAddedToScene(this);
}

//TODO: Use unique_ptr to make the fact that WORLD owns the system pointers (and is in charge of clearing them)
void Scene::unregisterSystem(System* system) {
    if (!system) return;
    systems.erase(std::remove(systems.begin(), systems.end(), system), systems.end());
    system->onRemovedFromScene(this);
    delete system;
}

void Scene::update() {
    for (auto system : systems) system->update(this);
}

Scene::~Scene() {
    for (auto system : systems) {
        system->onRemovedFromScene(this);
        delete system;
    }
    systems.clear();

    for (auto entity : entities) delete entity;
    entities.clear();
}

//void Scene::handleEvent(SDL_Event& event) {
//    for (auto system : systems) system->handleEvent(event);
//}

Entity::~Entity() {
    for (auto& component : *components) delete component.second;
    components->clear();
}
