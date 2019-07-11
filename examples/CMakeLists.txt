# Output setup

set(COWL_EXAMPLES_DATA_DIR "${COWL_EXAMPLES_DIR}/data")

file(GLOB COWL_EXAMPLES_DATA "${COWL_EXAMPLES_DATA_DIR}/*.owl")
file(COPY ${COWL_EXAMPLES_DATA} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

# Example targets

file(GLOB COWL_EXAMPLES "${COWL_EXAMPLES_DIR}/*.c")

foreach(COWL_EXAMPLE ${COWL_EXAMPLES})
    get_filename_component(COWL_EXAMPLE_TARGET "${COWL_EXAMPLE}" NAME_WE)
    string(REPLACE "_" "-" COWL_EXAMPLE_TARGET "${COWL_EXAMPLE_TARGET}")
    string(PREPEND COWL_EXAMPLE_TARGET "cowl-" )
    add_executable("${COWL_EXAMPLE_TARGET}" "${COWL_EXAMPLE}")
    target_link_libraries("${COWL_EXAMPLE_TARGET}" cowl-static)
endforeach()
