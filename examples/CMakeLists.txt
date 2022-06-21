# Output setup

file(GLOB COWL_EXAMPLES_DATA CONFIGURE_DEPENDS "${COWL_DATA_DIR}/*.owl")
file(COPY ${COWL_EXAMPLES_DATA} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

# Example targets

add_custom_target(cowl-examples COMMENT "Build the examples")
file(GLOB COWL_EXAMPLES CONFIGURE_DEPENDS "${COWL_EXAMPLES_DIR}/*.c")

foreach(COWL_EXAMPLE ${COWL_EXAMPLES})
    get_filename_component(COWL_EXAMPLE_TARGET "${COWL_EXAMPLE}" NAME_WE)
    string(REPLACE "_" "-" COWL_EXAMPLE_TARGET "${COWL_EXAMPLE_TARGET}")
    string(PREPEND COWL_EXAMPLE_TARGET "cowl-" )
    string(APPEND COWL_EXAMPLE_TARGET "-example")
    add_executable("${COWL_EXAMPLE_TARGET}" EXCLUDE_FROM_ALL "${COWL_EXAMPLE}")
    target_link_libraries("${COWL_EXAMPLE_TARGET}" PRIVATE cowl)
    add_dependencies(cowl-examples "${COWL_EXAMPLE_TARGET}")
endforeach()
