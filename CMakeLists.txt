cmake_minimum_required(VERSION 3.5)

set( CMAKE_C_STANDARD 99 )
set( CMAKE_CXX_STANDARD 11 )

option(BUILD_TESTING "Enable test (depends on googletest)." ON)
option(BUILD_VALGRIND "Enable valgrind (depends on BUILD_TESTING)." OFF)
option(BUILD_BENCHMARKS "Benchmarks" OFF)

add_library(fingera
  src/format.cpp
)

add_subdirectory(external)

target_link_libraries(fingera fingera_libc)
target_include_directories(fingera
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if (${BUILD_TESTING} STREQUAL "ON")
  include(CTest)
  add_subdirectory(tests)
endif()

if (${BUILD_BENCHMARKS} STREQUAL "ON")
  add_subdirectory(benchmarks)
endif()