#pragma once

#include "Zenith/Math/Vec2.hpp"

namespace zth {

class Transformable2D
{
public:
    virtual ~Transformable2D() = default;

    virtual void translate(const Vec2f& translation) = 0;
    virtual void rotate(float angle) = 0;
    virtual void scale(const Vec2f& factor) = 0;
};

} // namespace zth
