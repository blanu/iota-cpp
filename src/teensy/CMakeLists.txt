cmake_minimum_required(VERSION 3.31)
project(iota-teensy)

set(CMAKE_CXX_STANDARD 17)

set(TEENSY_CORE_PATH "$ENV{HOME}/Library/Arduino15/packages/teensy/hardware/avr/1.59.0")
get_filename_component(PROJECT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../.." ABSOLUTE)

set(IOTA_LIB_SOURCE_DIR ${IOTA}/src)
set(IOTA_ARDUINO_SOURCE_DIR ${IOTA_ARDUINO}/src)
set(ION_LIB_SOURCE_DIR ${ION}/src)
set(AUDIO_ARDUINO_SOURCE_DIR ${AUDIO_ARDUINO}/src)
set(AUDIO_TEENSY_SOURCE_DIR ${AUDIO_TEENSY}/src)
set(TRANSMISSION_LIB_SOURCE_DIR ${TRANSMISSION}/src)
set(TRANSMISSION_TEENSY_SOURCE_DIR ${TRANSMISSION_TEENSY}/src)
set(BIGNUMBER_LIB_SOURCE_DIR ${BIGNUMBER}/src)
set(BIGNUMBER_ARDUINO_SOURCE_DIR ${BIGNUMBER_ARDUINO}/src)

set(IOTA_TEENSY_EXAMPLES_DIR ${IOTA_TEENSY}/examples)
set(IOTA_TEENSY_PROTOCOL_SERVER_DIR ${IOTA_TEENSY_EXAMPLES_DIR}/iota-teensy-protocol-server)
set(LOOPBACK_DIR ${IOTA_TEENSY_EXAMPLES_DIR}/loopback)
set(LOOPBACK_SKETCH_FILE ${LOOPBACK_DIR}/loopback.ino)

# Define your sketch file
set(SKETCH_FILE ${IOTA_TEENSY_PROTOCOL_SERVER_DIR}/iota-teensy-protocol-server.ino)

set(BOARD "teensy:avr:teensy40")
set(PORT "/dev//dev/cu.usbmodem159402501")

set(OUTPUT_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/teensy/rp2350/iota-teensy)

include_directories(
  "${TEENSY_CORE_PATH}/cores/teensy4"
  "${TEENSY_CORE_PATH}/libraries"

  ${ION_LIB_SOURCE_DIR}

  ${IOTA_LIB_SOURCE_DIR}
  ${IOTA_ARDUINO_SOURCE_DIR}
  ${IOTA_TEENSY_SOURCE_DIR}

  ${AUDIO_ARDUINO_SOURCE_DIR}
  ${AUDIO_TEENSY_SOURCE_DIR}

  ${TRANSMISSION_ARDUINO_SOURCE_DIR}
  ${TRANSMISSION_TEENSY_SOURCE_DIR}

  ${BIGNUMBER_LIB_SOURCE_DIR}
  ${BIGNUMBER_ARDUINO_SOURCE_DIR}
)

file(GLOB_RECURSE IOTA_FILES
  ${ION_LIB_SOURCE_DIR}/*.cpp

  ${IOTA_LIB_SOURCE_DIR}/*.cpp
  ${IOTA_ARDUINO_SOURCE_DIR}/*.cpp
  ${IOTA_TEENSY_SOURCE_DIR}/*.cpp ${IOTA_TEENSY_SOURCE_DIR}/*.ino

  ${AUDIO_ARDUINO_SOURCE_DIR}/*.cpp
  ${AUDIO_TEENSY_SOURCE_DIR}/*.cpp

  ${TRANSMISSION_LIB_SOURCE_DIR}/*.cpp
  ${TRANSMISSION_TEENSY_SOURCE_DIR}/*.cpp

  ${BIGNUMBER_LIB_SOURCE_DIR}/*.cpp
  ${BIGNUMBER_ARDUINO_SOURCE_DIR}/*.cpp
)

add_executable(iota-teensy ${IOTA_FILES}
  src/effects/i2c/I2CEffects.cpp
  src/effects/i2c/I2CEffects.h
  src/effects/spi/SPIEffects.cpp
  src/effects/spi/SPIEffects.h)

add_custom_target(build_iota_teensy ALL
        COMMAND arduino-cli compile
            --fqbn ${BOARD}
            --output-dir ${OUTPUT_DIR}
            --build-property "compiler.cpp.extra_flags=-std=c++17 -D_BSD_SOURCE -D_DEFAULT_SOURCE"
            --build-property "build.usbtype=USB_MIDI_AUDIO_SERIAL"
            --libraries ${PROJECT_ROOT}/libraries
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
  --fqbn teensy:avr:teensy40:usb=serialmidiaudio
  --output-dir ${OUTPUT_DIR}
  --build-property "compiler.cpp.extra_flags=-std=c++17 -D_BSD_SOURCE -D_DEFAULT_SOURCE -Wno-psabi"
  --build-property "menu.usb=serialmidiaudio"
  --library ${IOTA}
  --library ${IOTA_ARDUINO}
  --library ${IOTA_TEENSY}
  --library ${TRANSMISSION}
  --library ${TRANSMISSION_TEENSY}
  --library ${BIGNUMBER}
  --library ${BIGNUMBER_ARDUINO}
  #--verbose
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