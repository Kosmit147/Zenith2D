/**
 * @file Updater.hpp
 * @brief Declares the Updater class for managing and updating a collection of Updatable objects.
 */

#pragma once

#include <vector>

namespace zth {

class Updatable;

/**
 * @class Updater
 * @brief Manages a collection of Updatable objects and calls their update functions.
 *
 * The Updater class allows for registering and deregistering Updatable objects,
 * and provides an update method that calls the on_update method of each registered Updatable.
 */
class Updater
{
public:
    /**
     * @brief Registers an Updatable object for updates.
     * @param updatable The Updatable object to register.
     */
    void register_updatable(Updatable& updatable);

    /**
     * @brief Deregisters an Updatable object from updates.
     * @param updatable The Updatable object to deregister.
     */
    void deregister_updatable(const Updatable& updatable);

    /**
     * @brief Calls the on_update method for each registered Updatable.
     */
    void update() const;

private:
    /// Collection of registered Updatable objects.
    std::vector<Updatable*> _updatables;
};

} // namespace zth
