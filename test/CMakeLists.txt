# Output setup

file(GLOB COWL_TEST_DATA CONFIGURE_DEPENDS "${COWL_DATA_DIR}/*.owl")
file(COPY ${COWL_TEST_DATA} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

# Copy and rename .c source files to .cpp

file(GLOB COWL_TEST_SOURCES tests/*.c)
list(APPEND COWL_TEST_SOURCES test.c)
file(COPY ${COWL_TEST_SOURCES} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

file(GLOB COWL_CPP_TEST_SOURCES "${CMAKE_CURRENT_BINARY_DIR}/*.c")

foreach(SRC ${COWL_CPP_TEST_SOURCES})
    file(RENAME "${SRC}" "${SRC}pp")
endforeach()

file(GLOB COWL_CPP_TEST_SOURCES "${CMAKE_CURRENT_BINARY_DIR}/*.cpp")

set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${COWL_TEST_SOURCES})
set_source_files_properties(${COWL_CPP_TEST_SOURCES}
                            DIRECTORY "${COWL_PROJECT_DIR}"
                            PROPERTIES GENERATED ON)

# Benchmark target

add_executable(cowl-bench EXCLUDE_FROM_ALL bench.c)
target_link_libraries(cowl-bench PRIVATE cowl)

# Test target

add_executable(cowl-test EXCLUDE_FROM_ALL ${COWL_TEST_SOURCES})
target_include_directories(cowl-test PRIVATE ${COWL_PRIVATE_HEADERS_DIRS} tests)
target_link_libraries(cowl-test PRIVATE cowl)

# C++ test target

enable_language(CXX)
add_executable(cowl-cpp-test EXCLUDE_FROM_ALL ${COWL_CPP_TEST_SOURCES})
target_compile_features(cowl-cpp-test PRIVATE cxx_std_20)
target_include_directories(cowl-cpp-test PRIVATE ${COWL_PRIVATE_HEADERS_DIRS} tests)
target_link_libraries(cowl-cpp-test PRIVATE cowl)
