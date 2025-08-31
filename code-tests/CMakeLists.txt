# Sets required versions of CMake and C++ that are required #
cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(PB-Util-Library-Tests)

# Sets the output folder for the binaries #
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

# Creates the binary of the tests #
add_executable(PBUtil-Tests
    "src/VecTests.cpp"
)

target_include_directories(PBUtil-Tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Creates and links the Util library (with extensions enabled) #
set(PB_UTIL_EXTENSIONS ON)
set(PB_TESTS ON)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/.. ${CMAKE_CURRENT_BINARY_DIR}/lib-build) # <- TODO: Fix absolute file path
target_link_libraries(PBUtil-Tests PashaBibko-UTIL)
