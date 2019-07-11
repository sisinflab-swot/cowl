# Output setup

set(COWL_TEST_DATA_DIR "${COWL_TEST_DIR}/data")

file(GLOB COWL_TEST_DATA "${COWL_TEST_DATA_DIR}/*.owl")
file(COPY ${COWL_TEST_DATA} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

# Test target

add_executable(cowl-test "${COWL_TEST_DIR}/test.c")
target_link_libraries(cowl-test cowl-static)
