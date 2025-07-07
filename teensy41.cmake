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

# Check if TEENSY41 core is already installed
execute_process(
  COMMAND arduino-cli core list
  OUTPUT_VARIABLE CORE_LIST
  ERROR_QUIET
)

string(FIND "${CORE_LIST}" "teensy41:teensy41" TEENSY41_INSTALLED)

if(TEENSY41_INSTALLED EQUAL -1)
  message(STATUS "Installing TEENSY41 core...")

  # Add TEENSY41 board manager URL if not already added
  execute_process(
    COMMAND arduino-cli config add board_manager.additional_urls https://www.pjrc.com/teensy/package_teensy_index.json
    OUTPUT_QUIET
    ERROR_QUIET
  )

  # Update index again after adding TEENSY41 URL
  execute_process(
    COMMAND arduino-cli core update-index
    OUTPUT_QUIET
    ERROR_QUIET
  )

  # Install TEENSY41 core
  execute_process(
    COMMAND arduino-cli core install teensy:avr
    RESULT_VARIABLE TEENSY41_INSTALL_RESULT
    OUTPUT_VARIABLE TEENSY41_INSTALL_OUTPUT
    ERROR_VARIABLE TEENSY41_INSTALL_ERROR
  )

  if(NOT TEENSY41_INSTALL_RESULT EQUAL 0)
    message(FATAL_ERROR "Failed to install TEENSY41 core: ${TEENSY41_INSTALL_ERROR}")
  else()
    message(STATUS "TEENSY41 core installed successfully")
  endif()
else()
  message(STATUS "TEENSY41 core is already installed")
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
set(TEENSY41_CORE_INSTALLED TRUE)