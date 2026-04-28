#pragma once

#include <memory>

#include <raylib.h>

#include <flustral/rendering/effects/effect.hpp>
#include <flustral/rendering/scoped_render_texture.hpp>




class EffectPass : public Updateable
{
// TODO: use "field_" project wide

protected:
    Effect& _effect;


public:
    bool set_effect_target_texture_when_apply = true;
    float down_sample_factor = 1;


    explicit EffectPass(Effect& effect) noexcept
        : _effect(effect) {}


    void update() noexcept override { _effect.update(); }


    virtual ScopedRenderTexture apply(const Texture& texture) noexcept;


    Effect& effect() noexcept { return _effect; }


private:
    void set_effect_target_texture_if_allowed(const Texture& source) noexcept;
    void apply_effect_and_render_to(const RenderTexture& render_texture, const RenderTexture& source) noexcept;
};