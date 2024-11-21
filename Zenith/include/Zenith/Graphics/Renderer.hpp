/**
 * @file Renderer.hpp
 * @brief Defines the `Renderer` class for managing the rendering process of drawable objects.
 */

#pragma once

#include <SFML/Graphics.hpp>

#include "Zenith/Graphics/CustomPrimitiveRenderer.hpp"
#include "Zenith/Graphics/PrimitiveRenderer.hpp"
#include "Zenith/Graphics/SfmlPrimitiveRenderer.hpp"
#include "Zenith/Utility/Utility.hpp"

namespace zth {

class Drawable;
class Sprite;
class VertexArray;

/**
 * @enum PrimitiveRendererType
 * @brief Specifies the type of primitive renderer to use.
 */
enum class PrimitiveRendererType
{
    SfmlPrimitiveRenderer,   ///< Use the SFML-based primitive renderer.
    CustomPrimitiveRenderer, ///< Use a custom primitive renderer.
};

/**
 * @class Renderer
 * @brief A class that manages the rendering of drawable objects.
 *
 * The `Renderer` class is responsible for drawing `Drawable` objects, `Sprite` objects, and `VertexArray` objects
 * to the given SFML render target. It also allows for the selection of different types of primitive renderers.
 *
 * @note The class can switch between using the SFML-based `SfmlPrimitiveRenderer` and a custom
 * `CustomPrimitiveRenderer`.
 */
class Renderer
{
public:
    /**
     * @brief Constructs a Renderer with a specified render target.
     * @param render_target The render target (e.g., a window or texture) on which the rendering is done.
     */
    explicit Renderer(sf::RenderTarget& render_target) : _render_target(render_target) {}

    /**
     * @brief Destructor for the Renderer class.
     */
    ~Renderer() = default;

    // Delete copy and move constructors and assignment operators
    ZTH_NO_COPY_NO_MOVE(Renderer)

    /**
     * @brief Draws a `Drawable` object to the render target.
     * @param drawable The object to be drawn.
     */
    void draw(const Drawable& drawable);

    /**
     * @brief Draws a `Sprite` object to the render target.
     * @param sprite The sprite to be drawn.
     */
    void draw_sprite(const Sprite& sprite) const;

    /**
     * @brief Draws a `VertexArray` object to the render target.
     * @param vertex_array The vertex array to be drawn.
     */
    void draw_vertex_array(const VertexArray& vertex_array) const;

    /**
     * @brief Accesses the currently selected primitive renderer.
     * @return A reference to the current primitive renderer.
     */
    auto& primitive_renderer() { return _selected_primitive_renderer; }

    /**
     * @brief Sets the type of primitive renderer to use.
     * @param primitive_renderer_type The type of the primitive renderer.
     */
    void set_primitive_renderer_type(PrimitiveRendererType primitive_renderer_type);

    /**
     * @brief Gets the currently selected primitive renderer type.
     * @return The current primitive renderer type.
     */
    PrimitiveRendererType get_primitive_renderer_type() const;

private:
    sf::RenderTarget& _render_target;                                     ///< The render target for drawing.
    SfmlPrimitiveRenderer _sfml_primitive_renderer{ _render_target };     ///< The SFML-based primitive renderer.
    CustomPrimitiveRenderer _custom_primitive_renderer{ _render_target }; ///< The custom primitive renderer.
    PrimitiveRenderer* _selected_primitive_renderer =
        &_sfml_primitive_renderer; ///< The currently selected primitive renderer.
};

} // namespace zth
