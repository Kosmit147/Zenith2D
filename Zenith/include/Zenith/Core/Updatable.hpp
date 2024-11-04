#pragma once

namespace zth {

class Updatable
{
public:
    virtual ~Updatable() = default;

    virtual void update(double delta_time) = 0;
};

} // namespace zth
