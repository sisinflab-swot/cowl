# Output setup

file(GLOB COWL_TEST_DATA CONFIGURE_DEPENDS "${COWL_DATA_DIR}/*.owl")
file(COPY ${COWL_TEST_DATA} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

# Test target

file(GLOB COWL_TEST_UTIL_SOURCES CONFIGURE_DEPENDS "${COWL_TEST_DIR}/cowl_*.c")
set(COWL_TEST_MAIN_SOURCE "${COWL_TEST_DIR}/test.c")

add_executable(cowl-test EXCLUDE_FROM_ALL ${COWL_TEST_UTIL_SOURCES} ${COWL_TEST_MAIN_SOURCE})
target_include_directories(cowl-test PRIVATE ${COWL_PRIVATE_HEADERS_DIRS})
target_link_libraries(cowl-test cowl-static)

# Benchmark target

set(COWL_BENCH_MAIN_SOURCE "${COWL_TEST_DIR}/bench.c")
add_executable(cowl-bench EXCLUDE_FROM_ALL ${COWL_BENCH_MAIN_SOURCE})
target_link_libraries(cowl-bench cowl-static)
