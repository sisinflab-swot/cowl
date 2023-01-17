#################
# Configuration #
#################

# CMake

cmake_minimum_required(VERSION 3.18)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake" "${CMAKE_MODULE_PATH}")

# Project

set(COWL_VERSION_MAJOR 0)
set(COWL_VERSION_MINOR 6)
set(COWL_VERSION_PATCH 2)
set(COWL_VERSION "${COWL_VERSION_MAJOR}.${COWL_VERSION_MINOR}.${COWL_VERSION_PATCH}")

set(COWL_VENDOR "SisInf Lab, Polytechnic University of Bari")
set(COWL_VENDOR_URL "http://swot.sisinflab.poliba.it")
set(COWL_COPYRIGHT_YEAR "2019-2023")
set(COWL_GIT_URL "https://github.com/sisinflab-swot/cowl")

project(Cowl
        VERSION "${COWL_VERSION}"
        DESCRIPTION "A lightweight C API for working with OWL ontologies."
        HOMEPAGE_URL "${COWL_VENDOR_URL}/cowl"
        LANGUAGES C)

# Options

option(COWL_EMBEDDED "Enable optimizations for embedded platforms" OFF)
option(COWL_LTO "Enable link-time optimization, if available" ON)
set(COWL_LIBRARY_TYPE "STATIC" CACHE STRING "Type of library to build.")
set(COWL_READERS "functional" CACHE STRING "List of enabled built-in readers (semicolon-separated)")
set(COWL_WRITERS "functional" CACHE STRING "List of enabled built-in writers (semicolon-separated)")

# Directories

set(COWL_PROJECT_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(COWL_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}")
set(COWL_PUBLIC_HEADERS_DIR "${COWL_PROJECT_DIR}/include")
set(COWL_LIB_DIR "${COWL_PROJECT_DIR}/lib")
set(COWL_SRC_DIR "${COWL_PROJECT_DIR}/src")
set(COWL_PRIVATE_HEADERS_DIR "${COWL_SRC_DIR}/include")
set(COWL_READER_DIR "${COWL_SRC_DIR}/reader")
set(COWL_WRITER_DIR "${COWL_SRC_DIR}/writer")

set(COWL_DATA_DIR "${COWL_PROJECT_DIR}/data")
set(COWL_DOCS_DIR "${COWL_PROJECT_DIR}/docs")
set(COWL_EXAMPLES_DIR "${COWL_PROJECT_DIR}/examples")
set(COWL_TEST_DIR "${COWL_PROJECT_DIR}/test")

set(COWL_HEADERS_OUT_DIR "${COWL_OUTPUT_DIR}/include")

# Target settings

set(COWL_COMPILE_FEATURES c_std_11)

list(APPEND COWL_PRIVATE_DEFINES
     COWL_BUILDING
     COWL_VERSION_MAJOR=${COWL_VERSION_MAJOR}
     COWL_VERSION_MINOR=${COWL_VERSION_MINOR}
     COWL_VERSION_PATCH=${COWL_VERSION_PATCH})

if(MSVC)
    set(COWL_WARNING_OPTIONS /W3 /wd4996)
else()
    set(COWL_WARNING_OPTIONS -Wall -Wextra)
endif()

if(COWL_LTO)
    include(CheckIPOSupported)
    check_ipo_supported(RESULT COWL_LTO_ENABLED)
endif()

# uLib

if(NOT TARGET ulib)
    option(ULIB_EMBEDDED "" ${COWL_EMBEDDED})
    option(ULIB_LTO "" ${COWL_LTO})
    add_subdirectory("${COWL_LIB_DIR}/ulib" EXCLUDE_FROM_ALL)
endif()

# Header dirs

set(COWL_PUBLIC_HEADERS_DIRS "${COWL_PUBLIC_HEADERS_DIR}")

set(COWL_PRIVATE_HEADERS_DIRS
    "${COWL_PRIVATE_HEADERS_DIR}"
    "${COWL_SRC_DIR}")

# Header files

file(GLOB COWL_PUBLIC_HEADERS CONFIGURE_DEPENDS "${COWL_PUBLIC_HEADERS_DIR}/*.h")
get_target_property(COWL_ULIB_HEADERS ulib PUBLIC_HEADER)
list(APPEND COWL_PUBLIC_HEADERS ${COWL_ULIB_HEADERS})

# Sources

file(GLOB COWL_SOURCES CONFIGURE_DEPENDS "${COWL_SRC_DIR}/*.c")

###############
### Targets ###
###############

# Readers

add_custom_target(cowl-readers COMMENT "Generate builtin readers.")

if(COWL_READERS)
    foreach(READER IN LISTS COWL_READERS)
        string(TOUPPER "${READER}" READER_OPT)
        set(READER_OPT "COWL_READER_${READER_OPT}")
        string(TOLOWER "${READER}" READER)

        add_subdirectory("${COWL_READER_DIR}/${READER}")
        list(APPEND COWL_READER_DEFINES "${READER_OPT}")
    endforeach()

    list(APPEND COWL_PUBLIC_DEFINES ${COWL_READER_DEFINES})

    list(GET COWL_READERS 0 COWL_DEFAULT_READER)
    if(DEFINED COWL_DEFAULT_READER)
        list(APPEND COWL_PUBLIC_DEFINES COWL_DEFAULT_READER=${COWL_DEFAULT_READER})
    endif()
endif()

# Writers

if(COWL_WRITERS)
    foreach(WRITER IN LISTS COWL_WRITERS)
        string(TOUPPER "${WRITER}" WRITER_OPT)
        set(WRITER_OPT "COWL_WRITER_${WRITER_OPT}")
        string(TOLOWER "${WRITER}" WRITER)

        add_subdirectory("${COWL_WRITER_DIR}/${WRITER}")
        list(APPEND COWL_WRITER_DEFINES "${WRITER_OPT}")
    endforeach()

    list(APPEND COWL_PUBLIC_DEFINES ${COWL_WRITER_DEFINES})

    list(GET COWL_WRITERS 0 COWL_DEFAULT_WRITER)
    if(DEFINED COWL_DEFAULT_WRITER)
        list(APPEND COWL_PUBLIC_DEFINES COWL_DEFAULT_WRITER=${COWL_DEFAULT_WRITER})
    endif()
endif()

# Copy headers

add_custom_target(cowl-headers
                  COMMAND "${CMAKE_COMMAND}" -E remove_directory "${COWL_HEADERS_OUT_DIR}"
                  COMMAND "${CMAKE_COMMAND}" -E make_directory "${COWL_HEADERS_OUT_DIR}"
                  COMMAND ${CMAKE_COMMAND} -E copy ${COWL_PUBLIC_HEADERS} "${COWL_HEADERS_OUT_DIR}"
                  COMMENT "Copy headers to the build directory.")

# Library

add_library(cowl ${COWL_LIBRARY_TYPE} ${COWL_SOURCES})
set_target_properties(cowl PROPERTIES
                      PUBLIC_HEADER "${COWL_PUBLIC_HEADERS}"
                      C_VISIBILITY_PRESET hidden
                      VISIBILITY_INLINES_HIDDEN ON)
target_compile_features(cowl PRIVATE ${COWL_COMPILE_FEATURES})
target_compile_options(cowl PRIVATE ${COWL_WARNING_OPTIONS})
target_compile_definitions(cowl
                           PUBLIC ${COWL_PUBLIC_DEFINES}
                           PRIVATE ${COWL_PRIVATE_DEFINES})
target_include_directories(cowl
                           PUBLIC ${COWL_PUBLIC_HEADERS_DIRS}
                           PRIVATE ${COWL_PRIVATE_HEADERS_DIRS})
target_link_libraries(cowl PUBLIC ulib)
add_dependencies(cowl cowl-readers cowl-headers)

if(COWL_LIBRARY_TYPE STREQUAL "SHARED")
    target_compile_definitions(cowl PUBLIC COWL_SHARED)
endif()

if(COWL_LTO_ENABLED)
    set_property(TARGET cowl PROPERTY INTERPROCEDURAL_OPTIMIZATION ON)
endif()

# Subprojects

add_subdirectory("${COWL_DOCS_DIR}")
add_subdirectory("${COWL_EXAMPLES_DIR}")
add_subdirectory("${COWL_TEST_DIR}")
