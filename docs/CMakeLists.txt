# Directories

set(COWL_DOCS_IMG_DIR "${COWL_DOCS_DIR}/img")
set(COWL_DOCS_OUT_DIR "${COWL_OUTPUT_DIR}/docs")

set(COWL_DOXYGEN_SRC_DIR "${COWL_DOCS_DIR}")
set(COWL_DOXYGEN_OUT_DIR "${COWL_DOCS_OUT_DIR}/doxygen")
set(COWL_DOXYGEN_XML_OUT_DIR "${COWL_DOXYGEN_OUT_DIR}/xml")

set(COWL_SPHINX_SRC_DIR "${COWL_DOCS_DIR}")
set(COWL_SPHINX_OUT_DIR "${COWL_DOCS_OUT_DIR}/sphinx")
set(COWL_SPHINX_HTML_OUT_DIR "${COWL_SPHINX_OUT_DIR}/html")

# Output setup

file(REMOVE_RECURSE ${COWL_DOCS_OUT_DIR})
file(MAKE_DIRECTORY ${COWL_SPHINX_OUT_DIR})

# Files

set(COWL_DOXYFILE_IN "${COWL_DOXYGEN_SRC_DIR}/Doxyfile")
set(COWL_DOXYFILE_OUT "${COWL_DOXYGEN_OUT_DIR}/Doxyfile")
set(COWL_SPHINX_CONF_IN "${COWL_SPHINX_SRC_DIR}/conf.py")
set(COWL_SPHINX_CONF_OUT "${COWL_SPHINX_OUT_DIR}/conf.py")
set(COWL_ICON "${COWL_DOCS_IMG_DIR}/cowl_logo.png")

# Documentation targets

find_package(Doxygen)

if (DOXYGEN_FOUND)
    add_custom_target(cowl-doxygen
                      COMMAND "${DOXYGEN_EXECUTABLE}" "${COWL_DOXYFILE_OUT}"
                      WORKING_DIRECTORY "${COWL_DOXYGEN_OUT_DIR}"
                      COMMENT "Generate documentation via Doxygen"
                      VERBATIM)

    find_package(Sphinx)

    if (SPHINX_FOUND)
        add_custom_target(cowl-sphinx
                          DEPENDS cowl-doxygen
                          COMMAND "${CMAKE_COMMAND}" -E remove_directory
                                  "${COWL_SPHINX_HTML_OUT_DIR}"
                          COMMAND "${SPHINX_EXECUTABLE}" -b html -c "${COWL_SPHINX_OUT_DIR}"
                                  "${COWL_SPHINX_SRC_DIR}" "${COWL_SPHINX_HTML_OUT_DIR}"
                          WORKING_DIRECTORY "${COWL_SPHINX_OUT_DIR}"
                          COMMENT "Generate documentation via Sphinx"
                          VERBATIM)

        configure_file("${COWL_SPHINX_CONF_IN}" "${COWL_SPHINX_CONF_OUT}" @ONLY)
        add_custom_target(cowl-docs DEPENDS cowl-sphinx)
    else()
        add_custom_target(cowl-docs DEPENDS cowl-doxygen)
    endif()

    configure_file("${COWL_DOXYFILE_IN}" "${COWL_DOXYFILE_OUT}" @ONLY)
endif()
