cmake_minimum_required(VERSION 3.31)
project(iota-cpp-lib)

set(CMAKE_CXX_STANDARD 17)
enable_testing()

# Compile iota-cpp library for local build machine architecture
set(IOTA_LIB_DIR ${CMAKE_SOURCE_DIR}/libraries/iota-cpp)
set(IOTA_LIB_SOURCE_DIR ${IOTA_LIB_DIR}/src)
set(ION_LIB_DIR ${CMAKE_SOURCE_DIR}/libraries/ion-cpp)
set(ION_LIB_SOURCE_DIR ${ION_LIB_DIR}/src)

include_directories(${IOTA_LIB_SOURCE_DIR} ${ION_LIB_SOURCE_DIR})
file(GLOB_RECURSE IOTA_FILES ${IOTA_LIB_SOURCE_DIR}/*.cpp)
add_library(iota-cpp-lib STATIC ${IOTA_FILES}
  src/iota-cpp.h)

target_include_directories(iota-cpp-lib PUBLIC ${IOTA_LIB_SOURCE_DIR} ${ION_LIB_SOURCE_DIR})
target_link_libraries(iota-cpp-lib PUBLIC ion-cpp)

if(ENABLE_COVERAGE AND (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang"))
  target_compile_options(iota-cpp-lib PRIVATE --coverage -O0 -g)
  target_link_options(iota-cpp-lib PRIVATE --coverage)
endif()