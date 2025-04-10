# Data

file(GLOB COWL_EXAMPLES_DATA CONFIGURE_DEPENDS "${COWL_DATA_DIR}/*.owl")
file(COPY ${COWL_EXAMPLES_DATA} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

# Sources

set(COWL_EXAMPLES_SRC_DIR "${COWL_EXAMPLES_DIR}/src")

# Example targets

add_custom_target(cowl-examples COMMENT "Build the examples")
file(GLOB COWL_EXAMPLES CONFIGURE_DEPENDS "${COWL_EXAMPLES_SRC_DIR}/*.c")

foreach(COWL_EXAMPLE ${COWL_EXAMPLES})
    get_filename_component(COWL_EXAMPLE_TARGET "${COWL_EXAMPLE}" NAME_WE)
    string(REPLACE "_" "-" COWL_EXAMPLE_TARGET "${COWL_EXAMPLE_TARGET}")
    string(PREPEND COWL_EXAMPLE_TARGET "cowl-")
    string(APPEND COWL_EXAMPLE_TARGET "-example")
    add_executable("${COWL_EXAMPLE_TARGET}")
    target_sources("${COWL_EXAMPLE_TARGET}" PRIVATE "${COWL_EXAMPLE}")
    target_compile_features("${COWL_EXAMPLE_TARGET}" PRIVATE ${COWL_COMPILE_FEATURES})
    target_compile_options("${COWL_EXAMPLE_TARGET}" PRIVATE ${COWL_WARNING_OPTIONS})
    target_link_libraries("${COWL_EXAMPLE_TARGET}" PRIVATE cowl)
    if(COWL_CLANG_TIDY)
        clang_tidy_check("${COWL_EXAMPLE_TARGET}")
    endif()
    add_dependencies(cowl-examples "${COWL_EXAMPLE_TARGET}")
    if(COWL_TESTS)
        add_test(NAME "Example: ${COWL_EXAMPLE_TARGET}" COMMAND "${COWL_EXAMPLE_TARGET}")
    endif()
endforeach()
