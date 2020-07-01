#pragma once

#include <string>
#include "ecs.h"

namespace Engine {
    class Application {

    public:
        explicit Application(std::string name = "Untitled app");

        virtual void init();

        virtual bool isRunning();

        virtual bool handleEvents();

        virtual void update();

        virtual void clean();

        virtual ~Application();

        const std::string appName;

        virtual void setScene(Scene* scene);

        virtual Scene* getScene();

    private:
        Scene* currentScene;
    };

    //to be defined by client
    extern Application* CreateApplication();
}
