#pragma once

#include <flustral/components/component.hpp>
#include <flustral/rendering/effects/native/surface_effect.hpp>




class SurfaceComponent : public Component
{
protected:
    SurfaceEffect _effect;


public:
    Vector2 size;
    float radius;


    SurfaceComponent(const Vector2& position, const Vector2& size, const float radius) noexcept;


    void update() noexcept override;
    void draw() noexcept override {}


    SurfaceEffect& effect() noexcept { return _effect; }
    Rectangle geometry() const noexcept { return Rectangle { .x = position.x, .y = position.y, .width = size.x, .height = size.y }; }
};