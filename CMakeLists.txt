cmake_minimum_required(VERSION 3.28)
include(cmake/warnings.cmake)

project(ZenithEngine LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE On)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELWITHDEBINFO On)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_MINSIZEREL On)

if (CMAKE_BUILD_TYPE MATCHES "Debug")
    add_compile_definitions(_DEBUG)
elseif(CMAKE_BUILD_TYPE MATCHES "Release" OR CMAKE_BUILD_TYPE MATCHES "MinSizeRel" OR CMAKE_BUILD_TYPE MATCHES "RelWithDebInfo")
    add_compile_definitions(_RELEASE)
    add_compile_definitions(NDEBUG)
endif()

get_compile_warnings(COMPILE_WARNINGS)
add_subdirectory("dependencies/SFML")

# unfortunately sfml-graphics does not set its headers as SYSTEM
# which results in warnings whenever these are included in our projects' files
# this is a hacky solution
get_target_property(_sfml_graphics_includes sfml-graphics INTERFACE_INCLUDE_DIRECTORIES)
target_include_directories(sfml-graphics SYSTEM INTERFACE ${_sfml_graphics_includes})

add_subdirectory("Zenith")
add_subdirectory("Testbed")
add_subdirectory("Sandbox")