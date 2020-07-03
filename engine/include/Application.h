#pragma once

#include <string>
#include "Window.h"
#include "ecs.h"
#include "KeyCodes.h"
#include "RenderSystem.h"

int main(int argc, char** argv);

namespace Engine {

    class Application {
    public:
        explicit Application(std::string name = "Untitled app");

        virtual ~Application();

        virtual void handleEvents();

        static Application& get() { return *instance; }

        Window& getWindow() { return *window; }

        std::unique_ptr<Scene> scene = std::make_unique<Scene>();

    private:
        virtual void run();

        const std::string appName;

        std::unique_ptr<Window> window;

        static Application* instance;

        friend int::main(int argc, char** argv);

        const uint WINDOW_WIDTH = 800 * 2;
        const uint WINDOW_HEIGHT = 600 * 2;
    };

    //to be defined by client
    extern Application* CreateApplication();
}
