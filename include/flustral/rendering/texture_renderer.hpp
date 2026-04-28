#pragma once

#include <raylib.h>

#include <flustral/rendering/renderer.hpp>
#include <flustral/rendering/scoped_render_texture.hpp>




class TextureRenderer : public Renderer
{
private:
    ScopedRenderTexture _render_texture;


public:
    TextureRenderer() noexcept
        : TextureRenderer(GetScreenWidth(), GetScreenHeight()) {}

    explicit TextureRenderer(const unsigned int width, const unsigned int height) noexcept;
    virtual ~TextureRenderer() = default;


    void begin_render() noexcept override;
    void end_render() noexcept override;


    RenderTexture contents() const noexcept override { return _render_texture; }


    static void draw_y_inverted_texture(const Texture& texture) noexcept;
};