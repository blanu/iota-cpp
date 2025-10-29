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

# Check if arduino-cli is installed (should be done by arduino-cli.cmake first)
command_exists(arduino-cli ARDUINO_CLI_FOUND)

if(NOT ARDUINO_CLI_FOUND)
  message(FATAL_ERROR "arduino-cli not found. Ensure arduino-cli.cmake is included before teensy41.cmake")
endif()

# Check if TEENSY core is already installed
execute_process(
  COMMAND arduino-cli core list
  OUTPUT_VARIABLE CORE_LIST
  ERROR_QUIET
)

string(FIND "${CORE_LIST}" "teensy:avr" TEENSY_INSTALLED)

if(TEENSY_INSTALLED EQUAL -1)
  message(STATUS "Installing TEENSY core...")

  # Add TEENSY board manager URL
  execute_process(
    COMMAND arduino-cli config add board_manager.additional_urls https://www.pjrc.com/teensy/package_teensy_index.json
    OUTPUT_QUIET
    ERROR_QUIET
  )

  # Update index after adding TEENSY URL
  message(STATUS "Updating arduino-cli core index for Teensy...")
  execute_process(
    COMMAND arduino-cli core update-index
    OUTPUT_QUIET
    ERROR_QUIET
  )

  # Install TEENSY core
  execute_process(
    COMMAND arduino-cli core install teensy:avr
    RESULT_VARIABLE TEENSY_INSTALL_RESULT
    OUTPUT_VARIABLE TEENSY_INSTALL_OUTPUT
    ERROR_VARIABLE TEENSY_INSTALL_ERROR
  )

  if(NOT TEENSY_INSTALL_RESULT EQUAL 0)
    message(FATAL_ERROR "Failed to install TEENSY core: ${TEENSY_INSTALL_ERROR}")
  else()
    message(STATUS "TEENSY core installed successfully")
  endif()
else()
  message(STATUS "TEENSY core is already installed")
endif()

# Set useful variables for the rest of your CMake project
set(ARDUINO_CLI_EXECUTABLE arduino-cli)
set(TEENSY_CORE_INSTALLED TRUE)