cmake_minimum_required(VERSION 3.28)
project(Zenith LANGUAGES CXX)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_library(
    Zenith
    "src/Application.cpp"
    "src/EllipseShape.cpp"
    "src/Event.cpp"
    "src/FileIo.cpp"
    "src/Input.cpp"
    "src/Logger.cpp"
    "src/PrimitiveRenderer.cpp"
    "src/Window.cpp"
)
target_include_directories(Zenith PRIVATE include/Zenith)
target_include_directories(Zenith INTERFACE include)
target_link_libraries(Zenith PUBLIC sfml-graphics)
target_compile_features(Zenith PRIVATE cxx_std_23)
target_compile_options(Zenith PRIVATE ${COMPILE_WARNINGS})
set_property(TARGET Zenith PROPERTY COMPILE_WARNING_AS_ERROR ON)

if(WIN32)
    add_custom_command(
        TARGET Zenith
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:Zenith>
        VERBATIM)
endif()
