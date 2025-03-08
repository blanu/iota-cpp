cmake_minimum_required(VERSION 3.31)
project(iota-arduino)

set(CMAKE_CXX_STANDARD 17)
set(IOTA_LIB_SOURCE_DIR ${CMAKE_SOURCE_DIR}/libraries/iota-cpp/src)
set(IOTA_ARDUINO_DIR ${CMAKE_SOURCE_DIR}/libraries/iota-arduino)
set(IOTA_ARDUINO_SOURCE_DIR ${IOTA_ARDUINO_DIR}/src)
set(IOTA_ARDUINO_EXAMPLES_DIR ${IOTA_ARDUINO_DIR}/examples)
set(IOTA_ARDUINO_PROTOCOL_SERVER_DIR ${IOTA_ARDUINO_EXAMPLES_DIR}/iota-arduino-protocol-server)

# Define your sketch file
set(SKETCH_FILE ${IOTA_ARDUINO_PROTOCOL_SERVER_DIR}/iota-arduino-protocol-server.ino)

set(BOARD "rp2040:rp2040:adafruit_feather_rp2350_hstx")

set(OUTPUT_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/arduino/rp2350/iota-arduino)
file(GLOB_RECURSE IOTA_FILES ${IOTA_LIB_SOURCE_DIR}/*.cpp ${IOTA_ARDUINO_SOURCE_DIR}/*.cpp ${IOTA_ARDUINO_SOURCE_DIR}/*.ino)

add_executable(iota-arduino ${IOTA_FILES})
add_dependencies(iota-arduino build_iota_arduino)
target_link_libraries(iota-arduino PRIVATE iota-cpp)

add_custom_target(build_iota_arduino ALL
        COMMAND arduino-cli compile
            --fqbn ${BOARD}
            --output-dir ${OUTPUT_DIR}
            --build-property build.extra_flags="-std=c++17"
            --libraries ${CMAKE_SOURCE_DIR}/libraries
            ${SKETCH_FILE}
        WORKING_DIRECTORY ${IOTA_ARDUINO_SOURCE_DIR}
        COMMENT "Building iota-arduino with arduino-cli"
)

# Generate ctags for vim
set(TAGS_FILE ${IOTA_ARDUINO_SOURCE_DIR}/tags)
add_custom_target(
        GenerateArduinoTags
        COMMAND ctags -R -f ${TAGS_FILE} ${IOTA_LIB_SOURCE_DIR} ${IOTA_ARDUINO_SOURCE_DIR}
        WORKING_DIRECTORY ${IOTA_ARDUINO_SOURCE_DIR}
        COMMENT "Generating ctags"
)
add_dependencies(build_iota_arduino GenerateArduinoTags)