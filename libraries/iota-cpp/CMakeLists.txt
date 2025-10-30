cmake_minimum_required(VERSION 3.31)
project(iota-cpp-lib)
set(CMAKE_CXX_STANDARD 17)
enable_testing()

set(IOTA_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(IOTA_LIB_SOURCE_DIR ${IOTA_LIB_DIR}/src)

# Get parent libraries directory
get_filename_component(LIBRARIES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/.. ABSOLUTE)
set(ION_LIB_DIR ${LIBRARIES_DIR}/ion-cpp)
set(ION_LIB_SOURCE_DIR ${ION_LIB_DIR}/src)
set(TRANSMISSION_LIB_DIR ${LIBRARIES_DIR}/transmission-cpp)
set(TRANSMISSION_LIB_SOURCE_DIR ${TRANSMISSION_LIB_DIR}/src)
set(BIGNUMBER_LIB_DIR ${LIBRARIES_DIR}/bignumber-cpp)
set(BIGNUMBER_LIB_SOURCE_DIR ${BIGNUMBER_LIB_DIR}/src)
set(BIGNUMBER_ARDUINO_DIR ${LIBRARIES_DIR}/bignumber-arduino)
set(BIGNUMBER_ARDUINO_SOURCE_DIR ${BIGNUMBER_ARDUINO_DIR}/src)

file(GLOB_RECURSE IOTA_FILES ${IOTA_LIB_SOURCE_DIR}/*.cpp)
message(STATUS "IOTA source dir: ${IOTA_LIB_SOURCE_DIR}")
message(STATUS "IOTA_FILES found: ${IOTA_FILES}")

add_library(iota-cpp-lib STATIC ${IOTA_FILES}
  src/nouns/data.cpp
  src/nouns/data.h)

target_include_directories(iota-cpp-lib PUBLIC
  ${IOTA_LIB_SOURCE_DIR}
  ${ION_LIB_SOURCE_DIR}
  ${TRANSMISSION_LIB_SOURCE_DIR}
  ${BIGNUMBER_LIB_SOURCE_DIR}
  ${BIGNUMBER_ARDUINO_SOURCE_DIR}
)

target_link_libraries(iota-cpp-lib PUBLIC
  ion-cpp
  transmission-cpp-lib
  bignumber-cpp-lib
)

if(ENABLE_COVERAGE AND (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CX_COMPILER_ID MATCHES "Clang"))
  target_compile_options(iota-cpp-lib PRIVATE --coverage -O0 -g)
  target_link_options(iota-cpp-lib PRIVATE --coverage)
endif()