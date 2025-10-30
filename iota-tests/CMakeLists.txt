cmake_minimum_required(VERSION 3.31)
project(iota-cpp-lib-tests)

set(CMAKE_CXX_STANDARD 17)
enable_testing()

set(CTEST_PROJECT_NAME iota-cpp)
set(CTEST_NIGHTLY_START_TIME 01:00:00 UTC)
set(CTEST_SUBMIT_URL https://my.cdash.org/submit.php?project=iota-cpp)
set(CTEST_DROP_SITE_CDASH TRUE)

include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.8.0
)

FetchContent_MakeAvailable(Catch2)

set(IOTA_LIB_DIR ${CMAKE_SOURCE_DIR}/libraries/iota-cpp)
set(IOTA_LIB_SOURCE_DIR ${IOTA_LIB_DIR}/src)
set(ION_LIB_DIR ${CMAKE_SOURCE_DIR}/libraries/ion-cpp)
set(ION_LIB_SOURCE_DIR ${ION_LIB_DIR}/src)
set(TRANSMISSION_LIB_DIR ${CMAKE_SOURCE_DIR}/libraries/transmission-cpp)
set(TRANSMISSION_LIB_SOURCE_DIR ${TRANSMISSION_LIB_DIR}/src)
set(BIGNUMBER_LIB_DIR ${CMAKE_SOURCE_DIR}/libraries/bignumber-cpp)
set(BIGNUMBER_LIB_SOURCE_DIR ${BIGNUMBER_LIB_DIR}/src)

set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin)

add_executable(iota-tests main.cpp
  monad_tests/noun_tests.cpp
  monad_tests/atom_tests.cpp
  monad_tests/char_tests.cpp
  monad_tests/enclose_tests.cpp
  monad_tests/not_tests.cpp
  monad_tests/enumerate_tests.cpp
  monad_tests/first_tests.cpp
  monad_tests/floor_tests.cpp
  monad_tests/format_tests.cpp
  monad_tests/gradeDown_tests.cpp
  monad_tests/gradeUp_tests.cpp
  monad_tests/group_tests.cpp
  monad_tests/negate_tests.cpp
  monad_tests/reciprocal_tests.cpp
  monad_tests/reverse_tests.cpp
  monad_tests/shape_tests.cpp
  monad_tests/size_tests.cpp
  monad_tests/transpose_tests.cpp
  monad_tests/undefined_tests.cpp
  monad_tests/unique_tests.cpp
  dyad_tests/cut_tests.cpp
  dyad_tests/divide_tests.cpp
  dyad_tests/drop_tests.cpp
  dyad_tests/equal_tests.cpp
  monad_tests/expand_tests.cpp
  dyad_tests/form_tests.cpp
  dyad_tests/format2_tests.cpp
  dyad_tests/find_tests.cpp
  dyad_tests/index_tests.cpp
  dyad_tests/integerDivide_tests.cpp
  effect_tests/log_tests.cpp
  effect_tests/random_tests.cpp
  effect_tests/state_tests.cpp
  noun_tests/integer_tests.cpp
  noun_tests/list_tests.cpp
  noun_tests/data_tests.cpp
)
target_include_directories(iota-tests PRIVATE
  ${IOTA_LIB_SOURCE_DIR}
  ${ION_LIB_SOURCE_DIR}
  ${TRANSMISSION_LIB_SOURCE_DIR}
  ${BIGNUMBER_LIB_SOURCE_DIR}
)

target_link_libraries(iota-tests PRIVATE
  iota-cpp-lib
  transmission-cpp-lib
  bignumber-cpp-lib
  Catch2::Catch2WithMain
)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  option(ENABLE_COVERAGE "Enable coverage reporting" ON)

  target_compile_options(iota-tests PRIVATE --coverage -O0 -g)
  target_link_options(iota-tests PRIVATE --coverage)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g")

  find_program(GCOV_PATH gcov)
  find_program(LCOV_PATH lcov)
  find_program(GENHTML_PATH genhtml)

  if(LCOV_PATH AND GCOV_PATH AND GENHTML_PATH)
    add_custom_target(iota-coverage
      COMMAND ${LCOV_PATH} --directory . --zerocounters
      COMMAND tests
      COMMAND ${LCOV_PATH} --directory . --capture --output-file coverage.info
      COMMAND ${LCOV_PATH} --extract coverage.info
      '${CMAKE_SOURCE_DIR}/libraries/iota-cpp/*'
      --output-file coverage.filtered.info
      COMMAND ${GENHTML_PATH} coverage.filtered.info --output-directory coverage_html
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
      COMMENT "Generating coverage report"
    )
  else()
    # Fallback to gcov directly
    add_custom_target(iota-coverage
      COMMAND ${CMAKE_COMMAND} -E remove_directory coverage
      COMMAND ${CMAKE_COMMAND} -E make_directory coverage
      COMMAND tests
      COMMAND ${CMAKE_COMMAND} -E chdir coverage ${GCOV_PATH} -abcfu ${CMAKE_SOURCE_DIR}/src/*.cpp
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
      COMMENT "Running gcov"
    )
  endif()
endif()