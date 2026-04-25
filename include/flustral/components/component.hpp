#pragma once

#include <raylib.h>

#include <flustral/spring.hpp>
#include <flustral/drawable.hpp>




class Component : public Spring, public Drawable
{
public:
    static constexpr float DefaultSpringSpeed = 12.0f;
    static constexpr float DefaultSpringDamping = 0.6f;


    explicit Component(const Vector2& position) noexcept;
};