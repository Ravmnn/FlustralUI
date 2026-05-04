#include <flustral/rendering/texture_renderer.hpp>




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