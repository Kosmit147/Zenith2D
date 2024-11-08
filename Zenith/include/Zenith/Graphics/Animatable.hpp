#pragma once

namespace zth {

class Animatable
{
public:
    virtual ~Animatable() = default;

    virtual void animate() = 0;
};

} // namespace zth
