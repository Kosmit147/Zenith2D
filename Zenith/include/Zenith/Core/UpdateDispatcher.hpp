#pragma once

#include <vector>

#include "Zenith/Core/Updatable.hpp"

namespace zth {

class UpdateDispatcher
{
public:
    void register_updatable(Updatable& updatable);
    void deregister_updatable(const Updatable& updatable);
    void dispatch(double delta_time) const;

private:
    std::vector<Updatable*> _updatables;
};

} // namespace zth
