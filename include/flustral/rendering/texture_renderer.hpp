#pragma once

#include <raylib.h>

#include <flustral/rendering/renderer.hpp>
#include <flustral/rendering/scoped_render_texture.hpp>




class TextureRenderer : public Renderer
{
protected:
    ScopedRenderTexture _render_texture;


public:
    TextureRenderer() noexcept
        : TextureRenderer(GetScreenWidth(), GetScreenHeight()) {}

    explicit TextureRenderer(const unsigned int width, const unsigned int height) noexcept;
    virtual ~TextureRenderer() = default;

    explicit TextureRenderer(const Vector2& size) noexcept
        : TextureRenderer(size.x, size.y) {}



    void begin_render() noexcept override;
    void end_render() noexcept override;


    RenderTexture contents() const noexcept override { return _render_texture; }
    RenderTexture release_contents() noexcept { return _render_texture.release(); }


    static void draw_y_inverted_texture(const Texture& texture) noexcept;
};