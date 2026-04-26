#include <flustral/components/rectangle.hpp>
#include <flustral/components/component_manager.hpp>
#include <flustral/rendering/window_renderer.hpp>
#include <flustral/scene.hpp>




int main()
{
    SetTraceLogLevel(LOG_WARNING);

    int monitor = GetCurrentMonitor();
    SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(GetMonitorWidth(monitor), GetMonitorHeight(monitor), "Fluid Crystal UI");
    SetTargetFPS(60);

    SceneLayer* layer = new SceneLayer(std::make_unique<TextureRenderer>());
    RectangleComponent* rectangle = layer->add_component<RectangleComponent>(Vector2{ 200, 200 }, Vector2{ 150, 150 }, 0.2);

    Scene scene;
    scene.layers.push_back(std::unique_ptr<SceneLayer>(layer));


    while (!WindowShouldClose())
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            rectangle->set_motion_target(GetMousePosition());

        scene.update();
        scene.draw();
    }


    CloseWindow();

    return 0;
}