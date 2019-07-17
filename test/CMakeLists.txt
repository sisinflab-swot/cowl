# Output setup

file(GLOB COWL_TEST_DATA "${COWL_DATA_DIR}/*.owl")
file(COPY ${COWL_TEST_DATA} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

# Test target

file(GLOB COWL_TEST_SOURCES "${COWL_TEST_DIR}/*.c")
add_executable(cowl-test ${COWL_TEST_SOURCES})
target_link_libraries(cowl-test cowl-static)
