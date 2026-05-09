/**
 * @file Shape.hpp
 * @brief Declares the Shape class, a base class for drawable 2D shapes with transformations and color.
 */

#pragma once

#include "Zenith/Core/Transformable.hpp"
#include "Zenith/Graphics/Color.hpp"
#include "Zenith/Graphics/Drawable.hpp"
#include "Zenith/Utility/Utility.hpp"

namespace zth {

/**
 * @class Shape
 * @brief A base class for drawable 2D shapes with transformation and color properties.
 *
 * The Shape class provides a common interface for all drawable shapes, enabling transformations
 * (such as translation, rotation, and scaling) and color customization. It inherits from
 * `Drawable` to support rendering and `Transformable2D` for geometric transformations.
 */
class Shape : public Drawable, public Transformable2D
{
public:
    /// The color of the shape (default is white).
    Color color = Color::white;

public:
    /**
     * @brief Default constructor for Shape.
     */
    explicit Shape() = default;

    /**
     * @brief Constructs a Shape with a specified color.
     * @param color The color to assign to the shape.
     */
    explicit Shape(const Color& color) : color(color) {}

    /// Default copy and move constructors and assignments.
    ZTH_DEFAULT_COPY_DEFAULT_MOVE(Shape)

    /**
     * @brief Virtual destructor for Shape.
     */
    ~Shape() override = default;
};

} // namespace zth
