#include <flustral/rendering/effects/native/gaussian_blur_effect_pass.hpp>




GaussianBlurEffectPass::GaussianBlurEffectPass(const int samples, const float sigma) noexcept
    : EffectPass(*_horizontal_blur), samples(samples), sigma(sigma),
        _horizontal_blur(new HorizontalBlurEffect(samples, sigma)),
        _vertical_blur(new VerticalBlurEffect(samples, sigma)),
        _horizontal_blur_pass(*_horizontal_blur),
        _vertical_blur_pass(*_vertical_blur)
{}




void GaussianBlurEffectPass::update() noexcept
{
    _horizontal_blur_pass.down_sample_factor = _vertical_blur_pass.down_sample_factor = down_sample_factor;
    _horizontal_blur->samples.value = _vertical_blur->samples.value = samples;
    _horizontal_blur->sigma.value = _vertical_blur->sigma.value = sigma;
}




RenderTexture GaussianBlurEffectPass::apply(const Texture& texture) noexcept
{
    update();

    const RenderTexture horizontal_blurred = _horizontal_blur_pass.apply(texture);
    const RenderTexture vertical_blurred = _vertical_blur_pass.apply(horizontal_blurred.texture);

    UnloadRenderTexture(horizontal_blurred);

    return vertical_blurred;
}