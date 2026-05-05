#pragma once

#include <flustral/components/component.hpp>
#include <flustral/rendering/renderizable.hpp>
#include <flustral/rendering/effects/native/surface_effect.hpp>




struct RenderedLayers
{
    RenderTexture background;
    RenderTexture blurred_background;


    RenderedLayers() = default;

    RenderedLayers(const RenderTexture& background, const RenderTexture& blurred_background)
        : background(background), blurred_background(blurred_background) {}
};


class SurfaceComponent : public Component, public Renderizable
{
protected:
    SurfaceEffect _effect;


public:
    Vector2 size;
    float radius;

    RenderedLayers rendered_layers;


    SurfaceComponent(const Vector2& position, const Vector2& size, const float radius) noexcept;


    void draw() noexcept override {}
    RenderTexture render() noexcept override;


    SurfaceEffect& effect() noexcept { return _effect; }
    Rectangle geometry() const noexcept { return Rectangle { .x = position().x, .y = position().y, .width = size.x, .height = size.y }; }


private:
    void update_effect_values() noexcept;
};