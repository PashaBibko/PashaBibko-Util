# Sets required versions of CMake and C++ for the Util library #
cmake_minimum_required (VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Creates a CMake project if it is the top level #
if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

	project(PashaBibko-Util-Project)
endif()

# Creates the static library #
add_library(PashaBibko-UTIL STATIC
	# List of core source files for the Util library #
	"core/FileManagment.cpp"
	"core/ReturnVal.cpp"
	"core/Misc.cpp"
	"core/Log.cpp"
)

# Includes the test-extension (temporary) #
add_subdirectory(extensions/testing)

# Sets the include paths for the Util library        #
# Shared with any projects that include this library #
target_include_directories(PashaBibko-UTIL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Only builds the .exe when this is the root project and not a gh-action build                         #
# This stops it building when this is included as a subproject but still allows testing of the library #
if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR} AND NOT GH_ACTION_BUILD)
	add_executable(PashaBibko-UTIL-Example example/ExampleUse.cpp)
	target_link_libraries(PashaBibko-UTIL-Example PashaBibko-UTIL)
endif()
