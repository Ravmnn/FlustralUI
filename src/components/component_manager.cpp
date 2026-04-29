#include <flustral/components/component_manager.hpp>

#include <flustral/rendering/renderer.hpp>




void ComponentManager::update() noexcept
{
    for (auto& component : components)
        component->update();
}




void ComponentManager::draw() noexcept
{
    for (auto& component : components)
        component->draw();
}