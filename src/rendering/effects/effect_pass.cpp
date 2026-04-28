#include <flustral/rendering/effects/effect_pass.hpp>

#include <flustral/texture_sample.hpp>




ScopedRenderTexture EffectPass::apply(const Texture& texture) noexcept
{
    const ScopedRenderTexture down_sampled = TextureSample::down_sample(texture, down_sample_factor);
    const ScopedRenderTexture render_texture(Vector2(down_sampled.size().x, down_sampled.size().y));

    set_effect_target_texture_if_allowed(down_sampled);
    apply_effect_and_render_to(render_texture, down_sampled);

    return TextureSample::up_sample(render_texture, down_sample_factor);
}


void EffectPass::set_effect_target_texture_if_allowed(const Texture& source) noexcept
{
    if (!set_effect_target_texture_when_apply)
        return;

    *_effect.target_texture() = source;
    *_effect.target_texture_resolution() = { (float)source.width, (float)source.height };
}


void EffectPass::apply_effect_and_render_to(const RenderTexture& render_texture, const RenderTexture& source) noexcept
{
    BeginTextureMode(render_texture);
        BeginShaderMode(*_effect.shader());
        _effect.update();

            DrawTexture(source.texture, 0, 0, WHITE);

        EndShaderMode();
    EndTextureMode();
}