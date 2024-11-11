#pragma once

#include <SFML/Graphics.hpp>

#include "Zenith/Graphics/CustomPrimitiveRenderer.hpp"
#include "Zenith/Graphics/PrimitiveRenderer.hpp"
#include "Zenith/Graphics/SfmlPrimitiveRenderer.hpp"
#include "Zenith/Utility/Utility.hpp"

namespace zth {

class Drawable;
class Sprite;

enum class PrimitiveRendererType
{
    SfmlPrimitiveRenderer,
    CustomPrimitiveRenderer,
};

class Renderer
{
public:
    explicit Renderer(sf::RenderTarget& render_target) : _render_target(render_target) {}
    ~Renderer() = default;
    ZTH_NO_COPY_NO_MOVE(Renderer)

    void draw(const Drawable& drawable);
    void draw_sprite(const Sprite& sprite) const;

    auto& primitive_renderer() { return _selected_primitive_renderer; }
    void set_primitive_renderer_type(PrimitiveRendererType primitive_renderer_type);
    PrimitiveRendererType get_primitive_renderer_type() const;

private:
    sf::RenderTarget& _render_target;
    SfmlPrimitiveRenderer _sfml_primitive_renderer{ _render_target };
    CustomPrimitiveRenderer _custom_primitive_renderer{ _render_target };
    PrimitiveRenderer* _selected_primitive_renderer = &_sfml_primitive_renderer;
};

} // namespace zth
