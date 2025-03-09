cmake_minimum_required(VERSION 3.31)
project(iota-cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory("iota-stdio")
add_subdirectory("libraries/iota-cpp")
add_subdirectory("libraries/iota-arduino")