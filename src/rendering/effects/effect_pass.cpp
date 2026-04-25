#include <flustral/rendering/effects/effect_pass.hpp>




Texture EffectPass::apply(const Texture& texture) noexcept
{
    initialize_texture_buffer(texture);
    draw_texture_to_buffer_with_effect(texture);

    return _texture_buffer->texture;
}


void EffectPass::draw_texture_to_buffer_with_effect(const Texture &texture)
{
    BeginTextureMode(*_texture_buffer);
        BeginShaderMode(*_effect->shader());
        _effect->update();

            DrawTexture(texture, 0, 0, WHITE);

        EndShaderMode();
    EndTextureMode();
}


void EffectPass::initialize_texture_buffer(const Texture& texture) noexcept
{
    if (_texture_buffer)
        UnloadRenderTexture(*_texture_buffer);

    _texture_buffer = std::make_unique<RenderTexture>(LoadRenderTexture(texture.width, texture.height));
}