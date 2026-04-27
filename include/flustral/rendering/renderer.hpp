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
};