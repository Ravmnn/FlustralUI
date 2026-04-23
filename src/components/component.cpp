#include <flustral/components/component.hpp>




Component::Component(const Vector2& position) noexcept
    : Spring(position, DefaultSpringSpeed, DefaultSpringDamping)
{}