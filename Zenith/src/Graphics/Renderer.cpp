#include "Zenith/Graphics/Renderer.hpp"

#include "Zenith/Graphics/Drawable.hpp"
#include "Zenith/Graphics/Sprite.hpp"

namespace zth {

void Renderer::draw_sprite(const Sprite& sprite) const
{
    _render_target.draw(sprite._sprite);
}

void Renderer::draw(const Drawable& drawable)
{
    drawable.draw(*this);
}

void Renderer::set_primitive_renderer_type(PrimitiveRendererType primitive_renderer_type)
{
    switch (primitive_renderer_type)
    {
    case PrimitiveRendererType::SfmlPrimitiveRenderer:
        _selected_primitive_renderer = &_sfml_primitive_renderer;
        break;
    case PrimitiveRendererType::CustomPrimitiveRenderer:
        _selected_primitive_renderer = &_custom_primitive_renderer;
        break;
    }
}

PrimitiveRendererType Renderer::get_primitive_renderer_type() const
{
    if (_selected_primitive_renderer == &_sfml_primitive_renderer)
        return PrimitiveRendererType::SfmlPrimitiveRenderer;
    else if (_selected_primitive_renderer == &_custom_primitive_renderer)
        return PrimitiveRendererType::CustomPrimitiveRenderer;

    assert(false);
    std::unreachable();
}

} // namespace zth
