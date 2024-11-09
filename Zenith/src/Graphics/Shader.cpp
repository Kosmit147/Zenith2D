#include "Zenith/Graphics/Shader.hpp"

#include "Zenith/Logging/Logger.hpp"

namespace zth {

bool Shader::load_from_string(std::string_view shader_source, ShaderType shader_type)
{
    if (!_shader.loadFromMemory(shader_source.data(), to_sf_shader_type(shader_type)))
    {
        logger.get_or_init().log_error("Failed to create {} shader from source: {}", to_string(shader_type),
                                       shader_source.data());
        return false;
    }

    return true;
}

bool Shader::load_from_string(std::string_view vertex_shader_source, std::string_view fragment_shader_source)
{
    if (!_shader.loadFromMemory(vertex_shader_source.data(), fragment_shader_source.data()))
    {
        auto& log = logger.get_or_init();
        log.log_error("Failed to create vertex shader from source: {}", vertex_shader_source.data());
        log.log_error("Failed to create fragment shader from source: {}", fragment_shader_source.data());
        return false;
    }

    return true;
}

bool Shader::load_from_file(std::string_view shader_path, ShaderType shader_type)
{
    if (!_shader.loadFromFile(shader_path.data(), to_sf_shader_type(shader_type)))
    {
        logger.get_or_init().log_error("Failed to load {} shader from path: {}", to_string(shader_type),
                                       shader_path.data());
        return false;
    }

    return true;
}

bool Shader::load_from_file(std::string_view vertex_shader_path, std::string_view fragment_shader_path)
{
    if (!_shader.loadFromFile(vertex_shader_path.data(), fragment_shader_path.data()))
    {
        auto& log = logger.get_or_init();
        log.log_error("Failed to load vertex shader from path: {}", vertex_shader_path.data());
        log.log_error("Failed to load fragment shader from path: {}", fragment_shader_path.data());
        return false;
    }

    return true;
}

ShaderType to_shader_type(sf::Shader::Type shader_type)
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

sf::Shader::Type to_sf_shader_type(ShaderType shader_type)
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

const char* to_string(ShaderType shader_type)
{
    switch (shader_type)
    {
        using enum ShaderType;
    case Vertex:
        return "Vertex";
    case Geometry:
        return "Geometry";
    case Fragment:
        return "Fragment";
    }

    assert(false);
    return "Unknown";
}

} // namespace zth
