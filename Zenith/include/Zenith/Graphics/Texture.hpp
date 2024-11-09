#pragma once

#include <SFML/Graphics/Texture.hpp>

#include <optional>
#include <string_view>

#include "Zenith/Core/Typedefs.hpp"
#include "Zenith/Utility/Utility.hpp"

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
    ZTH_DEFAULT_COPY(Texture)

    ~Texture() = default;

    Texture(Texture&& other) noexcept;
    Texture& operator=(Texture&& other) noexcept;

    bool load_from_file(std::string_view path);

    auto width() const { return _texture.getSize().x; }
    auto height() const { return _texture.getSize().y; }
    auto size() const { return TextureSize{ width(), height() }; }

    void bind() const { sf::Texture::bind(&_texture); }
    static void unbind() { sf::Texture::bind(nullptr); }

    unsigned int get_native_handle() const { return _texture.getNativeHandle(); }

    friend class Shader;
    friend class Sprite;

private:
    sf::Texture _texture;
};

} // namespace zth
