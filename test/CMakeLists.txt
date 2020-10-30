# Output setup

file(GLOB COWL_TEST_DATA CONFIGURE_DEPENDS "${COWL_DATA_DIR}/*.owl")
file(COPY ${COWL_TEST_DATA} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

# Test target

file(GLOB COWL_TEST_UTIL_SOURCES CONFIGURE_DEPENDS "${COWL_TEST_DIR}/cowl_*.c")
add_executable(cowl-test EXCLUDE_FROM_ALL ${COWL_TEST_UTIL_SOURCES} "${COWL_TEST_DIR}/test.c")
target_include_directories(cowl-test PRIVATE ${COWL_PRIVATE_HEADERS_DIRS})
target_link_libraries(cowl-test PRIVATE cowl-static)

if(COWL_DEBUG_LEAKS)
    target_compile_definitions(cowl-test PRIVATE COWL_DEBUG_LEAKS=1)
endif()

# Benchmark target

add_executable(cowl-bench EXCLUDE_FROM_ALL "${COWL_TEST_DIR}/bench.c")
target_link_libraries(cowl-bench PRIVATE cowl-static)
