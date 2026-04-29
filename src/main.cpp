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
        ExportImage(LoadImageFromTexture(background_texture_source), "/home/ravmn/Documentos/programming/cpp/Flustral/resources/debug/bg_source.png");

        SceneLayer* const background = new SceneLayer;
        SceneLayer* const foreground = new SceneLayer;
        SceneLayer* const foreground2 = new SceneLayer;
        SceneLayer* const foreground3 = new SceneLayer;

        TextureComponent* const background_texture = background->add_component<TextureComponent>(Vector2{}, Vector2{ 1920, 1080 }, background_texture_source);
        SurfaceComponent* const rectangle = foreground->add_component<SurfaceComponent>(Vector2{ 200, 200 }, Vector2{ 600, 500 }, 90.0);
        SurfaceComponent* const rectangle2 = foreground2->add_component<SurfaceComponent>(Vector2{ 200, 200 }, Vector2{ 400, 400 }, 60.0);
        SurfaceComponent* const rectangle3 = foreground3->add_component<SurfaceComponent>(Vector2{ 200, 200 }, Vector2{ 250, 250 }, 30.0);
        rectangle->effect().tint.value = {0.97, 0.93, 0.88};
        rectangle->effect().tint_strength.value = 2.2;

        Scene scene;
        scene.layers.push_back(std::unique_ptr<SceneLayer>(background));
        scene.layers.push_back(std::unique_ptr<SceneLayer>(foreground));
        scene.layers.push_back(std::unique_ptr<SceneLayer>(foreground2));
        scene.layers.push_back(std::unique_ptr<SceneLayer>(foreground3));


        while (!WindowShouldClose())
        {
            if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE))
                rectangle->set_motion_target(GetMousePosition());

            if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
                rectangle2->set_motion_target(GetMousePosition());

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                rectangle3->set_motion_target(GetMousePosition());

            scene.update_all();
            scene.draw_all();
        }
    }


    CloseWindow();

    return 0;
}