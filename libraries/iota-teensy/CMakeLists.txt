cmake_minimum_required(VERSION 3.31)
project(iota-teensy)

set(CMAKE_CXX_STANDARD 17)

set(IOTA_LIB_DIR ${CMAKE_SOURCE_DIR}/libraries/iota-cpp)
set(IOTA_ARDUINO_DIR ${CMAKE_SOURCE_DIR}/libraries/iota-arduino)
set(IOTA_TEENSY_DIR ${CMAKE_SOURCE_DIR}/libraries/iota-teensy)
set(AUDIO_ARDUINO_DIR ${CMAKE_SOURCE_DIR}/libraries/audio-arduino)
set(AUDIO_TEENSY_DIR ${CMAKE_SOURCE_DIR}/libraries/audio-teensy)
set(TRANSMISSION_LIB_DIR ${CMAKE_SOURCE_DIR}/libraries/transmission-cpp)
set(TRANSMISSION_TEENSY_DIR ${CMAKE_SOURCE_DIR}/libraries/transmission-teensy)

set(IOTA_LIB_SOURCE_DIR ${IOTA_LIB_DIR}/src)
set(IOTA_ARDUINO_SOURCE_DIR ${IOTA_ARDUINO_DIR}/src)
set(IOTA_TEENSY_SOURCE_DIR ${IOTA_TEENSY_DIR}/src)
set(IOTA_TEENSY_EXAMPLES_DIR ${IOTA_TEENSY_DIR}/examples)
set(IOTA_TEENSY_PROTOCOL_SERVER_DIR ${IOTA_TEENSY_EXAMPLES_DIR}/iota-teensy-protocol-server)
set(LOOPBACK_DIR ${IOTA_TEENSY_EXAMPLES_DIR}/loopback)
set(LOOPBACK_SKETCH_FILE ${LOOPBACK_DIR}/loopback.ino)

# Define your sketch file
set(SKETCH_FILE ${IOTA_TEENSY_PROTOCOL_SERVER_DIR}/iota-teensy-protocol-server.ino)

set(BOARD "teensy:avr:teensy41")
set(PORT "/dev/cu.usbmodem1101")

set(OUTPUT_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/teensy/rp2350/iota-teensy)
file(GLOB_RECURSE IOTA_FILES ${IOTA_LIB_SOURCE_DIR}/*.cpp ${IOTA_TEENSY_SOURCE_DIR}/*.cpp ${IOTA_TEENSY_SOURCE_DIR}/*.ino)

add_custom_target(build_iota_teensy ALL
        COMMAND arduino-cli compile
            --fqbn ${BOARD}
            --output-dir ${OUTPUT_DIR}
            --build-property "compiler.cpp.extra_flags=-std=c++17 -D_BSD_SOURCE -D_DEFAULT_SOURCE"
            --libraries ${CMAKE_SOURCE_DIR}/libraries
            ${SKETCH_FILE}
        WORKING_DIRECTORY ${IOTA_TEENSY_SOURCE_DIR}
        COMMENT "Building iota-teensy with teensy-cli"
)

add_custom_target(upload_iota_teensy_protocol_server ALL
        COMMAND arduino-cli upload
        -p ${PORT}
        --fqbn ${BOARD}
        ${IOTA_TEENSY_PROTOCOL_SERVER_DIR}
        COMMENT "Uploading iota-teensy-protocol-server with teensy-cli"
)
add_dependencies(upload_iota_teensy_protocol_server build_iota_teensy)

add_custom_target(build_loopback ALL
  COMMAND arduino-cli compile
  --fqbn ${BOARD}
  --output-dir ${OUTPUT_DIR}
  --build-property "compiler.cpp.extra_flags=-std=c++17 -D_BSD_SOURCE -D_DEFAULT_SOURCE"
  --library ${IOTA_LIB_DIR}
  --library ${IOTA_ARDUINO_DIR}
  --library ${IOTA_TEENSY_DIR}
  --library ${AUDIO_ARDUINO_DIR}
  --library ${AUDIO_TEENSY_DIR}
  --library ${TRANSMISSION_LIB_DIR}
  --library ${TRANSMISSION_TEENSY_DIR}
  ${LOOPBACK_SKETCH_FILE}
  WORKING_DIRECTORY ${IOTA_TEENSY_SOURCE_DIR}
  COMMENT "Building loopback with arduino-cli"
)

add_custom_target(upload_loopback ALL
  COMMAND arduino-cli upload
  -p ${PORT}
  --fqbn ${BOARD}
  ${LOOPBACK_DIR}
  COMMENT "Uploading loopback with arduino-cli"
)
add_dependencies(upload_loopback build_loopback)