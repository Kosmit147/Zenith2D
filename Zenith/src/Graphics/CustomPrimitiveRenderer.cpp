#include "Zenith/Graphics/CustomPrimitiveRenderer.hpp"

#include <stack>

#include "Zenith/Core/Typedefs.hpp"

namespace zth {

void CustomPrimitiveRenderer::draw_point_impl(const Vec2f& point, const Color& color)
{
    plot_point(point, color);
    draw_call();
}

void CustomPrimitiveRenderer::draw_points_impl(std::span<const Vec2f> points, const Color& color)
{
    plot_points(points, color);
    draw_call();
}

void CustomPrimitiveRenderer::draw_line_impl(const Vec2f& from, const Vec2f& to, const Color& color)
{
    plot_line(from, to, color);
    draw_call();
}

void CustomPrimitiveRenderer::draw_line_impl(const Line& line, const Color& color)
{
    plot_line(line, color);
    draw_call();
}

void CustomPrimitiveRenderer::draw_line_strip_impl(std::span<const Vec2f> points, const Color& color)
{
    plot_line_strip(points, color);
    draw_call();
}

void CustomPrimitiveRenderer::draw_lines_impl(std::span<const Line> lines, const Color& color)
{
    plot_lines(lines, color);
    draw_call();
}

void CustomPrimitiveRenderer::draw_closed_lines_impl(std::span<const Vec2f> points, const Color& color)
{
    plot_closed_lines(points, color);
    draw_call();
}

void CustomPrimitiveRenderer::draw_closed_lines_impl(std::span<const Line> lines, const Color& color)
{
    plot_closed_lines(lines, color);
    draw_call();
}

void CustomPrimitiveRenderer::draw_rect_impl(const Rect& rect, const Color& color)
{
    plot_rect(rect, color);
    draw_call();
}

void CustomPrimitiveRenderer::draw_filled_rect_impl(const Rect& rect, const Color& color)
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

void CustomPrimitiveRenderer::draw_polygon_impl(std::span<const Vec2f> points, const Color& color)
{
    // The main PrimitiveRenderer class checks whether the polygon is valid in the first place
    plot_polygon(points, color);
    draw_call();
}

void CustomPrimitiveRenderer::draw_polygon_impl(std::span<const Line> lines, const Color& color)
{
    // The main PrimitiveRenderer class checks whether the polygon is valid in the first place
    plot_polygon(lines, color);
    draw_call();
}

void CustomPrimitiveRenderer::draw_filled_polygon_impl(std::span<const Vec2f> points, const Color& color)
{
    const auto render_target_size = _render_target.getSize();
    auto& image = get_tmp_image(render_target_size);

    draw_line_strip_on_image(image, points, color);
    draw_line_on_image(image, points.back(), points.front(), color);

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

void CustomPrimitiveRenderer::draw_filled_polygon_impl(std::span<const Line> lines, const Color& color)
{
    const auto render_target_size = _render_target.getSize();
    auto& image = get_tmp_image(render_target_size);

    draw_lines_on_image(image, lines, color);

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

void CustomPrimitiveRenderer::draw_circle_impl(const Circle& circle, const Color& color)
{
    plot_circle(circle, color);
    draw_call();
}

void CustomPrimitiveRenderer::draw_ellipse_impl(const Ellipse& ellipse, const Color& color)
{
    plot_ellipse(ellipse, color);
    draw_call();
}

void CustomPrimitiveRenderer::draw_filled_circle_impl(const Circle& circle, const Color& color)
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

void CustomPrimitiveRenderer::draw_filled_ellipse_impl(const Ellipse& ellipse, const Color& color)
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
    _vertex_array.append({ static_cast<sf::Vector2f>(point), static_cast<sf::Color>(color) });
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
    float step = std::min(1.0f / circle.radius, 1.0f);
    usize iterations = static_cast<usize>(pi / 4.0f / step) + 1;
    float alpha = 0.0f;

    for (usize i = 0; i < iterations; i++)
    {
        float x = circle.radius * std::cos(alpha);
        float y = circle.radius * std::sin(alpha);

        std::array points = {
            Vec2f{ xc + x, yc + y }, Vec2f{ xc + x, yc - y }, Vec2f{ xc - x, yc + y }, Vec2f{ xc - x, yc - y },
            Vec2f{ xc + y, yc + x }, Vec2f{ xc + y, yc - x }, Vec2f{ xc - y, yc + x }, Vec2f{ xc - y, yc - x },
        };

        plot_points(points, color);
        alpha += step;
    }
}

void CustomPrimitiveRenderer::plot_ellipse(const Ellipse& ellipse, const Color& color)
{
    constexpr auto pi = std::numbers::pi_v<float>;

    auto [xc, yc] = ellipse.center;
    float step = 1.0f / std::max(ellipse.radius.x, ellipse.radius.y);
    step = std::min(step, 1.0f);
    usize iterations = static_cast<usize>(pi / 2.0f / step) + 1;
    float alpha = 0.0f;

    for (usize i = 0; i < iterations; i++)
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
        alpha += step;
    }
}

void CustomPrimitiveRenderer::draw_line_on_image(sf::Image& image, const Vec2f& from, const Vec2f& to,
                                                 const Color& color)
{
    // TODO: make sure the calculated points fit within the image

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
        u32 y = static_cast<u32>(start_point.y);
        u32 end_y = static_cast<u32>(end_point.y);
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

        u32 x = static_cast<u32>(start_point.x);
        u32 end_x = static_cast<u32>(end_point.x);
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
    // TODO: make sure the calculated points fit within the image

    const auto sf_color = static_cast<sf::Color>(color);
    constexpr auto pi = std::numbers::pi_v<float>;

    u32 xc = static_cast<u32>(circle.center.x);
    u32 yc = static_cast<u32>(circle.center.y);
    float step = std::min(1.0f / circle.radius, 1.0f);
    usize iterations = static_cast<usize>(pi / 4.0f / step) + 1;
    float alpha = 0.0f;

    for (usize i = 0; i < iterations; i++)
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

        alpha += step;
    }
}

void CustomPrimitiveRenderer::draw_ellipse_on_image(sf::Image& image, const Ellipse& ellipse, const Color& color)
{
    // TODO: make sure the calculated points fit within the image

    const auto sf_color = static_cast<sf::Color>(color);
    constexpr auto pi = std::numbers::pi_v<float>;

    u32 xc = static_cast<u32>(ellipse.center.x);
    u32 yc = static_cast<u32>(ellipse.center.y);
    float step = 1.0f / std::max(ellipse.radius.x, ellipse.radius.y);
    step = std::min(step, 1.0f);
    usize iterations = static_cast<usize>(pi / 2.0f / step) + 1;
    float alpha = 0.0f;

    for (usize i = 0; i < iterations; i++)
    {
        u32 x = static_cast<u32>(ellipse.radius.x * std::cos(alpha));
        u32 y = static_cast<u32>(ellipse.radius.y * std::sin(alpha));

        image.setPixel(xc + x, yc + y, sf_color);
        image.setPixel(xc + x, yc - y, sf_color);
        image.setPixel(xc - x, yc + y, sf_color);
        image.setPixel(xc - x, yc - y, sf_color);

        alpha += step;
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

sf::Image& CustomPrimitiveRenderer::get_tmp_image(sf::Vector2u target_size)
{
    static std::vector<Color> buff;
    static sf::Image image;

    auto image_size = image.getSize();

    if (image_size != target_size)
        buff.assign(static_cast<usize>(target_size.x) * static_cast<usize>(target_size.y), Color::transparent);

    image.create(target_size.x, target_size.y, reinterpret_cast<u8*>(buff.data()));

    return image;
}

void CustomPrimitiveRenderer::draw_call()
{
    _vertex_array.setPrimitiveType(sf::Points); // we're only ever drawing points in custom renderer
    _render_target.draw(_vertex_array);
    _vertex_array.clear();
}

} // namespace zth
