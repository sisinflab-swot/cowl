# Data

file(GLOB examples_data CONFIGURE_DEPENDS "${COWL_DATA_DIR}/*.owl")
file(COPY ${examples_data} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

# Sources

set(COWL_EXAMPLES_SRC_DIR "${COWL_EXAMPLES_DIR}/src")

# Example targets

add_custom_target(cowl-examples COMMENT "Build the examples")
file(GLOB examples CONFIGURE_DEPENDS "${COWL_EXAMPLES_SRC_DIR}/*.c")

foreach(example ${examples})
    get_filename_component(example_target "${example}" NAME_WE)
    string(REPLACE "_" "-" example_target "${example_target}")
    string(PREPEND example_target "cowl-")
    string(APPEND example_target "-example")
    add_executable("${example_target}")
    target_sources("${example_target}" PRIVATE "${example}")
    target_compile_features("${example_target}" PRIVATE ${COWL_COMPILE_FEATURES})
    target_compile_options("${example_target}" PRIVATE ${COWL_WARNING_OPTIONS})
    target_link_libraries("${example_target}" PRIVATE cowl)
    if(COWL_CLANG_TIDY)
        clang_tidy_check("${example_target}")
    endif()
    add_dependencies(cowl-examples "${example_target}")
    if(COWL_TESTS)
        add_test(NAME "Example: ${example_target}" COMMAND "${example_target}")
    endif()
endforeach()
