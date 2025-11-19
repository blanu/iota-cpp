cmake_minimum_required(VERSION 3.31)
project(iota-repl)
set(CMAKE_CXX_STANDARD 17)

set(IOTA_REPL_DIR ${CMAKE_SOURCE_DIR}/iota-repl)
set(IOTA_REPL_SOURCE_DIR ${IOTA_REPL_DIR}/src)
set(IOTA_LIB_DIR ${CMAKE_SOURCE_DIR}/libraries/iota-cpp)
set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin)

add_executable(iota-repl
  ${IOTA_REPL_SOURCE_DIR}/IotaRepl.cpp
  ${IOTA_REPL_SOURCE_DIR}/main.cpp
)
target_link_libraries(iota-repl iota-cpp-lib bignumber-cpp-lib)

# Link coverage runtime since ion-cpp was built with coverage
target_link_options(iota-repl PRIVATE --coverage)