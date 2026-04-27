#include <flustral/components/surface.hpp>
#include <flustral/components/texture.hpp>
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


    {
        Texture background_texture_source = LoadTexture("/home/ravmn/Documentos/programming/cpp/Flustral/resources/images/background.jpg");

        SceneLayer* const background = new SceneLayer(std::make_unique<TextureRenderer>());
        SceneLayer* const foreground = new SceneLayer(std::make_unique<TextureRenderer>());

        TextureComponent* const background_texture = background->add_component<TextureComponent>(Vector2{}, Vector2{ 1920, 1080 }, background_texture_source);
        SurfaceComponent* const rectangle = foreground->add_component<SurfaceComponent>(Vector2{ 200, 200 }, Vector2{ 150, 150 }, 15.0);

        Scene scene;
        scene.layers.push_back(std::unique_ptr<SceneLayer>(background));
        scene.layers.push_back(std::unique_ptr<SceneLayer>(foreground));


        while (!WindowShouldClose())
        {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                rectangle->set_motion_target(GetMousePosition());

            scene.update();
            scene.draw();
        }
    }


    CloseWindow();

    return 0;
}