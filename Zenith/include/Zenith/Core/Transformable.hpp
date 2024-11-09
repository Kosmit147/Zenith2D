#pragma once

#include "Zenith/Math/Vec2.hpp"

namespace zth {

class Transformable2D
{
public:
    virtual ~Transformable2D() = default;

    virtual void translate(const Vec2f& translation) = 0;
    virtual void rotate(const float& angle, const Vec2f& pivot_point) = 0;
    virtual void scale(const float& factor, const Vec2f& scaling_point) = 0;
};

} // namespace zth
