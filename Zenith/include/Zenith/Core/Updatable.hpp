/**
 * @file Updatable.hpp
 * @brief Declares the Updatable interface for objects that can be updated each frame.
 */

#pragma once

namespace zth {

/**
 * @class Updatable
 * @brief Interface for objects that require per-frame updates.
 *
 * Classes that inherit from Updatable must implement the on_update method,
 * which is called once per frame to update the object's state.
 */
class Updatable
{
public:
    /**
     * @brief Virtual destructor for Updatable.
     */
    virtual ~Updatable() = default;

    /**
     * @brief Called once per frame to update the object's state.
     */
    virtual void on_update() = 0;
};

} // namespace zth
