#pragma once

#include <flustral/rendering/effects/effect_pass.hpp>
#include <flustral/rendering/effects/native/horizontal_blur_effect.hpp>
#include <flustral/rendering/effects/native/vertical_blur_effect.hpp>




class GaussianBlurEffectPass : EffectPass
{
private:
    HorizontalBlurEffect* horizontal_blur_;
    VerticalBlurEffect* vertical_blur_;

    EffectPass horizontal_blur_pass_;
    EffectPass vertical_blur_pass_;


public:
    using EffectPass::down_sample_factor;

    int samples;
    float sigma;


    GaussianBlurEffectPass(const int samples, const float sigma) noexcept;


    void update() noexcept override;


    ScopedRenderTexture apply(const Texture& texture) noexcept override;
};