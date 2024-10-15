cmake_minimum_required(VERSION 3.28)
project(Engine LANGUAGES CXX)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_library(Engine
    "src/Color.cpp"
    "src/Engine.cpp"
    "src/Event.cpp"
    "src/Key.cpp"
    "src/Logger.cpp"
    "src/PrimitiveRenderer.cpp"
 "include/Engine/PrimitiveRenderer.h" "src/PrimitiveRenderer.cpp")
target_include_directories(Engine PRIVATE include/Engine)
target_include_directories(Engine INTERFACE include)
target_link_libraries(Engine PUBLIC sfml-graphics)
target_compile_features(Engine PRIVATE cxx_std_23)

if(WIN32)
    add_custom_command(
        TARGET Engine
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:Engine>
        VERBATIM)
endif()
