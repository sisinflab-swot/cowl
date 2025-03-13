# Files and directories

set(DOCS_IMAGES_DIRECTORY "${COWL_DOCS_DIR}/img")
set(SPHINX_INPUT_DIRECTORY "${COWL_DOCS_DIR}")
set(COWL_ICON "${DOCS_IMAGES_DIRECTORY}/cowl_logo.png")
set(ULIB_PUBLIC_HEADERS_DIR "${COWL_ULIB_DIR}/include")
file(GLOB ULIB_PUBLIC_HEADERS CONFIGURE_DEPENDS "${ULIB_PUBLIC_HEADERS_DIR}/*.h")

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
set(DOXYGEN_INCLUDE_PATH ${COWL_PUBLIC_HEADERS_DIRS} ${ULIB_PUBLIC_HEADERS_DIR})
set(DOXYGEN_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/doxygen")
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

find_program(DOXYGEN_PYTHON
             NAMES python3 python
             DOC "Path to the Python interpreter used to run Doxygen input filters")

if(DOXYGEN_PYTHON)
    set(DOXYGEN_INPUT_FILTER "${DOXYGEN_PYTHON} ${COWL_ULIB_UTILS_DIR}/doxygen/alias.py")
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
                        COMMENT "Generating documentation via Sphinx")
        add_dependencies("${DOCS_TARGET_NAME}" "${DOXYGEN_TARGET_NAME}" ulib-docs)
    else()
        set(DOXYGEN_TARGET_NAME "${DOCS_TARGET_NAME}")
    endif()

    doxygen_add_docs("${DOXYGEN_TARGET_NAME}" ${COWL_PUBLIC_HEADERS} ${ULIB_PUBLIC_HEADERS}
                     COMMENT "Generating documentation via Doxygen")
endif()
