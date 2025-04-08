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

set(IOTA_CPP_LIB_TEST_DIR ${CMAKE_SOURCE_DIR}/tests)
set(IOTA_LIB_DIR ${CMAKE_SOURCE_DIR}/libraries/iota-cpp)
set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin)

add_executable(tests main.cpp
  noun_tests.cpp
  atom_tests.cpp
  char_tests.cpp
  enclose_tests.cpp
  not_tests.cpp
  enumerate_tests.cpp
  first_tests.cpp
  floor_tests.cpp
  format_tests.cpp
  gradeDown_tests.cpp
  gradeUp_tests.cpp
)
target_link_libraries(tests PRIVATE iota-cpp-lib Catch2::Catch2WithMain)

# Generate ctags for vim
set(TAGS_FILE ${IOTA_CPP_LIB_TEST_DIR}/tags)
add_custom_target(
  GenerateTestTags
  COMMAND ctags -R -f ${TAGS_FILE} ${IOTA_CPP_LIB_TEST_DIR} ${IOTA_LIB_DIR}
  WORKING_DIRECTORY ${IOTA_CPP_LIB_TEST_DIR}
  COMMENT "Generating ctags"
)
add_dependencies(tests GenerateTestTags)

include(CTest)
add_test(NAME "small words" COMMAND tests)
