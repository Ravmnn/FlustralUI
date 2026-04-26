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
    DrawTextureRec(texture, { position.x, position.y, (float)texture.width, (float)-texture.height }, {}, WHITE);
}