#pragma once

#include <raylib.h>




class Renderer
{
public:
    Color clear_color = BLACK;


    virtual ~Renderer() = default;


    virtual void begin_render() = 0;
    virtual void end_render() = 0;


    virtual RenderTexture contents() const noexcept = 0;


    virtual Vector2 resolution() const noexcept
    {
        const RenderTexture render_texture = contents();
        const Vector2 resolution = { render_texture.texture.width, render_texture.texture.height };

        return resolution;
    }
};