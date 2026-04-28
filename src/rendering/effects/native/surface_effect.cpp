#include <flustral/rendering/effects/native/surface_effect.hpp>

#include <flustral/rendering/effects/native/native_shaders.hpp>




SurfaceEffect::SurfaceEffect(
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
) : Effect(std::make_unique<Shader>(LoadShaderFromMemory(nullptr, NativeShaders::DistortionShader))),

    background(EffectProperty<Texture>(*this->shader(), "u_background", {})),
    blurred_background(EffectProperty<Texture>(*this->shader(), "u_blurred_background", {})),
    resolution(EffectProperty<Vector2>(*this->shader(), "u_resolution", resolution)),
    position(EffectProperty<Vector2>(*this->shader(), "u_position", position)),
    size(EffectProperty<Vector2>(*this->shader(), "u_size", size)),
    radius(EffectProperty<float>(*this->shader(), "u_radius", radius)),
    border_width(EffectProperty<float>(*this->shader(), "u_border_width", border_width)),
    ior(EffectProperty<float>(*this->shader(), "u_ior", ior)),
    strength(EffectProperty<float>(*this->shader(), "u_strength", strength)),
    lens_strength(EffectProperty<float>(*this->shader(), "u_lens_strength", lens_strength)),
    noise_strength(EffectProperty<float>(*this->shader(), "u_noise_strength", noise_strength)),
    chromatic_green(EffectProperty<float>(*this->shader(), "u_chromatic_green", chromatic_green)),
    chromatic_blue(EffectProperty<float>(*this->shader(), "u_chromatic_blue", chromatic_blue)),
    fresnel_power(EffectProperty<float>(*this->shader(), "u_fresnel_power", fresnel_power)),
    fresnel_strength(EffectProperty<float>(*this->shader(), "u_fresnel_strength", fresnel_strength)),
    tint(EffectProperty<Vector3>(*this->shader(), "u_tint", tint)),
    tint_strength(EffectProperty<float>(*this->shader(), "u_tint_strength", tint_strength))
{}




void SurfaceEffect::update() noexcept
{
    background.update();
    blurred_background.update();
    resolution.update();
    position.update();
    size.update();
    radius.update();
    border_width.update();
    ior.update();
    strength.update();
    lens_strength.update();
    noise_strength.update();
    chromatic_green.update();
    chromatic_blue.update();
    fresnel_power.update();
    fresnel_strength.update();
    tint.update();
    tint_strength.update();
}