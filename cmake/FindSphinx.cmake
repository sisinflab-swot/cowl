find_program(SPHINX_EXECUTABLE
             NAMES sphinx-build
             DOC "Path to sphinx-build executable")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Sphinx "Failed to find sphinx-build" SPHINX_EXECUTABLE)

function(sphinx_add_docs SPHINX_TARGET SPHINX_INPUT_DIRECTORY)
    list(LENGTH ARGN INDEX)
    math(EXPR INDEX "${ARGC} - ${INDEX}")
    set(ONE_VALUE_ARGS COMMENT)
    set(MULTI_VALUE_ARGS ARGS)
    cmake_parse_arguments(PARSE_ARGV ${INDEX} SPHINX "" "${ONE_VALUE_ARGS}" "${MULTI_VALUE_ARGS}")

    set(SPHINX_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/sphinx")
    set(SPHINX_HTML_OUTPUT_DIRECTORY "${SPHINX_OUTPUT_DIRECTORY}/html")
    set(SPHINX_CONF_IN "${SPHINX_INPUT_DIRECTORY}/conf.py")
    set(SPHINX_CONF_OUT "${SPHINX_OUTPUT_DIRECTORY}/conf.py")

    add_custom_target("${SPHINX_TARGET}"
                      COMMAND "${CMAKE_COMMAND}" -E remove_directory
                      "${SPHINX_HTML_OUTPUT_DIRECTORY}"
                      COMMAND "${SPHINX_EXECUTABLE}" ${SPHINX_ARGS}
                      -b html -c "${SPHINX_OUTPUT_DIRECTORY}"
                      "${SPHINX_INPUT_DIRECTORY}" "${SPHINX_HTML_OUTPUT_DIRECTORY}"
                      WORKING_DIRECTORY "${SPHINX_OUTPUT_DIRECTORY}"
                      COMMENT "${SPHINX_COMMENT}"
                      VERBATIM)

    configure_file("${SPHINX_CONF_IN}" "${SPHINX_CONF_OUT}" @ONLY)
endfunction()
