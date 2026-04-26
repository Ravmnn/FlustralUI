#include <flustral/rendering/effects/effect_pass.hpp>




RenderTexture EffectPass::apply(const Texture& texture) noexcept
{
    const RenderTexture render_texture = LoadRenderTexture(texture.width, texture.height);

    if (set_effect_target_texture_when_apply)
        *_effect->target_texture() = texture;

    BeginTextureMode(render_texture);
        BeginShaderMode(*_effect->shader());
        _effect->update();

            DrawTexture(texture, 0, 0, WHITE);

        EndShaderMode();
    EndTextureMode();

    return render_texture;
}