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

    draw_y_inverted_contents();

    EndDrawing();
}


void WindowRenderer::draw_y_inverted_contents() const noexcept
{
    const Texture texture = contents();
    const Rectangle source = Rectangle{ 0, 0, texture.width, -texture.height };
    DrawTextureRec(texture, source, {}, WHITE);
}