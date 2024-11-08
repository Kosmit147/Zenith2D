#pragma once

namespace zth {

class Renderer;

class Drawable
{
public:
    virtual ~Drawable() = default;

    virtual void draw(Renderer& renderer) const = 0;
};

} // namespace zth
