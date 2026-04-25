#include <flustral/components/component_manager.hpp>




ComponentManager::ComponentManager(std::unique_ptr<Renderer> renderer) noexcept
    : renderer(std::move(renderer))
{}




void ComponentManager::update() noexcept
{
    for (auto& component : components)
        component->update();
}




void ComponentManager::draw() noexcept
{
    renderer->begin_render();

    for (auto& component : components)
        component->draw();

    renderer->end_render();
}


Texture ComponentManager::draw_and_get() noexcept
{
    draw();
    return renderer->contents();
}