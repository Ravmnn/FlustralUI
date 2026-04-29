#pragma once

#include <raylib.h>

#include <flustral/components/surface.hpp>
#include <flustral/rendering/effects/native/gaussian_blur_effect_pass.hpp>
#include <flustral/rendering/window_renderer.hpp>
#include <flustral/scene_layer.hpp>




class Scene
{
private:
    GaussianBlurEffectPass _blur_pass;

    WindowRenderer _renderer;
    RenderedLayers _rendered_layers;

    std::vector<RenderTexture> _unload_list;


public:
    std::vector<std::unique_ptr<SceneLayer>> layers;


    Scene() noexcept;


    void update_all() noexcept;
    void draw_all() noexcept;


private:
    RenderTexture get_first_layer_texture() noexcept;

    void draw_layers() noexcept;
    void draw_components(const SceneLayer& layer) noexcept;
    void update_blurred_background() noexcept;

    void draw_final_texture_to_window() noexcept;

    void unload_loaded_textures() noexcept;
    void add_to_unload_list(const RenderTexture& texture) noexcept { _unload_list.push_back(texture); }
};