#include <flustral/rendering/texture_renderer.hpp>




TextureRenderer::TextureRenderer(const unsigned int width, const unsigned int height) noexcept
    : _texture(LoadRenderTexture(width, height))
{}




void TextureRenderer::begin_render() noexcept
{
    BeginTextureMode(_texture);
    ClearBackground(clear_color);
}


void TextureRenderer::end_render() noexcept
{
    EndTextureMode();
}




void TextureRenderer::draw_y_inverted_texture(const Texture& texture, const Vector2& position) noexcept
{
    RenderTexture inverted = invert_texture_y(texture);
    DrawTexture(inverted.texture, position.x, position.y, WHITE);

    UnloadRenderTexture(inverted);
}


RenderTexture TextureRenderer::invert_texture_y(const Texture& texture) noexcept
{
    RenderTexture render = LoadRenderTexture(texture.width, texture.height);

    BeginTextureMode(render);
    DrawTextureRec(texture, { 0, 0, (float)texture.width, (float)-texture.height }, {}, WHITE);
    EndTextureMode();

    return render;
}