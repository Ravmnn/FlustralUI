#pragma once

#include <vector>
#include <memory>
#include <concepts>

#include <flustral/components/component.hpp>
#include <flustral/rendering/renderer.hpp>
#include <flustral/rendering/scoped_render_texture.hpp>




class ComponentManager : public Updateable, public Drawable
{
public:
    std::vector<std::unique_ptr<Component>> components;
    std::unique_ptr<Renderer> renderer;


    explicit ComponentManager(std::unique_ptr<Renderer> renderer) noexcept;
    virtual ~ComponentManager() = default;


    void update() noexcept override;
    void draw() noexcept override;

    RenderTexture draw_and_get() noexcept;


    template <typename T>
        requires std::derived_from<T, Component>
    T* add_component(T* const component) noexcept
    {
        components.push_back(std::unique_ptr<Component>(component));
    }


    template <typename T, typename... Args>
        requires std::derived_from<T, Component>
    T* add_component(Args&&... args) noexcept
    {
        components.push_back(std::make_unique<T>(args...));
        return dynamic_cast<T*>((components.end() - 1)->get());
    }
};