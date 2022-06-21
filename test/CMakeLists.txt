# Output setup

file(GLOB COWL_TEST_DATA CONFIGURE_DEPENDS "${COWL_DATA_DIR}/*.owl")
file(COPY ${COWL_TEST_DATA} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

set(COWL_CPP_TEST_SOURCE "${CMAKE_CURRENT_BINARY_DIR}/test_cpp.cpp")
file(COPY test.c DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
file(RENAME "${CMAKE_CURRENT_BINARY_DIR}/test.c" "${COWL_CPP_TEST_SOURCE}")

# Benchmark target

add_executable(cowl-bench EXCLUDE_FROM_ALL bench.c)
target_link_libraries(cowl-bench PRIVATE cowl)

# Test target

file(GLOB COWL_TEST_SOURCES CONFIGURE_DEPENDS tests/*.c)
add_executable(cowl-test EXCLUDE_FROM_ALL ${COWL_TEST_SOURCES} test.c)
target_include_directories(cowl-test PRIVATE ${COWL_PRIVATE_HEADERS_DIRS} tests)
target_link_libraries(cowl-test PRIVATE cowl)

# C++ test target

enable_language(CXX)
add_executable(cowl-cpp-test EXCLUDE_FROM_ALL ${COWL_TEST_SOURCES} ${COWL_CPP_TEST_SOURCE})
target_include_directories(cowl-cpp-test PRIVATE ${COWL_PRIVATE_HEADERS_DIRS} tests)
target_link_libraries(cowl-cpp-test PRIVATE cowl)
