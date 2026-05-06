#include <flustral/scene.hpp>

#include <flustral/rendering/effects/native/horizontal_blur_effect.hpp>
#include <flustral/rendering/effects/native/vertical_blur_effect.hpp>
#include <flustral/texture_sample.hpp>




Scene::Scene() noexcept
    : blur_pass_(2, 1)
{
    blur_pass_.down_sample_factor = 6;
    renderer_.use_buffer_texture = false;
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

    add_to_unload_list(rendered_layers_.background = get_first_layer_texture());
    draw_layers();

    draw_final_texture_to_window();

    unload_loaded_textures();
}


RenderTexture Scene::get_first_layer_texture() noexcept
{
    TextureRenderer renderer(renderer_.resolution());

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
        surface->rendered_layers = rendered_layers_;

        rendered_layers_.background = surface->render();
        add_to_unload_list(rendered_layers_.background);
    }
}


void Scene::update_blurred_background() noexcept
{
    const RenderTexture blurred_background = blur_pass_.apply(rendered_layers_.background.texture).release();
    rendered_layers_.blurred_background = blurred_background;
    add_to_unload_list(blurred_background);
}


void Scene::draw_final_texture_to_window() noexcept
{
    renderer_.begin_render();
    renderer_.draw_y_inverted_texture(rendered_layers_.background.texture);
    renderer_.end_render();
}


void Scene::unload_loaded_textures() noexcept
{
    for (const auto& texture : unload_list_)
        UnloadRenderTexture(texture);

    unload_list_.clear();
}