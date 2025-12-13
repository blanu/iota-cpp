cmake_minimum_required(VERSION 3.31)
project(iota-cpp-lib)
set(CMAKE_CXX_STANDARD 17)
enable_testing()

set(IOTA_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(IOTA_LIB_SOURCE_DIR ${IOTA_LIB_DIR}/src)

# Get parent libraries directory
get_filename_component(LIBRARIES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/.. ABSOLUTE)
set(ION_LIB_SOURCE_DIR ${ION}/src)
set(TRANSMISSION_LIB_SOURCE_DIR ${TRANSMISSION}/src)
set(BIGNUMBER_LIB_SOURCE_DIR ${BIGNUMBER}/src)
set(BIGNUMBER_ARDUINO_SOURCE_DIR ${BIGNUMBER_ARDUINO}/src)

file(GLOB_RECURSE IOTA_FILES ${IOTA_LIB_SOURCE_DIR}/*.cpp)
message(STATUS "IOTA source dir: ${IOTA_LIB_SOURCE_DIR}")
message(STATUS "IOTA_FILES found: ${IOTA_FILES}")

add_library(iota-cpp-lib STATIC ${IOTA_FILES}
  src/nouns/bindings.cpp
  src/nouns/bindings.h
  src/nouns/range.cpp
  src/nouns/range.h
  src/nouns/symbol_definition.cpp
  src/nouns/symbol_definition.h
  src/nouns/user_symbol.cpp
  src/nouns/user_symbol.h)

include_directories(iota-cpp-lib PUBLIC
  ${IOTA_LIB_SOURCE_DIR}
  ${ION_LIB_SOURCE_DIR}
  ${TRANSMISSION_LIB_SOURCE_DIR}
  ${BIGNUMBER_LIB_SOURCE_DIR}
  ${BIGNUMBER_ARDUINO_SOURCE_DIR}
  ${ONDA}/src
)

target_include_directories(iota-cpp-lib PUBLIC
  ${IOTA_LIB_SOURCE_DIR}
  ${ION_LIB_SOURCE_DIR}
  ${TRANSMISSION_LIB_SOURCE_DIR}
  ${BIGNUMBER_LIB_SOURCE_DIR}
  ${BIGNUMBER_ARDUINO_SOURCE_DIR}
  ${ONDA}/src
)

target_link_libraries(iota-cpp-lib PUBLIC
  ion-cpp
  transmission-cpp-lib
  bignumber-cpp-lib
  onda
)

if(ENABLE_COVERAGE AND (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CX_COMPILER_ID MATCHES "Clang"))
  target_compile_options(iota-cpp-lib PRIVATE --coverage -O0 -g)
  target_link_options(iota-cpp-lib PRIVATE --coverage)
endif()