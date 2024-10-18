cmake_minimum_required(VERSION 3.28)
project(Sandbox LANGUAGES CXX)

add_executable(Sandbox "src/main.cpp")
target_link_libraries(Sandbox PRIVATE Engine -lstdc++exp)
target_compile_features(Sandbox PRIVATE cxx_std_23)