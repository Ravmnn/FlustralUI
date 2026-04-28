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
    EffectProperty<float> border_width;
    EffectProperty<float> ior;
    EffectProperty<float> strength;
    EffectProperty<float> lens_strength;
    EffectProperty<float> noise_strength;

    EffectProperty<float> chromatic_green;
    EffectProperty<float> chromatic_blue;

    EffectProperty<float> fresnel_power;
    EffectProperty<float> fresnel_strength;

    EffectProperty<Vector3> tint;
    EffectProperty<float> tint_strength;


    SurfaceEffect(
        const Vector2& resolution,
        const Vector2& position,
        const Vector2& size,
        const float radius,
        const float border_width,
        const float ior,
        const float strength,
        const float lens_strength,
        const float noise_strength,
        const float chromatic_green,
        const float chromatic_blue,
        const float fresnel_power,
        const float fresnel_strength,
        const Vector3& tint,
        const float tint_strength
    );


    void update() noexcept override;


    Texture* target_texture() noexcept override { return &background.value; }
    Vector2* target_texture_resolution() noexcept override { return &resolution.value; }
};