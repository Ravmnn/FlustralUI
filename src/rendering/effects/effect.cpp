#include <flustral/rendering/effects/effect.hpp>





void Effect::enable(const std::optional<Texture>& texture) noexcept
{
    BeginShaderMode(*_shader);

    if (!texture)
        return;

    *target_texture() = *texture;
    *target_texture_resolution() = { (float)texture->width, (float)texture->height };
}


void Effect::disable() const noexcept
{
    EndShaderMode();
}