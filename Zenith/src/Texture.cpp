#include "Texture.hpp"

namespace zth {

Texture::Texture(TextureSize size)
{
    _texture.create(size.width, size.height);
}

std::optional<Texture> Texture::create_from_file(std::string_view path)
{
    if (Texture tex; tex.load_from_file(path))
        return tex;

    return {};
}

Texture::Texture(Texture&& other) noexcept
{
    _texture.swap(other._texture);
}

Texture& Texture::operator=(Texture&& other) noexcept
{
    _texture.swap(other._texture);
    return *this;
}

bool Texture::load_from_file(std::string_view path)
{
    return _texture.loadFromFile(path.data());
}

} // namespace zth
