/**
 * @file Drawable.hpp
 * @brief Defines an interface for drawable objects.
 */

#pragma once

namespace zth {

class Renderer;

/**
 * @class Drawable
 * @brief An interface for objects that can be rendered by a `Renderer`.
 *
 * The `Drawable` class defines a common interface for objects that can be drawn on a rendering target. 
 * Any object that implements this interface can be rendered by the `Renderer` class.
 */
class Drawable
{
public:
    /**
     * @brief Virtual destructor to allow proper cleanup of derived classes.
     */
    virtual ~Drawable() = default;

    /**
     * @brief Draws the object using the provided renderer.
     * @param renderer The renderer to use for drawing.
     *
     * This is a pure virtual method, which must be implemented by any derived class.
     * It will define how the object is drawn.
     */
    virtual void draw(Renderer& renderer) const = 0;
};

} // namespace zth
