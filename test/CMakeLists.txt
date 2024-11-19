# Configuration

option(COWL_CPP_TESTS "Enable C++ tests" OFF)

# Output setup

file(GLOB COWL_TEST_DATA CONFIGURE_DEPENDS "${COWL_DATA_DIR}/*.owl")
file(COPY ${COWL_TEST_DATA} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

# Sources

set(COWL_TEST_HEADERS_DIR "${COWL_TEST_DIR}/tests")
file(GLOB COWL_TEST_HEADERS CONFIGURE_DEPENDS "${COWL_TEST_HEADERS_DIR}/*.h")

file(GLOB COWL_TEST_SOURCES tests/*.c)
list(APPEND COWL_TEST_SOURCES test.c)

# Benchmark target

add_executable(cowl-bench EXCLUDE_FROM_ALL)
target_sources(cowl-bench PRIVATE "${COWL_TEST_DIR}/bench.c")
target_link_libraries(cowl-bench PRIVATE cowl)

if(COWL_LTO_ENABLED)
    set_target_properties(cowl-bench PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

if(COWL_CLANG_TIDY)
    clang_tidy_check(cowl-bench)
endif()

# Test target

add_executable(cowl-test EXCLUDE_FROM_ALL)
target_sources(cowl-test
               PRIVATE ${COWL_TEST_SOURCES}
               PRIVATE FILE_SET HEADERS
                       BASE_DIRS "${COWL_TEST_HEADERS_DIR}"
                       FILES ${COWL_TEST_HEADERS})
target_include_directories(cowl-test PRIVATE ${COWL_PRIVATE_HEADERS_DIRS})
target_link_libraries(cowl-test PRIVATE cowl)

if(COWL_LTO_ENABLED)
    set_target_properties(cowl-test PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

if(COWL_CLANG_TIDY)
    clang_tidy_check(cowl-test)
endif()

# C++ test target

if(COWL_CPP_TESTS)
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

    # Add target
    enable_language(CXX)
    add_executable(cowl-cpp-test EXCLUDE_FROM_ALL)
    target_sources(cowl-cpp-test
                   PRIVATE ${COWL_CPP_TEST_SOURCES}
                   PRIVATE FILE_SET HEADERS
                           BASE_DIRS "${COWL_TEST_HEADERS_DIR}"
                           FILES ${COWL_TEST_HEADERS})
    target_include_directories(cowl-cpp-test PRIVATE ${COWL_PRIVATE_HEADERS_DIRS})
    target_link_libraries(cowl-cpp-test PRIVATE cowl)
    set_target_properties(cowl-cpp-test PROPERTIES EXPORT_COMPILE_COMMANDS OFF)
endif()
