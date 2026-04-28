#pragma once

#include <flustral/rendering/effects/effect_pass.hpp>
#include <flustral/rendering/effects/native/horizontal_blur_effect.hpp>
#include <flustral/rendering/effects/native/vertical_blur_effect.hpp>




class GaussianBlurEffectPass : EffectPass
{
private:
    HorizontalBlurEffect* _horizontal_blur;
    VerticalBlurEffect* _vertical_blur;

    EffectPass _horizontal_blur_pass;
    EffectPass _vertical_blur_pass;


public:
    using EffectPass::down_sample_factor;

    int samples;
    float sigma;


    GaussianBlurEffectPass(const int samples, const float sigma) noexcept;


    void update() noexcept override;


    ScopedRenderTexture apply(const Texture& texture) noexcept override;
};