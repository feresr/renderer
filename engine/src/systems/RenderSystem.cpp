#include <RenderSystem.h>
#include <Components.h>
#include "ecs.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "model.h"
#include "Shader.h"

RenderSystem::RenderSystem(int gameResolutionWidth, int gameResolutionHeight) :
        GAME_RESOLUTION_WIDTH(gameResolutionWidth), GAME_RESOLUTION_HEIGHT(gameResolutionHeight) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

Shader* shader;
Model* obj;
glm::mat4 model;
glm::mat4 view;

void RenderSystem::onAddedToScene(Scene* scene) {
    shader = new Shader("assets/vertex.glsl", "assets/fragment.glsl");
    obj = new Model("assets/sponza/sponza.obj");

    model = glm::mat4(1.0);
    view = glm::translate(view, glm::vec3(0, 0.0f, 0.0f));
    glm::mat4 projection = glm::perspective(
            glm::radians(45.0f),
            (float) GAME_RESOLUTION_WIDTH / (float) GAME_RESOLUTION_HEIGHT,
            1.0f,
            3000.0f);
    shader->use();
    shader->setMatrix("model", glm::value_ptr(model));
    shader->setMatrix("projection", glm::value_ptr(projection));
}

float lightH = 0.0;
glm::vec3 lightpos(0.0, 20.0, 0.0);

void RenderSystem::update(Scene* scene) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    auto camera = scene->findFirst<CameraComponent>()->get<CameraComponent>();
    view = glm::lookAt(camera->position, camera->position + glm::normalize(camera->direction),
                       glm::vec3(0.0, 1.0, 0.0));

    shader->use();
    lightH+= .01f;
    lightpos.y = 480 + cos(lightH) * 440;
    lightpos.x = sin(lightH) * 200;
    shader->setVec3("lightpos", lightpos);
    shader->setMatrix("view", glm::value_ptr(view));
    obj->Draw(*shader);
}

void RenderSystem::onRemovedFromScene(Scene* scene) {
    delete shader;
    delete obj;
    System::onRemovedFromScene(scene);
}

RenderSystem::~RenderSystem() = default;
