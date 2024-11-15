#include "Zenith/Core/Updater.hpp"

#include "Zenith/Core/Updatable.hpp"

namespace zth {

void Updater::register_updatable(Updatable& updatable)
{
    _updatables.push_back(&updatable);
}

void Updater::deregister_updatable(const Updatable& updatable)
{
    std::erase(_updatables, &updatable);
}

void Updater::update() const
{
    // TODO:
    // modifying updatables vector during iterating over updatables will invalidate the iterators
    // we should probably collect all the updatables into a vector before iterating over
    // them and calling on_update

    for (auto updatable : _updatables)
        updatable->on_update();
}

} // namespace zth
