/**
 * @file VertexArray.hpp
 * @brief Defines the `VertexArray` class for managing and drawing a collection of vertices with a specified primitive type.
 * 
 * This file provides the `VertexArray` class, which is used to store and manage a collection of vertices 
 * for rendering. It supports various primitive types (points, lines, triangles, etc.) and can be drawn with 
 * a `Renderer`.
 */

#pragma once

#include <SFML/Graphics/VertexArray.hpp>

#include <span>

#include "Zenith/Core/Typedefs.hpp"
#include "Zenith/Graphics/Vertex.hpp"
#include "Zenith/Graphics/Drawable.hpp"
#include "Zenith/Math/Geometry.hpp"

namespace zth {

/**
 * @enum PrimitiveType
 * @brief Represents different types of primitives that can be drawn.
 * 
 * `PrimitiveType` specifies the shape to be rendered using the vertices. The following types are supported:
 * - `Points`: Individual points.
 * - `Lines`: Separate lines between each pair of vertices.
 * - `LineStrip`: A continuous line connecting all vertices.
 * - `Triangles`: A set of triangles.
 * - `TriangleStrip`: A connected set of triangles.
 * - `TriangleFan`: A fan of triangles.
 */
enum class PrimitiveType : u8
{
    Points, ///< Individual points.
    Lines, ///< Separate lines between each pair of vertices.
    LineStrip, ///< A continuous line connecting all vertices.
    Triangles, ///< A set of triangles.
    TriangleStrip, ///< A connected set of triangles.
    TriangleFan, ///< A fan of triangles.
};

/**
 * @brief Converts an SFML `sf::PrimitiveType` to `PrimitiveType`.
 * 
 * @param primitive_type The SFML primitive type.
 * @return The corresponding `PrimitiveType`.
 */
PrimitiveType to_primitive_type(sf::PrimitiveType primitive_type);

/**
 * @brief Converts a `PrimitiveType` to SFML's `sf::PrimitiveType`.
 * 
 * @param primitive_type The `PrimitiveType` to convert.
 * @return The corresponding SFML primitive type.
 */
sf::PrimitiveType to_sf_primitive_type(PrimitiveType primitive_type);

/**
 * @brief Converts a `PrimitiveType` to a string representation.
 * 
 * @param primitive_type The `PrimitiveType` to convert.
 * @return A C-style string representation of the primitive type.
 */
const char* to_string(PrimitiveType primitive_type);

/**
 * @class VertexArray
 * @brief Manages and draws a collection of vertices with a specified primitive type.
 * 
 * The `VertexArray` class stores vertices and allows for drawing them as various types of primitives such as 
 * points, lines, triangles, etc. It also provides methods for modifying and querying the vertices and their 
 * attributes.
 */
class VertexArray : public Drawable
{
public:
    /**
     * @brief Default constructor, initializes the `VertexArray` with a default primitive type (`Points`).
     */
    explicit VertexArray() = default;

    /**
     * @brief Initializes the `VertexArray` with a specified primitive type.
     * 
     * @param primitive_type The primitive type to set for the `VertexArray`.
     */
    explicit VertexArray(PrimitiveType primitive_type) : _vertex_array(to_sf_primitive_type(primitive_type)) {}

    /**
     * @brief Draws the `VertexArray` using the given `Renderer`.
     * 
     * This method is part of the `Drawable` interface. It submits the vertex data to the renderer.
     * 
     * @param renderer The `Renderer` used to draw the `VertexArray`.
     */
    void draw(Renderer& renderer) const override;

    /**
     * @brief Sets the primitive type of the `VertexArray`.
     * 
     * This changes the way the vertices are interpreted (e.g., points, lines, triangles, etc.).
     * 
     * @param primitive_type The new `PrimitiveType` for the `VertexArray`.
     */
    void set_primitive_type(PrimitiveType primitive_type);

    /**
     * @brief Appends a single `Vertex` to the `VertexArray`.
     * 
     * @param vertex The `Vertex` to append.
     */
    void append(const Vertex& vertex);

    /**
     * @brief Appends a range of vertices to the `VertexArray`.
     * 
     * @param vertices A span of `Vertex` objects to append.
     */
    void append(std::span<const Vertex> vertices);

    /**
     * @brief Clears all vertices from the `VertexArray`.
     */
    void clear();

    /**
     * @brief Retrieves the primitive type of the `VertexArray`.
     * 
     * @return The current `PrimitiveType` of the `VertexArray`.
     */
    auto primitive_type() const;

    /**
     * @brief Retrieves the number of vertices in the `VertexArray`.
     * 
     * @return The vertex count.
     */
    auto vertex_count() const;

    /**
     * @brief Retrieves the bounding rectangle of the `VertexArray`.
     * 
     * @return The bounding rectangle of the `VertexArray`.
     */
    auto bounds() const;

    friend class Renderer; ///< Allows `Renderer` class to access private members of `VertexArray`.
    friend class SfmlPrimitiveRenderer; ///< Allows `SfmlPrimitiveRenderer` class to access private members of `VertexArray`.
    friend class CustomPrimitiveRenderer; ///< Allows `CustomPrimitiveRenderer` class to access private members of `VertexArray`.

private:
    sf::VertexArray _vertex_array; ///< The underlying SFML `VertexArray` for rendering.
};

} // namespace zth
