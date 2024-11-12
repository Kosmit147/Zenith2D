#pragma once

#include <SFML/Graphics/VertexArray.hpp>

#include <span>

#include "Zenith/Core/Typedefs.hpp"
#include "Zenith/Graphics/Vertex.hpp"
#include "Zenith/Graphics/Drawable.hpp"
#include "Zenith/Math/Geometry.hpp"

namespace zth {

enum class PrimitiveType : u8
{
    Points,
    Lines,
    LineStrip,
    Triangles,
    TriangleStrip,
    TriangleFan,
};

PrimitiveType to_primitive_type(sf::PrimitiveType primitive_type);
sf::PrimitiveType to_sf_primitive_type(PrimitiveType primitive_type);
const char* to_string(PrimitiveType primitive_type);

class VertexArray : public Drawable
{
public:
    explicit VertexArray() = default;
    explicit VertexArray(PrimitiveType primitive_type) : _vertex_array(to_sf_primitive_type(primitive_type)) {}

    void draw(Renderer& renderer) const override;

    void set_primitive_type(PrimitiveType primitive_type)
    {
        _vertex_array.setPrimitiveType(to_sf_primitive_type(primitive_type));
    }

    void append(const Vertex& vertex) { _vertex_array.append(static_cast<sf::Vertex>(vertex)); }

    void append(std::span<const Vertex> vertices)
    {
        for (const auto& vertex : vertices)
            append(vertex);
    }

    void clear() { _vertex_array.clear(); }

    auto primitive_type() const { return to_primitive_type(_vertex_array.getPrimitiveType()); }
    auto vertex_count() const { return _vertex_array.getVertexCount(); }
    auto bounds() const { return Rect::from_sf_rect(_vertex_array.getBounds()); }

    friend class Renderer;
    friend class SfmlPrimitiveRenderer;
    friend class CustomPrimitiveRenderer;

private:
    sf::VertexArray _vertex_array{};
};

} // namespace zth
