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

file(MAKE_DIRECTORY ${COWL_SPHINX_OUT_DIR})

# Files

set(COWL_DOXYFILE_IN "${COWL_DOXYGEN_SRC_DIR}/Doxyfile")
set(COWL_DOXYFILE_OUT "${COWL_DOXYGEN_OUT_DIR}/Doxyfile")
set(COWL_SPHINX_CONF_IN "${COWL_SPHINX_SRC_DIR}/conf.py")
set(COWL_SPHINX_CONF_OUT "${COWL_SPHINX_OUT_DIR}/conf.py")
set(COWL_ICON "${COWL_DOCS_IMG_DIR}/cowl_logo.png")
set(COWL_README "${COWL_PROJECT_DIR}/README.md")

# Documentation target

option(BUILD_DOCS "Generate documentation" ON)

if (BUILD_DOCS)
    find_package(Doxygen)

    if (DOXYGEN_FOUND)
        configure_file("${COWL_DOXYFILE_IN}" "${COWL_DOXYFILE_OUT}" @ONLY)

        add_custom_target(cowl-doxygen-docs ALL
                          COMMAND "${DOXYGEN_EXECUTABLE}" "${COWL_DOXYFILE_OUT}"
                          WORKING_DIRECTORY "${COWL_DOXYGEN_OUT_DIR}"
                          COMMENT "Generate documentation via Doxygen"
                          VERBATIM)

        find_package(Sphinx)

        if (SPHINX_FOUND)
            configure_file("${COWL_SPHINX_CONF_IN}" "${COWL_SPHINX_CONF_OUT}" @ONLY)

            add_custom_target(cowl-sphinx-docs ALL
                              DEPENDS cowl-doxygen-docs
                              COMMAND "${SPHINX_EXECUTABLE}"
                              -b html -c ${COWL_SPHINX_OUT_DIR} -E
                              ${COWL_SPHINX_SRC_DIR} ${COWL_SPHINX_HTML_OUT_DIR}
                              WORKING_DIRECTORY ${COWL_SPHINX_OUT_DIR}
                              COMMENT "Generate documentation via Sphinx"
                              VERBATIM)
        endif ()
    else ()
        message(WARNING "Doxygen needs to be installed in order to generate the documentation.")
    endif ()
else ()
    message(STATUS "Skipping docs generation...")
endif ()
