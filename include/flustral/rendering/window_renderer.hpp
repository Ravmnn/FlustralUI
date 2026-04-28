#pragma once

#include <raylib.h>

#include <flustral/rendering/texture_renderer.hpp>




class WindowRenderer : public TextureRenderer
{
public:
    bool use_buffer_texture = true;


    WindowRenderer();


    void begin_render() noexcept override;
    void end_render() noexcept override;


private:
    void render_to_window() const noexcept;
};