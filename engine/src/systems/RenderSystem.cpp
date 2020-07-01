#include <RenderSystem.h>
#include "glad/glad.h"
#include "ecs.h"
#include "Shader.h"

RenderSystem::RenderSystem(int gameResolutionWidth, int gameResolutionHeight) :
        GAME_RESOLUTION_HEIGHT(gameResolutionWidth), GAME_RESOLUTION_WIDTH(gameResolutionHeight) {}


void RenderSystem::onAddedToScene(Scene* scene) {

    Shader shader("assets/vertex.glsl", "assets/fragment.glsl");

    shader.use();
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //pos
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);
    //color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    float vertices[] = {
            .0f, .5f, 1.0, 0.0, 0.0,
            -.5f, -.5f, 0.0, 1.0, 0.0,
            .5f, -.5f, 0.0, 0.0, 1.0,
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //TODO: static vs dynamic?

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //glBindVertexArray(0);
}

void RenderSystem::update(Scene* scene) {
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void RenderSystem::onRemovedFromScene(Scene* scene) {
    System::onRemovedFromScene(scene);
}

RenderSystem::~RenderSystem() = default;
