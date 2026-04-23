#include <flustral/components/rectangle.hpp>
#include <flustral/components/component_manager.hpp>




int main()
{
    int monitor = GetCurrentMonitor();
    SetConfigFlags(FLAG_FULLSCREEN_MODE);
    InitWindow(GetMonitorWidth(monitor), GetMonitorHeight(monitor), "Fluid Crystal UI");
    SetTargetFPS(60);

    ComponentManager manager;
    RectangleComponent* rectangle = manager.add_component<RectangleComponent>(Vector2{ 200, 200 }, Vector2{ 150, 150 }, 0.2);


    while (!WindowShouldClose())
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            rectangle->set_motion_target(GetMousePosition());

        manager.update();

        BeginDrawing();
        ClearBackground(BLACK);

        manager.draw();

        EndDrawing();
    }


    CloseWindow();

    return 0;
}