#pragma once

namespace zth {

class Updatable
{
public:
    virtual ~Updatable() = default;

    virtual void on_update(double delta_time) = 0;
};

} // namespace zth
