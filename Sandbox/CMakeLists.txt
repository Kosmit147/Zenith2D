cmake_minimum_required(VERSION 3.28)
project(Sandbox LANGUAGES CXX)

add_executable(
	Sandbox
	"src/Dragon.cpp"
	"src/Level1.cpp"
	"src/Level2.cpp"
	"src/Player.cpp"
	"src/Sandbox.cpp"
)

b_embed(Sandbox "assets/emoji.png")
b_embed(Sandbox "assets/dragon.png")
b_embed(Sandbox "assets/gold.png")
b_embed(Sandbox "assets/you_won.png")

if(CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*")
	target_link_libraries(Sandbox PRIVATE Zenith -lstdc++exp)
else()
	target_link_libraries(Sandbox PRIVATE Zenith)
endif()

target_compile_features(Sandbox PRIVATE cxx_std_23)
target_compile_options(Sandbox PRIVATE ${COMPILE_WARNINGS})
set_property(TARGET Sandbox PROPERTY COMPILE_WARNING_AS_ERROR ON)
