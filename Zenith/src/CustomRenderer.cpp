#include "CustomRenderer.hpp"

#include <execution>
#include <stack>

#include "Typedefs.hpp"

namespace zth {

void CustomRenderer::draw_line(const Vec2f& from, const Vec2f& to, const Color& color)
{
    const auto sf_color = static_cast<sf::Color>(color);

    auto [delta_x, delta_y] = to - from;
    float slope = delta_y / delta_x;

    if (slope > 1.0f || slope < -1.0f)
    {
        // we're drawing a point for every y coord and calculating the corresponding x coord
        slope = 1.0f / slope;

        const auto& [start_point, end_point] =
            std::minmax(from, to, [](auto& from, auto& to) { return from.y <= to.y; });

        float x = start_point.x;
        i32 y = static_cast<i32>(start_point.y);
        i32 end_y = static_cast<i32>(end_point.y);
        assert(y <= end_y);

        std::vector<sf::Vertex> vertices;
        vertices.reserve(static_cast<u32>(end_y - y + 1));

        for (; y <= end_y; y++)
        {
            x += slope;
            vertices.emplace_back(sf::Vector2f{ x, static_cast<float>(y) }, sf_color);
        }

        _window.draw(vertices.data(), vertices.size(), sf::Points);
    }
    else
    {
        // we're drawing a point for every x coord and calculating the corresponding y coord
        const auto& [start_point, end_point] =
            std::minmax(from, to, [](auto& from, auto& to) { return from.x <= to.x; });

        i32 x = static_cast<i32>(start_point.x);
        i32 end_x = static_cast<i32>(end_point.x);
        float y = start_point.y;
        assert(x <= end_x);

        std::vector<sf::Vertex> vertices;
        vertices.reserve(static_cast<u32>(end_x - x + 1));

        for (; x <= end_x; x++)
        {
            y += slope;
            vertices.emplace_back(sf::Vector2f{ static_cast<float>(x), y }, sf_color);
        }

        _window.draw(vertices.data(), vertices.size(), sf::Points);
    }
}

void CustomRenderer::draw_line(const Line& line, const Color& color)
{
    draw_line(line.from, line.to, color);
}

void CustomRenderer::draw_rect(const Rect& rect, const Color& outline_color)
{
    auto points = rect.points();

    draw_line(points[0], points[1], outline_color);
    draw_line(points[1], points[2], outline_color);
    draw_line(points[2], points[3], outline_color);
    draw_line(points[3], points[0], outline_color);
}

void CustomRenderer::draw_polygon(std::span<const Vec2f> points, const Color& outline_color)
{
    for (const auto line : points | std::views::adjacent<2>)
    {
        const auto& [from, to] = line;
        draw_line(from, to, outline_color);
    }

    if (points.size() < 3)
        return;

    draw_line(points.back(), points.front(), outline_color);
}

void CustomRenderer::draw_polygon(std::span<const Line> lines, const Color& outline_color)
{
    for (const auto& line : lines)
        draw_line(line, outline_color);
}

void CustomRenderer::draw_filled_polygon(std::span<const Vec2f> points, const Color& outline_color,
                                                   const Color& fill_color)
{
    auto& image = get_tmp_image();

    draw_lines_on_image(image, points, outline_color);

    // TODO: figure out a better way to find the seed
    auto seed = std::reduce(points.begin(), points.end(), Vec2f{ 0, 0 }) / static_cast<float>(points.size());

    switch (fill_algorithm)
    {
    case FillAlgorithm::BoundaryFill:
        boundary_fill(image, seed, outline_color, fill_color);
        break;
    case FillAlgorithm::FloodFill:
        flood_fill(image, seed, outline_color, Color::transparent);
        break;
    }

    sf::Texture texture;

    if (!texture.loadFromImage(image))
        return;

    sf::Sprite sprite(texture);
    _target.draw(sprite);
}

void CustomRenderer::draw_filled_polygon(std::span<const Line> lines, const Color& outline_color,
                                         const Color& fill_color)
{
    (void)lines;
    (void)outline_color;
    (void)fill_color;
    // TODO
}

void CustomRenderer::draw_circle(const Circle& circle, const Color& color)
{
    constexpr auto pi = std::numbers::pi_v<float>;
    const auto sf_color = static_cast<sf::Color>(color);

    auto [xc, yc] = circle.center;
    float step = 1.0f / circle.radius;

    // TODO: do something about floating-point loop counter
    for (float alpha = 0; alpha < pi / 4.0f; alpha += step)
    {
        float x = circle.radius * std::cos(alpha);
        float y = circle.radius * std::sin(alpha);

        std::array vertices = {
            sf::Vertex{ { xc + x, yc + y }, sf_color }, sf::Vertex{ { xc + x, yc - y }, sf_color },
            sf::Vertex{ { xc - x, yc + y }, sf_color }, sf::Vertex{ { xc - x, yc - y }, sf_color },
            sf::Vertex{ { xc + y, yc + x }, sf_color }, sf::Vertex{ { xc + y, yc - x }, sf_color },
            sf::Vertex{ { xc - y, yc + x }, sf_color }, sf::Vertex{ { xc - y, yc - x }, sf_color },
        };

        _target.draw(vertices.data(), vertices.size(), sf::Points);
    }
}

void CustomRenderer::draw_ellipse(const Ellipse& ellipse, const Color& color) const
{
    constexpr auto pi = std::numbers::pi_v<float>;
    const auto sf_color = static_cast<sf::Color>(color);

    auto [xc, yc] = ellipse.center;
    float step = 1.0f / std::max(ellipse.radius.x, ellipse.radius.y);

    // TODO: do something about floating-point loop counter
    for (float alpha = 0; alpha < pi / 2.0f; alpha += step)
    {
        float x = ellipse.radius.x * std::cos(alpha);
        float y = ellipse.radius.y * std::sin(alpha);

        std::array vertices = {
            sf::Vertex{ { xc + x, yc + y }, sf_color },
            sf::Vertex{ { xc + x, yc - y }, sf_color },
            sf::Vertex{ { xc - x, yc + y }, sf_color },
            sf::Vertex{ { xc - x, yc - y }, sf_color },
        };

        _target.draw(vertices.data(), vertices.size(), sf::Points);
    }
}

void CustomRenderer::draw_line_on_image(sf::Image& image, const Vec2f& from, const Vec2f& to, const Color& color)
{
    // TODO: this code is copied from draw_line_custom function; refactor
    const auto sf_color = static_cast<sf::Color>(color);

    auto [delta_x, delta_y] = to - from;
    float slope = delta_y / delta_x;

    if (slope > 1.0f || slope < -1.0f)
    {
        // we're drawing a point for every y coord and calculating the corresponding x coord
        slope = 1.0f / slope;

        const auto& [start_point, end_point] =
            std::minmax(from, to, [](auto& from, auto& to) { return from.y <= to.y; });

        float x = start_point.x;
        i32 y = static_cast<i32>(start_point.y);
        i32 end_y = static_cast<i32>(end_point.y);
        assert(y <= end_y);

        for (; y <= end_y; y++)
        {
            x += slope;
            image.setPixel(static_cast<u32>(x), y, sf_color);
        }
    }
    else
    {
        // we're drawing a point for every x coord and calculating the corresponding y coord
        const auto& [start_point, end_point] =
            std::minmax(from, to, [](auto& from, auto& to) { return from.x <= to.x; });

        i32 x = static_cast<i32>(start_point.x);
        i32 end_x = static_cast<i32>(end_point.x);
        float y = start_point.y;
        assert(x <= end_x);

        for (; x <= end_x; x++)
        {
            y += slope;
            image.setPixel(x, static_cast<u32>(y), sf_color);
        }
    }
}

void CustomRenderer::draw_line_on_image(sf::Image& image, const Line& line, const Color& color)
{
    draw_line_on_image(image, line.from, line.to, color);
}

void CustomRenderer::draw_lines_on_image(sf::Image& image, std::span<const Vec2f> points, const Color& color)
{
    for (const auto line : points | std::views::adjacent<2>)
    {
        const auto& [from, to] = line;
        draw_line_on_image(image, from, to, color);
    }

    if (points.size() < 3)
        return;

    draw_line_on_image(image, points.back(), points.front(), color);
}

void CustomRenderer::draw_lines_on_image(sf::Image& image, std::span<const Line> lines, const Color& color)
{
    for (const auto& line : lines)
        draw_line_on_image(image, line, color);
}

void CustomRenderer::boundary_fill(sf::Image& image, const Vec2f& seed, const Color& border_color,
                                   const Color& fill_color)
{
    std::stack<Vec2u> stack;
    stack.emplace(static_cast<u32>(seed.x), static_cast<u32>(seed.y));

    auto push_if_valid = [&](u32 x, u32 y) {
        auto image_size = image.getSize();
        if (x > 0 && x < image_size.x && y > 0 && y < image_size.y)
            stack.emplace(x, y);
    };

    while (!stack.empty())
    {
        auto x = stack.top().x;
        auto y = stack.top().y;
        stack.pop();

        auto pixel_color = image.getPixel(x, y);

        if (pixel_color == static_cast<sf::Color>(fill_color))
            continue;

        if (pixel_color == static_cast<sf::Color>(border_color))
            continue;

        image.setPixel(x, y, static_cast<sf::Color>(fill_color));

        push_if_valid(x, y - 1);
        push_if_valid(x + 1, y);
        push_if_valid(x, y + 1);
        push_if_valid(x - 1, y);
    }
}

void CustomRenderer::flood_fill(sf::Image& image, const Vec2f& seed, const Color& fill_color,
                                const Color& background_color)
{
    std::stack<Vec2u> stack;
    stack.emplace(static_cast<u32>(seed.x), static_cast<u32>(seed.y));

    auto push_if_valid = [&](u32 x, u32 y) {
        auto image_size = image.getSize();
        if (x > 0 && x < image_size.x && y > 0 && y < image_size.y)
            stack.emplace(x, y);
    };

    while (!stack.empty())
    {
        auto x = stack.top().x;
        auto y = stack.top().y;
        stack.pop();

        auto pixel_color = image.getPixel(x, y);

        if (pixel_color == static_cast<sf::Color>(fill_color))
            continue;

        if (pixel_color != static_cast<sf::Color>(background_color))
            continue;

        image.setPixel(x, y, static_cast<sf::Color>(fill_color));

        push_if_valid(x, y - 1);
        push_if_valid(x + 1, y);
        push_if_valid(x, y + 1);
        push_if_valid(x - 1, y);
    }
}

sf::Image& CustomRenderer::get_tmp_image(sf::Vector2u size)
{
    // this seems hacky
    static sf::Image image;

    auto image_size = image.getSize();

    if (size != image_size)
        image.create(size.x, size.y, static_cast<sf::Color>(Color::transparent));

    auto xs = std::views::iota(0u, size.x);
    auto ys = std::views::iota(0u, size.y);
    const auto pixel_coords = std::views::cartesian_product(xs, ys);

    // clear the image
    std::for_each(std::execution::par_unseq, pixel_coords.begin(), pixel_coords.end(), [&](const auto& coords) {
        const auto& [x, y] = coords;
        image.setPixel(x, y, static_cast<sf::Color>(Color::transparent));
    });

    return image;
}

} // namespace zth
