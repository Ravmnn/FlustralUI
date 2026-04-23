#include <flustral/spring.hpp>

#include <raymath.h>




Spring::Spring(const Vector2& position, const float speed, const float damping) noexcept
    : _target(position), _velocity({}), position(position), speed(speed), damping(damping)
{}




void Spring::update() noexcept
{
    update_spring_motion();
}


void Spring::update_spring_motion() noexcept
{
    const float dt = GetFrameTime();

    const float omega = speed;
    const float zeta = damping;

    const float omega_squared = omega * omega;
    const float dt_omega_squared = dt * omega_squared;
    const float dt2_omega_squared = dt * dt_omega_squared;
    const float f = 1.0f + 2.0f * dt * omega * zeta;
    const float inverse_determinant = 1.0f / (f + dt2_omega_squared);

    const Vector2 current_position = position;
    const Vector2 current_velocity = _velocity;

    const Vector2 new_position = (current_position * f + current_velocity * dt + _target * dt2_omega_squared) * inverse_determinant;
    const Vector2 new_velocity = (current_velocity + (_target - current_position) * dt_omega_squared) * inverse_determinant;

    position = new_position;
    _velocity = new_velocity;
}