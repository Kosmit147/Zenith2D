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
    static std::optional<Texture> from_file(std::string_view path);

    ~Texture() = default;

    Texture(const Texture&) = default;
    Texture(Texture&& other) noexcept;

    Texture& operator=(const Texture&) = default;
    Texture& operator=(Texture&& other) noexcept;

    bool load_from_file(std::string_view path);

    auto width() const { return _texture.getSize().x; }
    auto height() const { return _texture.getSize().y; }
    auto size() const { return TextureSize{ width(), height() }; }

    unsigned int get_native_handle() const { return _texture.getNativeHandle(); }

    friend class Shader;
    friend class Sprite;

private:
    sf::Texture _texture;
};

} // namespace zth
