cmake_minimum_required(VERSION 3.31)
project(iota-stdio)

set(CMAKE_CXX_STANDARD 17)

set(IOTA_STDIO_DIR ${CMAKE_SOURCE_DIR}/iota-stdio)
set(IOTA_LIB_DIR ${CMAKE_SOURCE_DIR}/libraries/iota-cpp)
set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin)

add_executable(iota-stdio main.cpp)
target_link_libraries(iota-stdio iota_cpp)

# Generate ctags for vim
set(TAGS_FILE ${IOTA_STDIO_DIR}/tags)
add_custom_target(
        GenerateStdioTags
        COMMAND ctags -R -f ${TAGS_FILE} ${IOTA_STDIO_DIR} ${IOTA_LIB_DIR}
        WORKING_DIRECTORY ${IOTA_DIR}
        COMMENT "Generating ctags"
)
add_dependencies(${PROJECT_NAME} GenerateStdioTags)
