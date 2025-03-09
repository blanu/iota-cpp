cmake_minimum_required(VERSION 3.31)
project(iota_cpp)

set(CMAKE_CXX_STANDARD 17)

# Compile iota-cpp library for local build machine architecture
set(IOTA_LIB_DIR ${CMAKE_SOURCE_DIR}/libraries/iota-cpp)
set(IOTA_LIB_SOURCE_DIR ${IOTA_LIB_DIR}/src)
include_directories(${IOTA_LIB_SOURCE_DIR})
file(GLOB_RECURSE IOTA_FILES ${IOTA_LIB_SOURCE_DIR}/*.cpp)
add_library(iota_cpp STATIC ${IOTA_FILES}
        src/nouns/integer.h
        src/nouns/integer.cpp
        src/nouns/nouns.h
        src/nouns/real.h
        src/nouns/real.cpp
        src/nouns/list.h
        src/nouns/list.cpp
        src/nouns/character.h
        src/nouns/character.cpp
        src/nouns/iota_string.h
        src/nouns/iota_string.cpp
        src/nouns/dictionary.h
        src/nouns/expression.h
        src/nouns/conditional.h
        src/nouns/symbol.h
        src/nouns/quoted_symbol.h
        src/storage/mixed_array.h
        src/verbs.h
        src/verbs.cpp
        src/nouns/dictionary.cpp
        src/nouns/expression.cpp
        src/storage/mixed_array.cpp
        src/nouns/quoted_symbol.cpp
        src/nouns/symbol.cpp
        src/nouns/conditional.cpp
        src/storage/word.h
        src/storage/word.cpp
        src/storage/float.h
        src/storage/float.cpp
        src/storage/word_array.h
        src/storage/word_array.cpp
        src/storage/float_array.h
        src/storage/float_array.cpp)
target_include_directories(iota_cpp PUBLIC ${IOTA_LIB_SOURCE_DIR})

# Generate ctags for vim
set(TAGS_FILE ${IOTA_LIB_SOURCE_DIR}/tags)
add_custom_target(
        GenerateLibTags
        COMMAND ctags -R -f ${TAGS_FILE} ${IOTA_LIB_SOURCE_DIR}
        WORKING_DIRECTORY ${IOTA_LIB_SOURCE_DIR}
        COMMENT "Generating ctags"
)
add_dependencies(${PROJECT_NAME} GenerateLibTags)
