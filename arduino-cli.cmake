# Function to check if a command exists
function(command_exists COMMAND RESULT_VAR)
  if(WIN32)
    execute_process(
      COMMAND where ${COMMAND}
      RESULT_VARIABLE EXIT_CODE
      OUTPUT_QUIET
      ERROR_QUIET
    )
  else()
    execute_process(
      COMMAND which ${COMMAND}
      RESULT_VARIABLE EXIT_CODE
      OUTPUT_QUIET
      ERROR_QUIET
    )
  endif()

  if(EXIT_CODE EQUAL 0)
    set(${RESULT_VAR} TRUE PARENT_SCOPE)
  else()
    set(${RESULT_VAR} FALSE PARENT_SCOPE)
  endif()
endfunction()

# Check if homebrew is installed
command_exists(brew HOMEBREW_FOUND)

if(NOT HOMEBREW_FOUND)
  message(FATAL_ERROR "Homebrew is not installed. Please install Homebrew first from https://brew.sh")
endif()

# Check if arduino-cli is installed
command_exists(arduino-cli ARDUINO_CLI_FOUND)

if(NOT ARDUINO_CLI_FOUND)
  message(STATUS "arduino-cli not found. Installing via Homebrew...")
  execute_process(
    COMMAND brew install arduino-cli
    RESULT_VARIABLE INSTALL_RESULT
    OUTPUT_VARIABLE INSTALL_OUTPUT
    ERROR_VARIABLE INSTALL_ERROR
  )

  if(NOT INSTALL_RESULT EQUAL 0)
    message(FATAL_ERROR "Failed to install arduino-cli: ${INSTALL_ERROR}")
  else()
    message(STATUS "arduino-cli installed successfully")
  endif()
else()
  message(STATUS "arduino-cli is already installed")
endif()

# Initialize arduino-cli configuration if needed
execute_process(
  COMMAND arduino-cli config init
  RESULT_VARIABLE INIT_RESULT
  OUTPUT_QUIET
  ERROR_QUIET
)

# ESP32 official URL
execute_process(
  COMMAND arduino-cli config add board_manager.additional_urls https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
  OUTPUT_QUIET
  ERROR_QUIET
)


# Adafruit board manager URL
execute_process(
  COMMAND arduino-cli config add board_manager.additional_urls https://adafruit.github.io/arduino-board-index/package_adafruit_index.json
  OUTPUT_QUIET
  ERROR_QUIET
)

# Update the core index
message(STATUS "Updating arduino-cli core index...")
execute_process(
  COMMAND arduino-cli core update-index
  RESULT_VARIABLE UPDATE_RESULT
  OUTPUT_VARIABLE UPDATE_OUTPUT
  ERROR_VARIABLE UPDATE_ERROR
)

if(NOT UPDATE_RESULT EQUAL 0)
  message(WARNING "Failed to update core index: ${UPDATE_ERROR}")
endif()

# Display installed cores
message(STATUS "Installed Arduino cores:")
execute_process(
  COMMAND arduino-cli core list
  OUTPUT_VARIABLE INSTALLED_CORES
)
message(STATUS "${INSTALLED_CORES}")

# Set useful variables for the rest of your CMake project
set(ARDUINO_CLI_EXECUTABLE arduino-cli)