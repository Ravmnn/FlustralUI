#pragma once

#include <flustral/rendering/effects/effect.hpp>
#include <flustral/rendering/effects/effect_property.hpp>




class BlurEffect : public Effect
{
public:
    EffectProperty<Vector2> resolution;
    EffectProperty<int> samples;
    EffectProperty<float> sigma;

    EffectProperty<Texture> texture;


    BlurEffect(
        std::unique_ptr<Shader> shader,
        const Vector2& resolution,
        const int samples,
        const float sigma
    );


    void update() noexcept override;
};