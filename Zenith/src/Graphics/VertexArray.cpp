#include "Zenith/Graphics/VertexArray.hpp"

#include "Zenith/Graphics/Renderer.hpp"

namespace zth {

PrimitiveType to_primitive_type(sf::PrimitiveType primitive_type)
{
    switch (primitive_type)
    {
    case sf::PrimitiveType::Points:
        return PrimitiveType::Points;
    case sf::PrimitiveType::Lines:
        return PrimitiveType::Lines;
    case sf::PrimitiveType::LineStrip:
        return PrimitiveType::LineStrip;
    case sf::PrimitiveType::Triangles:
        return PrimitiveType::Triangles;
    case sf::PrimitiveType::TriangleStrip:
        return PrimitiveType::TriangleStrip;
    case sf::PrimitiveType::TriangleFan:
        return PrimitiveType::TriangleFan;
    }

    assert(false);
    std::unreachable();
}

sf::PrimitiveType to_sf_primitive_type(PrimitiveType primitive_type)
{
    switch (primitive_type)
    {
    case PrimitiveType::Points:
        return sf::PrimitiveType::Points;
    case PrimitiveType::Lines:
        return sf::PrimitiveType::Lines;
    case PrimitiveType::LineStrip:
        return sf::PrimitiveType::LineStrip;
    case PrimitiveType::Triangles:
        return sf::PrimitiveType::Triangles;
    case PrimitiveType::TriangleStrip:
        return sf::PrimitiveType::TriangleStrip;
    case PrimitiveType::TriangleFan:
        return sf::PrimitiveType::TriangleFan;
    }

    assert(false);
    std::unreachable();
}

const char* to_string(PrimitiveType primitive_type)
{
    switch (primitive_type)
    {
        using enum PrimitiveType;
    case Points:
        return "Points";
    case Lines:
        return "Lines";
    case LineStrip:
        return "LineStrip";
    case Triangles:
        return "Triangles";
    case TriangleStrip:
        return "TriangleStrip";
    case TriangleFan:
        return "TriangleFan";
    }

    assert(false);
    return "Unknown";
}

void VertexArray::draw(Renderer& renderer) const
{
    renderer.draw_vertex_array(*this);
}

} // namespace zth
