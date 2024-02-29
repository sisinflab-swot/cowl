# Files and directories

set(DOCS_IMAGES_DIRECTORY "${COWL_DOCS_DIR}/img")
set(DOCS_OUTPUT_DIRECTORY "${COWL_OUTPUT_DIR}/docs")
set(SPHINX_INPUT_DIRECTORY "${COWL_DOCS_DIR}")
set(DOXYGEN_UTILS_DIRECTORY "${COWL_DOCS_DIR}/doxygen")
set(COWL_ICON "${DOCS_IMAGES_DIRECTORY}/cowl_logo.png")
list(APPEND CMAKE_MODULE_PATH "${COWL_DOCS_DIR}/cmake")
get_target_property(ULIB_DIRS ulib INTERFACE_INCLUDE_DIRECTORIES)

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
set(DOXYGEN_WARN_AS_ERROR YES)
set(DOXYGEN_EXCLUDE_SYMBOLS "p_*" "P_*")
set(DOXYGEN_EXAMPLE_PATTERNS "*.c")
set(DOXYGEN_COLS_IN_ALPHA_INDEX 2)
set(DOXYGEN_IGNORE_PREFIX "COWL_" "cowl_" "Cowl" "COWL")
set(DOXYGEN_HTML_DYNAMIC_SECTIONS YES)
set(DOXYGEN_TOC_EXPAND YES)
set(DOXYGEN_GENERATE_TREEVIEW YES)
set(DOXYGEN_GENERATE_XML YES)
set(DOXYGEN_MACRO_EXPANSION YES)
set(DOXYGEN_PREDEFINED ${COWL_PUBLIC_DEFINES}
    "COWL_RETAINED=/** @note You must release the returned object via <tt>#cowl_release()</tt>. */"
    "COWL_DEPRECATED(msg)=/** @@deprecated msg */"
    "COWL_INLINE=")
set(DOXYGEN_INCLUDE_PATH ${COWL_PUBLIC_HEADERS_DIRS} ${ULIB_DIRS})
set(DOXYGEN_OUTPUT_DIRECTORY "${DOCS_OUTPUT_DIRECTORY}/doxygen")
set(DOXYGEN_XML_OUTPUT_DIRECTORY "${DOXYGEN_OUTPUT_DIRECTORY}/xml")
set(DOXYGEN_ALIASES
    [[destructor{1}="@note The returned object must be destroyed by calling <tt>#\1()</tt>."]]
    [[superstruct{1}="**Pseudo-extends:** <tt>#\1</tt>"]]
    [[superstruct{2}="**Pseudo-extends:** <tt>#\1</tt>, <tt>#\2</tt>"]]
    [[superstruct{3}="**Pseudo-extends:** <tt>#\1</tt>, <tt>#\2</tt>, <tt>#\3</tt>"]]
    [[func{1}="<tt>\1</tt>"]]
    [[type{1}="<tt>\1</tt>"]]
    [[val{1}="<tt>\1</tt>"]]
    [[alias=@noop]]
)
set(DOXYGEN_VERBATIM_VARS DOXYGEN_ALIASES)

find_program(PYTHON
             NAMES python3 python
             DOC "Path to the Python interpreter")

if(NOT PYTHON STREQUAL "PYTHON-NOTFOUND")
    set(DOXYGEN_INPUT_FILTER "${PYTHON} ${DOXYGEN_UTILS_DIRECTORY}/alias.py")
endif()

# Documentation targets

find_package(Doxygen)

if(DOXYGEN_FOUND)
    find_package(Sphinx)
    set(DOCS_TARGET_NAME cowl-docs)

    if(SPHINX_FOUND)
        get_target_property(TEMP_DIR ulib-docs BINARY_DIR)
        set(ULIB_DOCS_INVENTORY_FILE "${TEMP_DIR}/sphinx/html/objects.inv")

        set(DOXYGEN_TARGET_NAME cowl-doxygen)
        sphinx_add_docs("${DOCS_TARGET_NAME}" "${SPHINX_INPUT_DIRECTORY}" ARGS -W
                        COMMENT "Generate documentation via Sphinx")
        add_dependencies("${DOCS_TARGET_NAME}" "${DOXYGEN_TARGET_NAME}" ulib-docs)
    else()
        set(DOXYGEN_TARGET_NAME "${DOCS_TARGET_NAME}")
    endif()

    doxygen_add_docs("${DOXYGEN_TARGET_NAME}" ${COWL_PUBLIC_HEADERS}
                     COMMENT "Generate documentation via Doxygen")
endif()
