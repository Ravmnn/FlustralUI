#pragma once

#include <memory>
#include <optional>

#include <raylib.h>




class ScopedRenderTexture
{
private:
    std::optional<RenderTexture> _render_texture;


public:
    ScopedRenderTexture(const ScopedRenderTexture&) = delete;
    ScopedRenderTexture& operator=(const ScopedRenderTexture&) = delete;


    explicit ScopedRenderTexture(const Vector2& size) noexcept
        : ScopedRenderTexture(LoadRenderTexture(size.x, size.y)) {}

    explicit ScopedRenderTexture(const RenderTexture& render_texture) noexcept
        : _render_texture(render_texture) { }


    explicit ScopedRenderTexture(ScopedRenderTexture&& other) noexcept { own(other); }


    ScopedRenderTexture& operator=(ScopedRenderTexture&& other) noexcept
    {
        if (&other == this)
            return *this;

        own(other);
        return *this;
    }


    ~ScopedRenderTexture() noexcept
    {
        if (_render_texture)
            UnloadRenderTexture(_render_texture.value());
    }


    operator RenderTexture() const noexcept { return render_texture(); }
    operator Texture() const noexcept { return texture(); }


    const RenderTexture& render_texture() const noexcept { return _render_texture.value(); }
    const Texture& texture() const noexcept { return _render_texture.value().texture; }


    Vector2 size() const noexcept { return { texture().width, texture().height }; }


    RenderTexture release() noexcept
    {
        RenderTexture buffer = _render_texture.value();
        _render_texture.reset();

        return buffer;
    }


private:
    void own(ScopedRenderTexture& other) noexcept
    {
        _render_texture = other._render_texture;
        other._render_texture.reset();
    }
};