#include "Sandbox.h"

class Sandbox : public Engine::Application {
public:
    Sandbox() : Engine::Application("My Sandbox app") {
        Entity* camera = scene->create();
        camera->assign<CameraComponent>(
                glm::vec3(0),
                glm::vec3(0.0, 0.0, 1.0f)
        );
    }

    float lastX = 0;
    float lastY = 0;

    float yaw = 0;
    float pitch = 0;

    void handleEvents() override {
        auto camera = scene->findFirst<CameraComponent>()->get<CameraComponent>();
        if (Engine::Input::isKeyPressed(Engine::KeyCode::W)) camera->position += (camera->direction * 5.f);
        if (Engine::Input::isKeyPressed(Engine::KeyCode::S)) camera->position -= camera->direction * 5.f;
        if (Engine::Input::isKeyPressed(Engine::KeyCode::A))
            camera->position -= glm::cross(camera->direction, glm::vec3(0.0, 1.0, 0.0));
        if (Engine::Input::isKeyPressed(Engine::KeyCode::D))
            camera->position += glm::cross(camera->direction, glm::vec3(0.0, 1.0, 0.0));

        double mouseX, mouseY;
        Engine::Input::getMousePosition(mouseX, mouseY);


        float xoffset = (float) mouseX - lastX;
        float yoffset = lastY - (float) mouseY;
        lastX = (float) mouseX;
        lastY = (float) mouseY;
        float sensitivity = 0.1f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;
        yaw += xoffset;
        pitch += yoffset;
        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;
        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        camera->direction = glm::normalize(direction);
    }

    ~Sandbox() override = default;
};

Engine::Application* Engine::CreateApplication() {
    return new Sandbox();
}