
#include "ecs.h"

class RenderSystem : public System {

public:
    explicit RenderSystem(int gameResolutionWidth, int gameResolutionHeight);

    void onAddedToScene(Scene* scene) override;

    //void setBackgroundColor(int r, int g, int b);

    void update(Scene* world) override;

    void onRemovedFromScene(Scene* world) override;

    ~RenderSystem() override;

private:
    const int GAME_RESOLUTION_WIDTH;
    const int GAME_RESOLUTION_HEIGHT;
};