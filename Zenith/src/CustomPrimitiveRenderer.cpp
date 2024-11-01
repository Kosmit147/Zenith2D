#include "CustomPrimitiveRenderer.hpp"

#include <execution>
#include <stack>

#include "Typedefs.hpp"

namespace zth {

void CustomPrimitiveRenderer::draw_point(const Vec2f& point, const Color& color)
{
    plot_point(point, color);
    _draw_call.execute(_render_target, sf::Points);
}

void CustomPrimitiveRenderer::draw_points(std::span<const Vec2f> points, const Color& color)
{
    plot_points(points, color);
    _draw_call.execute(_render_target, sf::Points);
}

void CustomPrimitiveRenderer::draw_line(const Vec2f& from, const Vec2f& to, const Color& color)
{
    plot_line(from, to, color);
    _draw_call.execute(_render_target, sf::Points);
}

void CustomPrimitiveRenderer::draw_line(const Line& line, const Color& color)
{
    plot_line(line, color);
    _draw_call.execute(_render_target, sf::Points);
}

void CustomPrimitiveRenderer::draw_line_strip(std::span<const Vec2f> points, const Color& color)
{
    plot_line_strip(points, color);
    _draw_call.execute(_render_target, sf::Points);
}

void CustomPrimitiveRenderer::draw_lines(std::span<const Line> lines, const Color& color)
{
    plot_lines(lines, color);
    _draw_call.execute(_render_target, sf::Points);
}

void CustomPrimitiveRenderer::draw_closed_lines(std::span<const Vec2f> points, const Color& color)
{
    plot_closed_lines(points, color);
    _draw_call.execute(_render_target, sf::Points);
}

void CustomPrimitiveRenderer::draw_closed_lines(std::span<const Line> lines, const Color& color)
{
    plot_closed_lines(lines, color);
    _draw_call.execute(_render_target, sf::Points);
}

void CustomPrimitiveRenderer::draw_rect(const Rect& rect, const Color& color)
{
    plot_rect(rect, color);
    _draw_call.execute(_render_target, sf::Points);
}

void CustomPrimitiveRenderer::draw_filled_rect(const Rect& rect, const Color& color)
{
    const auto render_target_size = _render_target.getSize();
    auto& image = get_tmp_image(render_target_size);

    draw_rect_on_image(image, rect, color);

    auto top_left = rect.position;
    auto bottom_right = rect.position + rect.size;

    // get the middle of the diagonal as the starting point
    auto seed = static_cast<Vec2u>((top_left + bottom_right) / 2.0f);

    switch (fill_algorithm)
    {
    case FillAlgorithm::BoundaryFill:
        boundary_fill(image, seed, color, color);
        break;
    case FillAlgorithm::FloodFill:
        flood_fill(image, seed, color, Color::transparent);
        break;
    }

    sf::Texture texture;

    if (!texture.loadFromImage(image))
        return;

    sf::Sprite sprite(texture);
    _render_target.draw(sprite);
}

void CustomPrimitiveRenderer::draw_polygon(std::span<const Vec2f> points, const Color& color)
{
    // The main PrimitiveRenderer class checks whether the polygon is valid in the first place
    plot_polygon(points, color);
    _draw_call.execute(_render_target, sf::Points);
}

void CustomPrimitiveRenderer::draw_polygon(std::span<const Line> lines, const Color& color)
{
    // The main PrimitiveRenderer class checks whether the polygon is valid in the first place
    plot_polygon(lines, color);
    _draw_call.execute(_render_target, sf::Points);
}

void CustomPrimitiveRenderer::draw_filled_polygon(std::span<const Vec2f> points, const Color& color) const
{
    const auto render_target_size = _render_target.getSize();
    auto& image = get_tmp_image(render_target_size);

    draw_line_strip_on_image(image, points, color);
    draw_line_on_image(image, points.back(), points.front(), color);

    // TODO: figure out a better way to find the seed
    auto points_sum = std::reduce(points.begin(), points.end(), Vec2f{ 0, 0 });
    auto points_average = points_sum / static_cast<float>(points.size());
    auto seed = static_cast<Vec2u>(points_average);

    switch (fill_algorithm)
    {
    case FillAlgorithm::BoundaryFill:
        boundary_fill(image, seed, color, color);
        break;
    case FillAlgorithm::FloodFill:
        flood_fill(image, seed, color, Color::transparent);
        break;
    }

    sf::Texture texture;

    if (!texture.loadFromImage(image))
        return;

    sf::Sprite sprite(texture);
    _render_target.draw(sprite);
}

void CustomPrimitiveRenderer::draw_filled_polygon(std::span<const Line> lines, const Color& color) const
{
    const auto render_target_size = _render_target.getSize();
    auto& image = get_tmp_image(render_target_size);

    draw_lines_on_image(image, lines, color);

    // TODO: figure out a better way to find the seed
    auto points_sum = std::transform_reduce(lines.begin(), lines.end(), Vec2f{ 0.0f, 0.0f }, std::plus{},
                                            [](auto& line) { return line.from; });
    auto points_average = points_sum / static_cast<float>(lines.size());
    auto seed = static_cast<Vec2u>(points_average);

    switch (fill_algorithm)
    {
    case FillAlgorithm::BoundaryFill:
        boundary_fill(image, seed, color, color);
        break;
    case FillAlgorithm::FloodFill:
        flood_fill(image, seed, color, Color::transparent);
        break;
    }

    sf::Texture texture;

    if (!texture.loadFromImage(image))
        return;

    sf::Sprite sprite(texture);
    _render_target.draw(sprite);
}

void CustomPrimitiveRenderer::draw_circle(const Circle& circle, const Color& color)
{
    plot_circle(circle, color);
    _draw_call.execute(_render_target, sf::Points);
}

void CustomPrimitiveRenderer::draw_ellipse(const Ellipse& ellipse, const Color& color)
{
    plot_ellipse(ellipse, color);
    _draw_call.execute(_render_target, sf::Points);
}

void CustomPrimitiveRenderer::draw_filled_circle(const Circle& circle, const Color& color) const
{
    const auto render_target_size = _render_target.getSize();
    auto& image = get_tmp_image(render_target_size);

    draw_circle_on_image(image, circle, color);

    auto seed = static_cast<Vec2u>(circle.center);

    switch (fill_algorithm)
    {
    case FillAlgorithm::BoundaryFill:
        boundary_fill(image, seed, color, color);
        break;
    case FillAlgorithm::FloodFill:
        flood_fill(image, seed, color, Color::transparent);
        break;
    }

    sf::Texture texture;

    if (!texture.loadFromImage(image))
        return;

    sf::Sprite sprite(texture);
    _render_target.draw(sprite);
}

void CustomPrimitiveRenderer::draw_filled_ellipse(const Ellipse& ellipse, const Color& color) const
{
    const auto render_target_size = _render_target.getSize();
    auto& image = get_tmp_image(render_target_size);

    draw_ellipse_on_image(image, ellipse, color);

    auto seed = static_cast<Vec2u>(ellipse.center);

    switch (fill_algorithm)
    {
    case FillAlgorithm::BoundaryFill:
        boundary_fill(image, seed, color, color);
        break;
    case FillAlgorithm::FloodFill:
        flood_fill(image, seed, color, Color::transparent);
        break;
    }

    sf::Texture texture;

    if (!texture.loadFromImage(image))
        return;

    sf::Sprite sprite(texture);
    _render_target.draw(sprite);
}

void CustomPrimitiveRenderer::plot_point(const Vec2f& point, const Color& color)
{
    _draw_call.vertices.emplace_back(static_cast<sf::Vector2f>(point), static_cast<sf::Color>(color));
}

void CustomPrimitiveRenderer::plot_points(std::span<const Vec2f> points, const Color& color)
{
    for (const auto& point : points)
        plot_point(point, color);
}

void CustomPrimitiveRenderer::plot_line(const Vec2f& from, const Vec2f& to, const Color& color)
{
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
            plot_point({ x, static_cast<float>(y) }, color);
            x += slope;
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
            plot_point({ static_cast<float>(x), y }, color);
            y += slope;
        }
    }
}

void CustomPrimitiveRenderer::plot_line(const Line& line, const Color& color)
{
    plot_line(line.from, line.to, color);
}

void CustomPrimitiveRenderer::plot_line_strip(std::span<const Vec2f> points, const Color& color)
{
    for (const auto line : points | std::views::adjacent<2>)
    {
        const auto& [from, to] = line;
        plot_line(from, to, color);
    }
}

void CustomPrimitiveRenderer::plot_lines(std::span<const Line> lines, const Color& color)
{
    for (const auto& line : lines)
        plot_line(line, color);
}

void CustomPrimitiveRenderer::plot_closed_lines(std::span<const Vec2f> points, const Color& color)
{
    plot_line_strip(points, color);
    plot_line(points.back(), points.front(), color);
}

void CustomPrimitiveRenderer::plot_closed_lines(std::span<const Line> lines, const Color& color)
{
    plot_lines(lines, color);

    if (lines.size() < 2)
        return;

    plot_line(lines.back().to, lines.front().from, color);
}

void CustomPrimitiveRenderer::plot_rect(const Rect& rect, const Color& color)
{
    auto points = rect.points();
    plot_line_strip(points, color);
    plot_line(points.back(), points.front(), color);
}

void CustomPrimitiveRenderer::plot_polygon(std::span<const Vec2f> points, const Color& color)
{
    for (const auto line : points | std::views::adjacent<2>)
    {
        const auto& [from, to] = line;
        plot_line(from, to, color);
    }

    if (points.size() < 3)
        return;

    plot_line(points.back(), points.front(), color);
}

void CustomPrimitiveRenderer::plot_polygon(std::span<const Line> lines, const Color& color)
{
    for (const auto& line : lines)
        plot_line(line, color);
}

void CustomPrimitiveRenderer::plot_circle(const Circle& circle, const Color& color)
{
    constexpr auto pi = std::numbers::pi_v<float>;

    auto [xc, yc] = circle.center;
    float step = 1.0f / circle.radius;

    // TODO: do something about floating-point loop counter
    for (float alpha = 0; alpha < pi / 4.0f; alpha += step)
    {
        float x = circle.radius * std::cos(alpha);
        float y = circle.radius * std::sin(alpha);

        std::array points = {
            Vec2f{ xc + x, yc + y }, Vec2f{ xc + x, yc - y }, Vec2f{ xc - x, yc + y }, Vec2f{ xc - x, yc - y },
            Vec2f{ xc + y, yc + x }, Vec2f{ xc + y, yc - x }, Vec2f{ xc - y, yc + x }, Vec2f{ xc - y, yc - x },
        };

        plot_points(points, color);
    }
}

void CustomPrimitiveRenderer::plot_ellipse(const Ellipse& ellipse, const Color& color)
{
    constexpr auto pi = std::numbers::pi_v<float>;

    auto [xc, yc] = ellipse.center;
    float step = 1.0f / std::max(ellipse.radius.x, ellipse.radius.y);

    // TODO: do something about floating-point loop counter
    for (float alpha = 0; alpha < pi / 2.0f; alpha += step)
    {
        float x = ellipse.radius.x * std::cos(alpha);
        float y = ellipse.radius.y * std::sin(alpha);

        std::array points = {
            Vec2f{ xc + x, yc + y },
            Vec2f{ xc + x, yc - y },
            Vec2f{ xc - x, yc + y },
            Vec2f{ xc - x, yc - y },
        };

        plot_points(points, color);
    }
}

void CustomPrimitiveRenderer::draw_line_on_image(sf::Image& image, const Vec2f& from, const Vec2f& to,
                                                 const Color& color)
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

        for (; y <= end_y; y++)
        {
            image.setPixel(static_cast<u32>(x), y, sf_color);
            x += slope;
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
            image.setPixel(x, static_cast<u32>(y), sf_color);
            y += slope;
        }
    }
}

void CustomPrimitiveRenderer::draw_line_on_image(sf::Image& image, const Line& line, const Color& color)
{
    draw_line_on_image(image, line.from, line.to, color);
}

void CustomPrimitiveRenderer::draw_line_strip_on_image(sf::Image& image, std::span<const Vec2f> points,
                                                       const Color& color)
{
    for (const auto line : points | std::views::adjacent<2>)
    {
        const auto& [from, to] = line;
        draw_line_on_image(image, from, to, color);
    }
}

void CustomPrimitiveRenderer::draw_lines_on_image(sf::Image& image, std::span<const Line> lines, const Color& color)
{
    for (const auto& line : lines)
        draw_line_on_image(image, line, color);
}

void CustomPrimitiveRenderer::draw_rect_on_image(sf::Image& image, const Rect& rect, const Color& color)
{
    auto points = rect.points();
    draw_line_strip_on_image(image, points, color);
    draw_line_on_image(image, points.back(), points.front(), color);
}

void CustomPrimitiveRenderer::draw_circle_on_image(sf::Image& image, const Circle& circle, const Color& color)
{
    const auto sf_color = static_cast<sf::Color>(color);
    constexpr auto pi = std::numbers::pi_v<float>;

    u32 xc = static_cast<u32>(circle.center.x);
    u32 yc = static_cast<u32>(circle.center.y);
    float step = 1.0f / circle.radius;

    // TODO: do something about floating-point loop counter
    for (float alpha = 0; alpha < pi / 4.0f; alpha += step)
    {
        u32 x = static_cast<u32>(circle.radius * std::cos(alpha));
        u32 y = static_cast<u32>(circle.radius * std::sin(alpha));

        image.setPixel(xc + x, yc + y, sf_color);
        image.setPixel(xc + x, yc - y, sf_color);
        image.setPixel(xc - x, yc + y, sf_color);
        image.setPixel(xc - x, yc - y, sf_color);
        image.setPixel(xc + y, yc + x, sf_color);
        image.setPixel(xc + y, yc - x, sf_color);
        image.setPixel(xc - y, yc + x, sf_color);
        image.setPixel(xc - y, yc - x, sf_color);
    }
}

void CustomPrimitiveRenderer::draw_ellipse_on_image(sf::Image& image, const Ellipse& ellipse, const Color& color)
{
    const auto sf_color = static_cast<sf::Color>(color);
    constexpr auto pi = std::numbers::pi_v<float>;

    u32 xc = static_cast<u32>(ellipse.center.x);
    u32 yc = static_cast<u32>(ellipse.center.y);
    float step = 1.0f / std::max(ellipse.radius.x, ellipse.radius.y);

    // TODO: do something about floating-point loop counter
    for (float alpha = 0; alpha < pi / 2.0f; alpha += step)
    {
        u32 x = static_cast<u32>(ellipse.radius.x * std::cos(alpha));
        u32 y = static_cast<u32>(ellipse.radius.y * std::sin(alpha));

        image.setPixel(xc + x, yc + y, sf_color);
        image.setPixel(xc + x, yc - y, sf_color);
        image.setPixel(xc - x, yc + y, sf_color);
        image.setPixel(xc - x, yc - y, sf_color);
    }
}

void CustomPrimitiveRenderer::boundary_fill(sf::Image& image, const Vec2u& seed, const Color& border_color,
                                            const Color& fill_color)
{
    const auto image_size = image.getSize();

    std::stack<Vec2u> stack;
    stack.emplace(seed.x, seed.y);

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

        if (y > 1)
            stack.emplace(x, y - 1);

        if (x < image_size.x - 1)
            stack.emplace(x + 1, y);

        if (y < image_size.y - 1)
            stack.emplace(x, y + 1);

        if (x > 1)
            stack.emplace(x - 1, y);
    }
}

void CustomPrimitiveRenderer::flood_fill(sf::Image& image, const Vec2u& seed, const Color& fill_color,
                                         const Color& background_color)
{
    const auto image_size = image.getSize();

    std::stack<Vec2u> stack;
    stack.emplace(seed.x, seed.y);

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

        if (y > 1)
            stack.emplace(x, y - 1);

        if (x < image_size.x - 1)
            stack.emplace(x + 1, y);

        if (y < image_size.y - 1)
            stack.emplace(x, y + 1);

        if (x > 1)
            stack.emplace(x - 1, y);
    }
}

sf::Image& CustomPrimitiveRenderer::get_tmp_image(sf::Vector2u size)
{
    // TODO:
    // maybe change this to return a temporary buffer, then upload that buffer into sf::Image (or a texture?) to draw?
    // not sure if this is a good idea
    // this seems hacky
    // TODO: get a zeroed out buffer ready to be copied to the image whenever it needs to be cleared
    static sf::Image image;

    auto image_size = image.getSize();

    if (size != image_size)
        image.create(size.x, size.y, static_cast<sf::Color>(Color::transparent));

    auto xs = std::views::iota(0u, size.x);
    auto ys = std::views::iota(0u, size.y);
    const auto pixel_coords = std::views::cartesian_product(ys, xs); // first ys, then xs!

    // clear the image
    std::for_each(std::execution::par_unseq, pixel_coords.begin(), pixel_coords.end(), [&](const auto& coords) {
        const auto& [y, x] = coords; // first ys, then xs!
        image.setPixel(x, y, static_cast<sf::Color>(Color::transparent));
    });

    return image;
}

} // namespace zth
