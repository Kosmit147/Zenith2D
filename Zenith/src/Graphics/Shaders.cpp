#include "Zenith/Graphics/Shaders.hpp"

#include <battery/embed.hpp>

namespace zth::shaders {

static const auto basic_shader_vert = b::embed<"src/Shaders/basic.vert">();
static const auto basic_shader_frag = b::embed<"src/Shaders/basic.frag">();
const Shader basic_shader{ basic_shader_vert, basic_shader_frag };

} // namespace zth::shaders
