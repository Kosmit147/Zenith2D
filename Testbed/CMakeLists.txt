cmake_minimum_required(VERSION 3.28)
project(Testbed LANGUAGES CXX)

add_executable(
	Testbed
	"src/PrimitiveRendererTest.cpp"
	"src/Testbed.cpp"
)

if(CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*")
	target_link_libraries(Testbed PRIVATE Zenith -lstdc++exp)
else()
	target_link_libraries(Testbed PRIVATE Zenith)
endif()

target_compile_features(Testbed PRIVATE cxx_std_23)
target_compile_options(Testbed PRIVATE ${COMPILE_WARNINGS})
set_property(TARGET Testbed PROPERTY COMPILE_WARNING_AS_ERROR ON)
