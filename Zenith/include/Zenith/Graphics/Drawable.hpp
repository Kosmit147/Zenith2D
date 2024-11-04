#pragma once

namespace zth {

class PrimitiveRenderer;

class Drawable
{
public:
    virtual ~Drawable() = default;

    virtual void draw(PrimitiveRenderer& renderer) const = 0;
};

} // namespace zth
