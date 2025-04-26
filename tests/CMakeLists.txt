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
