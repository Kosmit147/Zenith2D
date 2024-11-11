#pragma once

namespace zth {

class Updatable
{
public:
    virtual ~Updatable() = default;

    virtual void on_update() = 0;
};

} // namespace zth
