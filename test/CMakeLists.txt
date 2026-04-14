# Data

file(GLOB test_data CONFIGURE_DEPENDS "${COWL_DATA_DIR}/*.owl")
file(COPY ${test_data} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

# Sources

set(COWL_TEST_SRC_DIR "${COWL_TEST_DIR}/src")
file(GLOB COWL_TEST_HEADERS CONFIGURE_DEPENDS "${COWL_TEST_SRC_DIR}/*.h")
file(GLOB COWL_TEST_SOURCES CONFIGURE_DEPENDS "${COWL_TEST_SRC_DIR}/*.c")

# Test target

add_executable(cowl-test)
target_sources(
    cowl-test
    PRIVATE ${COWL_TEST_SOURCES}
    PRIVATE FILE_SET HEADERS
            BASE_DIRS "${COWL_TEST_SRC_DIR}"
            FILES ${COWL_TEST_HEADERS}
)
set_target_properties(cowl-test PROPERTIES INTERPROCEDURAL_OPTIMIZATION ${COWL_LTO_ENABLED})
target_compile_features(cowl-test PRIVATE ${COWL_COMPILE_FEATURES})
target_compile_options(cowl-test PRIVATE ${COWL_WARNING_OPTIONS})
target_link_libraries(cowl-test PRIVATE cowl)

if(COWL_CLANG_TIDY)
    clang_tidy_check(cowl-test)
endif()

add_test(NAME "Test" COMMAND cowl-test)

# C++ test target

if(COWL_CPP_TESTS)
    # Copy and rename .c source files to .cpp
    file(COPY ${COWL_TEST_SOURCES} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
    file(GLOB COWL_CPP_TEST_SOURCES "${CMAKE_CURRENT_BINARY_DIR}/*.c")

    foreach(src ${COWL_CPP_TEST_SOURCES})
        file(RENAME "${src}" "${src}pp")
    endforeach()

    file(GLOB COWL_CPP_TEST_SOURCES "${CMAKE_CURRENT_BINARY_DIR}/*.cpp")
    set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${COWL_TEST_SOURCES})

    # Add target
    enable_language(CXX)
    add_executable(cowl-cpp-test)
    target_sources(
        cowl-cpp-test
        PRIVATE ${COWL_CPP_TEST_SOURCES}
        PRIVATE FILE_SET HEADERS
                BASE_DIRS "${COWL_TEST_SRC_DIR}"
                FILES ${COWL_TEST_HEADERS}
    )
    target_link_libraries(cowl-cpp-test PRIVATE cowl)
    set_target_properties(cowl-cpp-test PROPERTIES EXPORT_COMPILE_COMMANDS OFF)

    add_test(NAME "Test (C++)" COMMAND cowl-cpp-test)
endif()
