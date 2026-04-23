#pragma once

#include <flustral/components/component.hpp>




class RectangleComponent : public Component
{
public:
    Vector2 size;
    float radius;


    RectangleComponent(const Vector2& position, const Vector2& size, const float radius) noexcept;


    void draw() noexcept override;


    Rectangle geometry() const noexcept { return Rectangle { .x = position.x, .y = position.y, .width = size.x, .height = size.y }; }
};