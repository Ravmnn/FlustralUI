#pragma once

#include <raylib.h>

#include <flustral/updateable.hpp>




class Spring : public Updateable
{
private:
    Vector2 _target;
    Vector2 _velocity;


public:
    Vector2 position;

    float speed;
    float damping;


    Spring(const Vector2& position, const float speed, const float damping) noexcept;


    void update() noexcept override;


    void set_motion_target(const Vector2& position) noexcept { _target = position; }


private:
    void update_spring_motion() noexcept;
};