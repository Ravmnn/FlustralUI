#include <flustral/components/surface.hpp>

#include <raymath.h>




SurfaceComponent::SurfaceComponent(const Vector2& position, const Vector2& size, const float radius) noexcept
    : Component(position), size(size), radius(radius),
        _effect(
            Vector2{ (float)GetScreenWidth(), (float)GetScreenHeight() },
            position,
            size,
            radius,
            20,
            1.5,
            0.06,
            0,
            2,
            1.02,
            1.04,
            3,
            0.12,
            {0.88, 0.93, 0.97},
            1
        )
{}




void SurfaceComponent::update() noexcept
{
    Component::update();

    _effect.position.value = position / _effect.resolution.value;
    _effect.size.value = size;
    _effect.radius.value = radius;
}