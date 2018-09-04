

add_executable( test_fingeracpp
  test_format.cpp
)

target_link_libraries( test_fingeracpp fingera gtest_main )
add_test(NAME test_fingeracpp COMMAND test_fingeracpp)

if (${BUILD_VALGRIND} STREQUAL "ON")
  find_program(VALGRIND "valgrind")
  if(VALGRIND)
    add_custom_target(valgrind
        COMMAND "${VALGRIND}" --leak-check=full --track-fds=yes $<TARGET_FILE:test_fingeracpp>)
  endif()
endif()

