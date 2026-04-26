#pragma once

#include <memory>

#include <raylib.h>

#include <flustral/rendering/effects/effect.hpp>




class EffectPass : Updateable
{
private:
    std::unique_ptr<Effect> _effect;


public:
    bool set_effect_target_texture_when_apply = true;


    explicit EffectPass(std::unique_ptr<Effect> effect) noexcept
        : _effect(std::move(effect)) {}


    void update() noexcept override { _effect->update(); }


    RenderTexture apply(const Texture& texture) noexcept;


    Effect* effect() noexcept { return _effect.get(); }
};