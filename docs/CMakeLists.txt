# Directories

set(DOCS_IMAGES_DIRECTORY "${COWL_DOCS_DIR}/img")
set(DOCS_OUTPUT_DIRECTORY "${COWL_OUTPUT_DIR}/docs")

set(SPHINX_INPUT_DIRECTORY "${COWL_DOCS_DIR}")
set(SPHINX_OUTPUT_DIRECTORY "${DOCS_OUTPUT_DIRECTORY}/sphinx")
set(SPHINX_HTML_OUTPUT_DIRECTORY "${SPHINX_OUTPUT_DIRECTORY}/html")

# Files

set(SPHINX_CONF_IN "${SPHINX_INPUT_DIRECTORY}/conf.py")
set(SPHINX_CONF_OUT "${SPHINX_OUTPUT_DIRECTORY}/conf.py")
set(COWL_ICON "${DOCS_IMAGES_DIRECTORY}/cowl_logo.png")

# Doxygen configuration

set(DOXYGEN_FULL_PATH_NAMES NO)
set(DOXYGEN_JAVADOC_AUTOBRIEF YES)
set(DOXYGEN_OPTIMIZE_OUTPUT_FOR_C YES)
set(DOXYGEN_TOC_INCLUDE_HEADINGS 0)
set(DOXYGEN_DISTRIBUTE_GROUP_DOC YES)
set(DOXYGEN_TYPEDEF_HIDES_STRUCT YES)
set(DOXYGEN_FORCE_LOCAL_INCLUDES YES)
set(DOXYGEN_MAX_INITIALIZER_LINES 0)
set(DOXYGEN_WARN_NO_PARAMDOC YES)
set(DOXYGEN_EXCLUDE_SYMBOLS "__*")
set(DOXYGEN_EXAMPLE_PATTERNS "*.c")
set(DOXYGEN_COLS_IN_ALPHA_INDEX 2)
set(DOXYGEN_IGNORE_PREFIX "COWL_" "cowl_" "Cowl" "COWL")
set(DOXYGEN_HTML_DYNAMIC_SECTIONS YES)
set(DOXYGEN_TOC_EXPAND YES)
set(DOXYGEN_GENERATE_TREEVIEW YES)
set(DOXYGEN_GENERATE_XML YES)
set(DOXYGEN_MACRO_EXPANSION YES)
set(DOXYGEN_INCLUDE_PATH "${COWL_VECTOR_DIR}" "${COWL_UHASH_DIR}")
set(DOXYGEN_OUTPUT_DIRECTORY "${DOCS_OUTPUT_DIRECTORY}/doxygen")
set(DOXYGEN_XML_OUTPUT_DIRECTORY "${DOXYGEN_OUTPUT_DIRECTORY}/xml")

# Output setup

file(REMOVE_RECURSE ${DOCS_OUTPUT_DIRECTORY})
file(MAKE_DIRECTORY ${SPHINX_OUTPUT_DIRECTORY})
file(MAKE_DIRECTORY ${DOXYGEN_OUTPUT_DIRECTORY})

# Documentation targets

find_package(Doxygen)

if(DOXYGEN_FOUND)
    doxygen_add_docs(cowl-doxygen ${COWL_PUBLIC_HEADERS}
                     COMMENT "Generate documentation via Doxygen"
                     WORKING_DIRECTORY "${DOXYGEN_OUTPUT_DIRECTORY}")

    find_package(Sphinx)

    if(SPHINX_FOUND)
        add_custom_target(cowl-sphinx
                          DEPENDS cowl-doxygen
                          COMMAND "${CMAKE_COMMAND}" -E remove_directory
                                  "${SPHINX_HTML_OUTPUT_DIRECTORY}"
                          COMMAND "${SPHINX_EXECUTABLE}" -b html -c "${SPHINX_OUTPUT_DIRECTORY}"
                                  "${SPHINX_INPUT_DIRECTORY}" "${SPHINX_HTML_OUTPUT_DIRECTORY}"
                          WORKING_DIRECTORY "${SPHINX_OUTPUT_DIRECTORY}"
                          COMMENT "Generate documentation via Sphinx"
                          VERBATIM)

        configure_file("${SPHINX_CONF_IN}" "${SPHINX_CONF_OUT}" @ONLY)
        add_custom_target(cowl-docs DEPENDS cowl-sphinx)
    else()
        add_custom_target(cowl-docs DEPENDS cowl-doxygen)
    endif()
endif()
