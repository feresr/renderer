#pragma once

#include "ecs.h"
#include "glm/glm.hpp"

struct CameraComponent : public Component {
    glm::vec3 position;
    glm::vec3 direction;

    explicit CameraComponent(glm::vec3 position, glm::vec3 direction) : position{position}, direction{direction} {}
};