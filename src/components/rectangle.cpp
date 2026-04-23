#include <flustral/components/rectangle.hpp>




RectangleComponent::RectangleComponent(const Vector2& position, const Vector2& size, const float radius) noexcept
    : Component(position), size(size), radius(radius)
{}




void RectangleComponent::draw() noexcept
{
    DrawRectangleRounded(geometry(), radius, 16, WHITE);
}