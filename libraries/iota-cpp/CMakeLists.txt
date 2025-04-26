cmake_minimum_required(VERSION 3.31)
project(iota-cpp-lib)

set(CMAKE_CXX_STANDARD 17)
enable_testing()

# Compile iota-cpp library for local build machine architecture
set(IOTA_LIB_DIR ${CMAKE_SOURCE_DIR}/libraries/iota-cpp)
set(IOTA_LIB_SOURCE_DIR ${IOTA_LIB_DIR}/src)
include_directories(${IOTA_LIB_SOURCE_DIR})
file(GLOB_RECURSE IOTA_FILES ${IOTA_LIB_SOURCE_DIR}/*.cpp)
add_library(iota-cpp-lib STATIC ${IOTA_FILES}
  src/effects/testing/testing_effects_register.cpp
  src/effects/testing/testing_effects_register.h
  src/effects/testing/log/log.cpp
  src/effects/testing/log/log.h
  src/effects/random/random_symbols.h
  src/effects/testing/random/random.cpp
  src/effects/testing/random/random.h)
target_include_directories(iota-cpp-lib PUBLIC ${IOTA_LIB_SOURCE_DIR})

# Generate ctags for vim
set(TAGS_FILE ${IOTA_LIB_SOURCE_DIR}/tags)
add_custom_target(
        GenerateLibTags
        COMMAND ctags -R -f ${TAGS_FILE} ${IOTA_LIB_SOURCE_DIR}
        WORKING_DIRECTORY ${IOTA_LIB_SOURCE_DIR}
        COMMENT "Generating ctags"
)
add_dependencies(${PROJECT_NAME} GenerateLibTags)
