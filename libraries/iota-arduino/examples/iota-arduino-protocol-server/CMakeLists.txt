cmake_minimum_required(VERSION 3.31)
project(iota-arduino-protocol-server)

set(CMAKE_CXX_STANDARD 17)
set(IOTA_LIB_DIR ${CMAKE_SOURCE_DIR}/iota-cpp)
set(IOTA_ARDUINO_DIR ${CMAKE_SOURCE_DIR}/iota-arduino)
set(IOTA_ARDUINO_PROTOCOL_SERVER_DIR ${CMAKE_SOURCE_DIR}/iota-arduino-protocol-server)

# Define your sketch file
set(SKETCH_FILE ${IOTA_ARDUINO_PROTOCOL_SERVER_DIR}/iota-arduino-protocol-server.ino)

set(BOARD "rp2040:rp2040:adafruit_feather_rp2350_hstx")

set(OUTPUT_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/arduino/rp2350/iota-arduino-protocol-server)
file(GLOB_RECURSE IOTA_FILES ${IOTA_LIB_DIR}/*.cpp ${IOTA_ARDUINO_DIR}/*.cpp ${IOTA_ARDUINO_PROTOCOL_SERVER_DIR}/*.cpp ${IOTA_ARDUINO_PROTOCOL_SERVER_DIR}/*.ino)

add_executable(iota-arduino-protocol-server ${IOTA_FILES})
add_dependencies(iota-arduino-protocol-server build_iota_arduino_protocol_server)

add_custom_target(build_iota_arduino_protocol_server ALL
        COMMAND arduino-cli compile
            --fqbn ${BOARD}
            --output-dir ${OUTPUT_DIR}
            --build-property "build.extra_flags=-std=c++17\ -I${CMAKE_SOURCE_DIR}"
            --libraries ${CMAKE_SOURCE_DIR}
            ${SKETCH_FILE}
        WORKING_DIRECTORY ${IOTA_ARDUINO_PROTOCOL_SERVER_DIR}
        COMMENT "Building iota-arduino-protocol-server with arduino-cli"
)

# Generate ctags for vim
set(TAGS_FILE ${IOTA_ARDUINO_PROTOCOL_SERVER_DIR}/tags)
add_custom_target(
        GenerateArduinoProtocolServerTags
        COMMAND ctags -R -f ${TAGS_FILE} ${IOTA_LIB_DIR} ${IOTA_ARDUINO_DIR} ${IOTA_ARDUINO_PROTOCOL_SERVER_DIR}
        WORKING_DIRECTORY ${IOTA_ARDUINO_PROTOCOL_SERVER_DIR}
        COMMENT "Generating ctags"
)
add_dependencies(build_iota_arduino_protocol_server GenerateArduinoProtocolServerTags)