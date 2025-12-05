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

set(ONDA ${CMAKE_SOURCE_DIR}/lib/onda/src/cpp)
set(ONDA_ARDUINO ${CMAKE_SOURCE_DIR}/lib/onda/src/arduino)
set(AUDIO ${CMAKE_SOURCE_DIR}/lib/Audio-core)
set(AUDIO_TEENSY ${CMAKE_SOURCE_DIR}/lib/Audio-Teensy4)
set(BIGNUMBER ${CMAKE_SOURCE_DIR}/lib/BigNumber/libraries/bignumber-cpp)
set(BIGNUMBER_ARDUINO ${CMAKE_SOURCE_DIR}/lib/BigNumber/libraries/bignumber-arduino)
set(TRANSMISSION ${CMAKE_SOURCE_DIR}/lib/TransmissionArduino/src/cpp)
set(TRANSMISSION_TEENSY ${CMAKE_SOURCE_DIR}/lib/TransmissionArduino/src/teensy)
set(ION ${CMAKE_SOURCE_DIR}/lib/ion-cpp/src/cpp)
set(ION_ARDUINO ${CMAKE_SOURCE_DIR}/lib/ion-cpp/src/arduino)
set(IOTA ${CMAKE_SOURCE_DIR}/src/cpp)
set(IOTA_ARDUINO ${CMAKE_SOURCE_DIR}/src/arduino)
set(IOTA_TEENSY ${CMAKE_SOURCE_DIR}/src/teensy)

add_subdirectory(${TRANSMISSION})
add_subdirectory(${ION})
add_subdirectory(${IOTA})
add_subdirectory(${BIGNUMBER})
add_subdirectory(${ONDA})

add_subdirectory("iota-stdio")
add_subdirectory("iota-repl")
add_subdirectory("iota-tests")