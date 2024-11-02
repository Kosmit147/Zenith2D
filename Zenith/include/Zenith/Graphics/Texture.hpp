#pragma once

#include <SFML/Graphics/Texture.hpp>

#include <optional>
#include <string_view>

#include "Zenith/Core/Typedefs.hpp"

namespace zth {

struct TextureSize
{
    u32 width;
    u32 height;
};

class Texture
{
public:
    explicit Texture() = default;
    explicit Texture(TextureSize size);
    static std::optional<Texture> create_from_file(std::string_view path);

    ~Texture() = default;

    Texture(const Texture& other) = default;
    Texture(Texture&& other) noexcept;

    Texture& operator=(const Texture& other) = default;
    Texture& operator=(Texture&& other) noexcept;

    bool load_from_file(std::string_view path);

    auto width() const { return _texture.getSize().x; }
    auto height() const { return _texture.getSize().y; }
    auto size() const { return TextureSize{ width(), height() }; }

private:
    sf::Texture _texture;
};

} // namespace zth
