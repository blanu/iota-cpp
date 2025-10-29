cmake_minimum_required(VERSION 3.31)
project(iota-cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Initialize git submodules found in lib/
find_package(Git QUIET)

if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
  # Only update specific submodules, not all
  if(EXISTS "${PROJECT_SOURCE_DIR}/.gitmodules")
    message(STATUS "Checking git submodules...")

    # Check if lib/ submodules need initialization
    if(EXISTS "${PROJECT_SOURCE_DIR}/lib" AND IS_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")
      file(GLOB lib_subdirs "${PROJECT_SOURCE_DIR}/lib/*")
      if(NOT lib_subdirs)
        message(STATUS "Initializing lib/ submodules...")
        execute_process(
          COMMAND ${GIT_EXECUTABLE} submodule update --init lib/
          WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
          RESULT_VARIABLE GIT_SUBMOD_RESULT
        )
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
          message(WARNING "git submodule update for lib/ failed")
        endif()
      endif()
    endif()
  endif()
endif()

# Verify lib/ directory has content (only if it exists)
if(EXISTS "${PROJECT_SOURCE_DIR}/lib")
  file(GLOB lib_contents "${PROJECT_SOURCE_DIR}/lib/*")
  if(NOT lib_contents)
    message(WARNING "lib/ directory is empty. Submodule initialization may have failed.")
  endif()
endif()

include(arduino-cli.cmake)
include(teensy41.cmake)

add_subdirectory("libraries/transmission-cpp")
add_subdirectory("libraries/ion-cpp")
add_subdirectory("libraries/iota-cpp")
add_subdirectory("libraries/bignumber-cpp")

add_subdirectory("iota-stdio")
add_subdirectory("iota-tests")

add_subdirectory("libraries/iota-arduino")
add_subdirectory("libraries/iota-teensy")