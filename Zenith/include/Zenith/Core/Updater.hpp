#pragma once

#include <vector>

namespace zth {

class Updatable;

class Updater
{
public:
    void register_updatable(Updatable& updatable);
    void deregister_updatable(const Updatable& updatable);
    void update() const;

private:
    std::vector<Updatable*> _updatables;
};

} // namespace zth
