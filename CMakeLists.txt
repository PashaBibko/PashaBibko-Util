# Sets required versions of CMake and C++ for the Util library #
cmake_minimum_required (VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Creates the static library #
add_library(PashaBibko-UTIL STATIC
	# List of source files for the Util library #
	modules/ConsoleManip.cpp
)

# Sets the include paths for the Util library #
# Shared with any projects that include this library #
target_include_directories(PashaBibko-UTIL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Only builds the .exe when this is the root project #
# This stops it building when this is included as a subproject but still allows testing of the library #
if (CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
	add_executable(PashaBibko-UTIL-Example example/ExampleUse.cpp)
	target_link_libraries(PashaBibko-UTIL-Example PashaBibko-UTIL)
endif()
