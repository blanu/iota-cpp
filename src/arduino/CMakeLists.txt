cmake_minimum_required(VERSION 3.31)
project(iota-arduino)

set(CMAKE_CXX_STANDARD 17)
set(IOTA_LIB_SOURCE_DIR ${IOTA}/src)
set(IOTA_ARDUINO_SOURCE_DIR ${IOTA_ARDUINO}/src)
set(IOTA_ARDUINO_EXAMPLES_DIR ${IOTA_ARDUINO}/examples)
set(IOTA_ARDUINO_PROTOCOL_SERVER_DIR ${IOTA_ARDUINO_EXAMPLES_DIR}/iota-arduino-protocol-server)

# Define your sketch file
set(SKETCH_FILE ${IOTA_ARDUINO_PROTOCOL_SERVER_DIR}/iota-arduino-protocol-server.ino)

set(BOARD "rp2040:rp2040:adafruit_feather_rp2350_hstx")
set(PORT "/dev/cu.usbmodem1101")

set(OUTPUT_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/arduino/rp2350/iota-arduino)
file(GLOB_RECURSE IOTA_FILES ${IOTA_LIB_SOURCE_DIR}/*.cpp ${IOTA_ARDUINO_SOURCE_DIR}/*.cpp ${IOTA_ARDUINO_SOURCE_DIR}/*.ino)

add_executable(iota-arduino ${IOTA_FILES}
  ../iota-teensy/src/effects/gpio/GPIOEffects.cpp
  ../iota-teensy/src/effects/gpio/GPIOEffects.h
  ../iota-teensy/src/effects/serial/SerialEffects.cpp
  ../iota-teensy/src/effects/serial/SerialEffects.h
  src/effects/time/TimeEffects.cpp
  src/effects/time/TimeEffects.h
  src/effects/random/RandomEffects.cpp
  src/effects/random/RandomEffects.h)
add_dependencies(iota-arduino build_iota_arduino)
target_link_libraries(iota-arduino PRIVATE iota-cpp)

add_custom_target(build_iota_arduino ALL
        COMMAND arduino-cli compile
            --fqbn ${BOARD}
            --output-dir ${OUTPUT_DIR}
            --build-property "compiler.cpp.extra_flags=-std=c++17 -D_BSD_SOURCE -D_DEFAULT_SOURCE"
            --library ${ION}
            --library ${IOTA}
            --library ${IOTA_ARDUINO}
            --library ${TRANSMISSION}
            --library ${TRANSMISSION_ARDUINO}
            --library ${AUDIO_ARDUINO}
  ${SKETCH_FILE}
        WORKING_DIRECTORY ${IOTA_ARDUINO_SOURCE_DIR}
        COMMENT "Building iota-arduino with arduino-cli"
)

add_custom_target(upload_iota_arduino_protocol_server ALL
        COMMAND arduino-cli upload
        -p ${PORT}
        --fqbn ${BOARD}
        ${IOTA_ARDUINO_PROTOCOL_SERVER_DIR}
        COMMENT "Uploading iota-arduino-protocol-server with arduino-cli"
)
add_dependencies(upload_iota_arduino_protocol_server build_iota_arduino)

# Generate ctags for vim
set(TAGS_FILE ${IOTA_ARDUINO_SOURCE_DIR}/tags)
add_custom_target(
        GenerateArduinoTags
        COMMAND ctags -R -f ${TAGS_FILE} ${IOTA_LIB_SOURCE_DIR} ${IOTA_ARDUINO_SOURCE_DIR}
        WORKING_DIRECTORY ${IOTA_ARDUINO_SOURCE_DIR}
        COMMENT "Generating ctags"
)
add_dependencies(build_iota_arduino GenerateArduinoTags)