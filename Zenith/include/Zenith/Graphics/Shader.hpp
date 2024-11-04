#pragma once

#include <SFML/Graphics/Shader.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>

#include <cassert>
#include <string>
#include <string_view>
#include <utility>

#include "Zenith/Core/Typedefs.hpp"
#include "Zenith/Graphics/Texture.hpp"
#include "Zenith/Math/Vec2.hpp"
#include "Zenith/Math/Vec3.hpp"
#include "Zenith/Utility/Utility.hpp"

namespace zth {

enum class ShaderType
{
    Vertex,
    Geometry,
    Fragment,
};

class Shader
{
public:
    explicit Shader() = default;
    explicit Shader(std::string_view shader_source, ShaderType shader_type);
    explicit Shader(std::string_view vertex_shader_source, std::string_view fragment_shader_source);
    ~Shader() = default;
    ZTH_NO_COPY_NO_MOVE(Shader)

    bool load_from_string(std::string_view shader_source, ShaderType shader_type);
    bool load_from_string(std::string_view vertex_shader_source, std::string_view fragment_shader_source);
    bool load_from_file(std::string_view path, ShaderType shader_type);
    bool load_from_file(std::string_view vertex_path, std::string_view fragment_path);

    void bind() const { sf::Shader::bind(&_shader); }

    template<typename T> void set_unif(const std::string& name, T val);

    u32 get_native_handle() const { return _shader.getNativeHandle(); }

private:
    sf::Shader _shader;
};

template<> inline void Shader::set_unif(const std::string& name, float val)
{
    _shader.setUniform(name, val);
}

template<> inline void Shader::set_unif(const std::string& name, const Vec2f& val)
{
    _shader.setUniform(name, static_cast<sf::Vector2f>(val));
}

template<> inline void Shader::set_unif(const std::string& name, const Vec3f& val)
{
    _shader.setUniform(name, static_cast<sf::Vector3f>(val));
}

template<> inline void Shader::set_unif(const std::string& name, i32 val)
{
    _shader.setUniform(name, val);
}

template<> inline void Shader::set_unif(const std::string& name, const Vec2i& val)
{
    _shader.setUniform(name, static_cast<sf::Vector2i>(val));
}

template<> inline void Shader::set_unif(const std::string& name, const Vec3i& val)
{
    _shader.setUniform(name, static_cast<sf::Vector3i>(val));
}

template<> inline void Shader::set_unif(const std::string& name, bool val)
{
    _shader.setUniform(name, val);
}

template<> inline void Shader::set_unif(const std::string& name, const Texture& val)
{
    _shader.setUniform(name, val._texture);
}

constexpr auto to_shader_type(sf::Shader::Type shader_type)
{
    switch (shader_type)
    {
    case sf::Shader::Vertex:
        return ShaderType::Vertex;
    case sf::Shader::Geometry:
        return ShaderType::Geometry;
    case sf::Shader::Fragment:
        return ShaderType::Fragment;
    }

    assert(false);
    std::unreachable();
}

constexpr auto to_sf_shader_type(ShaderType shader_type)
{
    switch (shader_type)
    {
    case ShaderType::Vertex:
        return sf::Shader::Vertex;
    case ShaderType::Geometry:
        return sf::Shader::Geometry;
    case ShaderType::Fragment:
        return sf::Shader::Fragment;
    }

    assert(false);
    std::unreachable();
}

const char* to_string(ShaderType shader_type);

} // namespace zth
