# Output setup

file(GLOB COWL_TEST_DATA CONFIGURE_DEPENDS "${COWL_DATA_DIR}/*.owl")
file(COPY ${COWL_TEST_DATA} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

# Test target

file(GLOB COWL_TEST_SOURCES CONFIGURE_DEPENDS tests/*.c)
add_executable(cowl-test EXCLUDE_FROM_ALL ${COWL_TEST_SOURCES} test.c)
target_include_directories(cowl-test PRIVATE ${COWL_PRIVATE_HEADERS_DIRS} tests)
target_link_libraries(cowl-test PRIVATE cowl-static)

# Benchmark target

add_executable(cowl-bench EXCLUDE_FROM_ALL bench.c)
target_link_libraries(cowl-bench PRIVATE cowl-static)
