cmake_minimum_required(VERSION 3.31)
project(iota-cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Initialize git submodules found in lib/
find_package(Git QUIET)

if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
  message(STATUS "Updating git submodules...")
  execute_process(
    COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    RESULT_VARIABLE GIT_SUBMOD_RESULT
  )
  if(NOT GIT_SUBMOD_RESULT EQUAL "0")
    message(FATAL_ERROR "git submodule update --init --recursive failed")
  endif()
endif()

# Verify lib/ directory has content
file(GLOB lib_contents "${PROJECT_SOURCE_DIR}/lib/*")
if(NOT lib_contents)
  message(FATAL_ERROR "lib/ directory is empty. Submodule initialization may have failed.")
endif()

include(arduino-cli.cmake)
include(teensy41.cmake)

add_subdirectory("iota-stdio")
add_subdirectory("libraries/iota-cpp")
add_subdirectory("libraries/iota-arduino")
add_subdirectory("libraries/iota-teensy")
add_subdirectory("tests/")