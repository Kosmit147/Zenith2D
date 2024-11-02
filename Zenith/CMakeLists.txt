cmake_minimum_required(VERSION 3.28)
project(Zenith LANGUAGES CXX)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

add_library(
    Zenith STATIC
    "src/Core/Application.cpp"
    "src/Filesystem/FileIo.cpp"
    "src/Graphics/CustomPrimitiveRenderer.cpp"
    "src/Graphics/EllipseShape.cpp"
    "src/Graphics/PrimitiveRenderer.cpp"
    "src/Graphics/SfmlPrimitiveRenderer.cpp"
    "src/Graphics/Texture.cpp"
    "src/Logging/Logger.cpp"
    "src/Platform/Event.cpp"
    "src/Platform/Input.cpp"
    "src/Platform/Window.cpp"
)
target_link_libraries(Zenith PUBLIC sfml-graphics)
target_include_directories(Zenith PUBLIC "include")
target_compile_features(Zenith PRIVATE cxx_std_23)
target_compile_options(Zenith PRIVATE ${COMPILE_WARNINGS})
target_precompile_headers(Zenith PRIVATE "src/pch.hpp")
set_property(TARGET Zenith PROPERTY COMPILE_WARNING_AS_ERROR ON)

if(WIN32)
    add_custom_command(
        TARGET Zenith
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:Zenith>
        VERBATIM)
endif()
