#include <flustral/rendering/effects/native/surface_effect.hpp>

#include <flustral/rendering/effects/native/native_shaders.hpp>




SurfaceEffect::SurfaceEffect(
    const Vector2& resolution,
    const Vector2& position,
    const Vector2& size,
    const float radius,
    const float noise_strength
) : Effect(std::make_unique<Shader>(LoadShaderFromMemory(nullptr, NativeShaders::BlurMaskShader))),

    background(EffectProperty<Texture>(*this->shader(), "u_background", {})),
    blurred_background(EffectProperty<Texture>(*this->shader(), "u_blurred_background", {})),
    resolution(EffectProperty<Vector2>(*this->shader(), "u_resolution", resolution)),
    position(EffectProperty<Vector2>(*this->shader(), "u_position", position)),
    size(EffectProperty<Vector2>(*this->shader(), "u_size", size)),
    radius(EffectProperty<float>(*this->shader(), "u_radius", radius)),
    noise_strength(EffectProperty<float>(*this->shader(), "u_noise_strength", noise_strength))
{}




void SurfaceEffect::update() noexcept
{
    background.update();
    blurred_background.update();
    resolution.update();
    position.update();
    size.update();
    radius.update();
    noise_strength.update();
}