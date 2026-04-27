#include <flustral/rendering/window_renderer.hpp>




WindowRenderer::WindowRenderer()
    : TextureRenderer(GetScreenWidth(), GetScreenHeight())
{}




void WindowRenderer::begin_render() noexcept
{
    if (use_buffer_texture)
    {
        TextureRenderer::begin_render();
        return;
    }

    BeginDrawing();
    ClearBackground(clear_color);
}


void WindowRenderer::end_render() noexcept
{
    if (!use_buffer_texture)
    {
        EndDrawing();
        return;
    }

    TextureRenderer::end_render();
    render_to_window();
}


void WindowRenderer::render_to_window() const noexcept
{
    BeginDrawing();
    ClearBackground(clear_color);

    DrawTexture(contents().texture, 0, 0, WHITE);

    EndDrawing();
}