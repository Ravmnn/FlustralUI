#include <flustral/rendering/effects/native/blur_effect.hpp>




BlurEffect::BlurEffect(
    std::unique_ptr<Shader> shader,
    const Vector2& resolution,
    const int samples,
    const float sigma
) : Effect(std::move(shader)),

    resolution(EffectProperty<Vector2>(*this->shader(), "u_resolution", resolution)),
    samples(EffectProperty<int>(*this->shader(), "u_samples", samples)),
    sigma(EffectProperty<float>(*this->shader(), "u_sigma", sigma)),
    texture(EffectProperty<Texture>(*this->shader(), "u_texture", {}))
{}




void BlurEffect::update() noexcept
{
    texture.update();
    resolution.update();
    samples.update();
    sigma.update();
}