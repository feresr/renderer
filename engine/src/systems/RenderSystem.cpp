#include <RenderSystem.h>
#include "ecs.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "model.h"
#include "Shader.h"

RenderSystem::RenderSystem(int gameResolutionWidth, int gameResolutionHeight) :
        GAME_RESOLUTION_WIDTH(gameResolutionWidth), GAME_RESOLUTION_HEIGHT(gameResolutionHeight) {}

Shader* shader;
Model* backpack;
glm::mat4 model;

void RenderSystem::onAddedToScene(Scene* scene) {
    shader = new Shader("assets/vertex.glsl", "assets/fragment.glsl");
    backpack = new Model("assets/backpack/backpack.obj");

    glm::mat4 view = glm::mat4(1.0);
    model = glm::mat4(1.0);
    view = glm::translate(view, glm::vec3(0, 0, -5.0f));
    glm::mat4 projection = glm::perspective(
            glm::radians(45.0f),
            (float) GAME_RESOLUTION_WIDTH / (float) GAME_RESOLUTION_HEIGHT,
            .1f,
            100.0f
    );

    shader->use();
    shader->setMatrix("view", glm::value_ptr(view));
    shader->setMatrix("projection", glm::value_ptr(projection));
}

void RenderSystem::update(Scene* scene) {
    shader->use();
    model = glm::rotate(model, glm::radians(.5f), glm::vec3(0.0, -1.0, 0.0));
    shader->setMatrix("model", glm::value_ptr(model));
    backpack->Draw(*shader);
}

void RenderSystem::onRemovedFromScene(Scene* scene) {
    System::onRemovedFromScene(scene);
}

RenderSystem::~RenderSystem() = default;
