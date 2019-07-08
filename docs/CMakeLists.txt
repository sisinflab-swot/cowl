# Directories

set(COWL_DOCS_IMG_DIR "${COWL_DOCS_DIR}/img")
set(COWL_DOCS_PAGES_DIR "${COWL_DOCS_DIR}/pages")
set(COWL_DOCS_STYLE_DIR "${COWL_DOCS_DIR}/style")
set(COWL_DOCS_OUT_DIR "${COWL_OUTPUT_DIR}/docs")

# Output setup

file(GLOB COWL_DOCS_IMAGES "${COWL_DOCS_IMG_DIR}/*.png")
file(COPY ${COWL_DOCS_IMAGES} DESTINATION "${COWL_DOCS_OUT_DIR}/html")

# Files

set(COWL_DOXYFILE_IN "${COWL_DOCS_DIR}/Doxyfile.in")
set(COWL_DOXYGEN_LAYOUT "${COWL_DOCS_STYLE_DIR}/layout.xml")
set(COWL_DOXYGEN_STYLESHEET "${COWL_DOCS_STYLE_DIR}/style.css")
set(COWL_DOXYGEN_FOOTER "${COWL_DOCS_STYLE_DIR}/footer.html")
set(COWL_ICON "${COWL_DOCS_IMG_DIR}/cowl_logo.png")
set(COWL_README "${COWL_PROJECT_DIR}/README.md")

# Documentation target

option(BUILD_DOCS "Generate documentation" ON)

if (BUILD_DOCS)
    find_package(Doxygen)

    if (DOXYGEN_FOUND)
        set(COWL_DOXYFILE_OUT "${COWL_DOCS_OUT_DIR}/Doxyfile")

        configure_file("${COWL_DOXYFILE_IN}"
                       "${COWL_DOXYFILE_OUT}" @ONLY)

        add_custom_target(cowl-docs ALL
                          COMMAND "${DOXYGEN_EXECUTABLE}" "${COWL_DOXYFILE_OUT}"
                          WORKING_DIRECTORY "${COWL_DOCS_OUT_DIR}"
                          COMMENT "Generate documentation"
                          VERBATIM)
    else (DOXYGEN_FOUND)
        message(WARNING "Doxygen needs to be installed in order to generate the documentation.")
    endif (DOXYGEN_FOUND)
else (BUILD_DOCS)
    message(STATUS "Skipping docs generation...")
endif (BUILD_DOCS)
