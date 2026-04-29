#include <flustral/scene.hpp>

#include <flustral/rendering/effects/native/horizontal_blur_effect.hpp>
#include <flustral/rendering/effects/native/vertical_blur_effect.hpp>
#include <flustral/texture_sample.hpp>




Scene::Scene() noexcept
    : _blur_pass(2, 1)
{
    _blur_pass.down_sample_factor = 6;
    _renderer.use_buffer_texture = false;
}




void Scene::update_all() noexcept
{
    for (auto& layer : layers)
        layer->update();
}




void Scene::draw_all() noexcept
{
    // TODO: surfaces cannot exist on the background layer

    if (layers.empty())
        return;

    add_to_unload_list(_rendered_layers.background = get_first_layer_texture());
    draw_layers();

    draw_final_texture_to_window();

    unload_loaded_textures();
}


RenderTexture Scene::get_first_layer_texture() noexcept
{
    TextureRenderer renderer(_renderer.resolution());

    renderer.begin_render();
    layers.front()->draw();
    renderer.end_render();

    return renderer.release_contents();
}


void Scene::draw_layers() noexcept
{
    for (size_t i = 1; i < layers.size(); i++)
    {
        update_blurred_background();
        draw_components(*layers[i]);
    }
}


void Scene::draw_components(const SceneLayer& layer) noexcept
{
    for (auto& component : layer.components)
    {
        SurfaceComponent* surface = dynamic_cast<SurfaceComponent*>(component.get());
        surface->rendered_layers = _rendered_layers;

        _rendered_layers.background = surface->render();
        add_to_unload_list(_rendered_layers.background);
    }
}


void Scene::update_blurred_background() noexcept
{
    const RenderTexture blurred_background = _blur_pass.apply(_rendered_layers.background.texture).release();
    _rendered_layers.blurred_background = blurred_background;
    add_to_unload_list(blurred_background);
}


void Scene::draw_final_texture_to_window() noexcept
{
    _renderer.begin_render();
    _renderer.draw_y_inverted_texture(_rendered_layers.background.texture);
    _renderer.end_render();
}


void Scene::unload_loaded_textures() noexcept
{
    for (const auto& texture : _unload_list)
        UnloadRenderTexture(texture);

    _unload_list.clear();
}