#pragma once

#include <vector>

#include "Zenith/Core/Updatable.hpp"

namespace zth {

class Updater
{
public:
    void register_updatable(Updatable& updatable);
    void deregister_updatable(const Updatable& updatable);
    void update(double delta_time) const;

private:
    std::vector<Updatable*> _updatables;
};

} // namespace zth
