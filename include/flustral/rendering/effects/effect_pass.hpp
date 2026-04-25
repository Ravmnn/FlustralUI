#pragma once

#include <memory>

#include <raylib.h>

#include <flustral/rendering/effects/effect.hpp>




class EffectPass : Updateable
{
private:
    std::unique_ptr<Effect> _effect;
    std::unique_ptr<RenderTexture> _texture_buffer;


public:
    explicit EffectPass(std::unique_ptr<Effect> effect) noexcept
        : _effect(std::move(effect)) {}


    void update() noexcept override { _effect->update(); }


    Texture apply(const Texture &texture) noexcept;


    Effect* effect() noexcept { return _effect.get(); }


private:
    void initialize_texture_buffer(const Texture& texture) noexcept;
    void draw_texture_to_buffer_with_effect(const Texture &texture);
};