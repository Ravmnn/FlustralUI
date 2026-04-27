#pragma once

#include <flustral/rendering/effects/effect.hpp>
#include <flustral/rendering/effects/effect_property.hpp>




class SurfaceEffect : public Effect
{
public:
    EffectProperty<Texture> background;
    EffectProperty<Texture> blurred_background;
    EffectProperty<Vector2> resolution;

    EffectProperty<Vector2> position;
    EffectProperty<Vector2> size;
    EffectProperty<float> radius;
    EffectProperty<float> noise_strength;


    SurfaceEffect(
        const Vector2& resolution,
        const Vector2& position,
        const Vector2& size,
        const float radius,
        const float noise_strength
    );


    void update() noexcept override;


    Texture* target_texture() noexcept override { return &background.value; }
    Vector2* target_texture_resolution() noexcept override { return &resolution.value; }
};