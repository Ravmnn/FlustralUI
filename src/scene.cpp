#include <flustral/scene.hpp>

#include <optional>
#include <queue>

#include <flustral/drawable.hpp>
#include <flustral/components/surface.hpp>
#include <flustral/rendering/effects/native/horizontal_blur_effect.hpp>
#include <flustral/rendering/effects/native/vertical_blur_effect.hpp>
#include <flustral/texture_sample.hpp>




Scene::Scene() noexcept
    : _blur_pass(2, 1), _window_renderer()
{
    _blur_pass.down_sample_factor = 6;
    _window_renderer.use_buffer_texture = false;
}




void Scene::update() noexcept
{
    for (auto& layer : layers)
        layer->update();
}




void Scene::draw() noexcept
{
    // TODO: surfaces cannot exist on the background layer

    std::optional<RenderTexture> background_texture;
    std::vector<RenderTexture> unload_list;

    for (auto& layer : layers)
    {
        if (!background_texture)
        {
            background_texture = layer->draw_and_get();
            continue;
        }

        ScopedRenderTexture blurred_background_texture = _blur_pass.apply(background_texture.value().texture);

        for (auto& component : layer->components)
        {
            SurfaceComponent* surface = dynamic_cast<SurfaceComponent*>(component.get());
            SurfaceEffect* effect = dynamic_cast<SurfaceEffect*>(&surface->effect());

            effect->background.value = background_texture.value().texture;
            effect->blurred_background.value = blurred_background_texture;

            background_texture = EffectPass(*effect).apply(background_texture.value().texture).release();
            unload_list.push_back(background_texture.value());
        }
    }


    _window_renderer.begin_render();
    TextureRenderer::draw_y_inverted_texture(background_texture.value().texture);
    _window_renderer.end_render();


    for (const auto& texture : unload_list)
        UnloadRenderTexture(texture);

    unload_list.clear();
}