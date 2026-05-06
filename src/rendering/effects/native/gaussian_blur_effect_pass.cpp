#include <flustral/rendering/effects/native/gaussian_blur_effect_pass.hpp>




GaussianBlurEffectPass::GaussianBlurEffectPass(const int samples, const float sigma) noexcept
    : EffectPass(*horizontal_blur_), samples(samples), sigma(sigma),
        horizontal_blur_(new HorizontalBlurEffect(samples, sigma)),
        vertical_blur_(new VerticalBlurEffect(samples, sigma)),
        horizontal_blur_pass_(*horizontal_blur_),
        vertical_blur_pass_(*vertical_blur_)
{}




void GaussianBlurEffectPass::update() noexcept
{
    horizontal_blur_pass_.down_sample_factor = vertical_blur_pass_.down_sample_factor = down_sample_factor;
    horizontal_blur_->samples.value = vertical_blur_->samples.value = samples;
    horizontal_blur_->sigma.value = vertical_blur_->sigma.value = sigma;
}




ScopedRenderTexture GaussianBlurEffectPass::apply(const Texture& texture) noexcept
{
    update();

    const ScopedRenderTexture horizontal_blurred = horizontal_blur_pass_.apply(texture);
    ScopedRenderTexture vertical_blurred = vertical_blur_pass_.apply(horizontal_blurred);

    return ScopedRenderTexture(vertical_blurred.release());
}