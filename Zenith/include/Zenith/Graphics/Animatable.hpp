/**
 * @file Animatable.hpp
 * @brief Declares the Animatable interface for objects that support animation.
 */

#pragma once

namespace zth {

/**
 * @class Animatable
 * @brief An interface for objects that can be animated.
 *
 * The Animatable interface defines a contract for objects that can have animations applied to them.
 * Classes implementing this interface must define the `animate()` method, which will be responsible
 * for handling the animation logic.
 */
class Animatable
{
public:
    /**
     * @brief Virtual destructor for Animatable.
     */
    virtual ~Animatable() = default;

    /**
     * @brief Virtual method for animating the object.
     *
     * This method should be implemented by derived classes to perform the necessary steps
     * to animate the object.
     */
    virtual void animate() = 0;
};

} // namespace zth
