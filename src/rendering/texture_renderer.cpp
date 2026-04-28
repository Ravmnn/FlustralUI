#include <flustral/rendering/texture_renderer.hpp>




TextureRenderer::TextureRenderer(const unsigned int width, const unsigned int height) noexcept
    : _render_texture(LoadRenderTexture(width, height))
{}




void TextureRenderer::begin_render() noexcept
{
    BeginTextureMode(_render_texture);
    ClearBackground(clear_color);
}


void TextureRenderer::end_render() noexcept
{
    EndTextureMode();
}




void TextureRenderer::draw_y_inverted_texture(const Texture& texture) noexcept
{
    DrawTextureRec(texture, { 0, 0, (float)texture.width, (float)-texture.height }, {}, WHITE);
}