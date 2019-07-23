#################
# Configuration #
#################

# Cmake

cmake_minimum_required(VERSION 3.0)
cmake_policy(SET CMP0063 NEW)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake" "${CMAKE_MODULE_PATH}")

# Project

project(Cowl
        VERSION 0.2.0
        DESCRIPTION "A lightweight C API for working with OWL ontologies."
        HOMEPAGE_URL "http://sisinflab.poliba.it/swottools/cowl"
        LANGUAGES C)

set(COWL_VENDOR "SisInf Lab, Polytechnic University of Bari")
set(COWL_COPYRIGHT_YEAR "2019")
set(COWL_GIT_URL "https://github.com/sisinflab-swot/cowl")

# Directories

set(COWL_PROJECT_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(COWL_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}")
set(COWL_PUBLIC_HEADERS_DIR "${COWL_PROJECT_DIR}/include")
set(COWL_LIB_DIR "${COWL_PROJECT_DIR}/lib")
set(COWL_SRC_DIR "${COWL_PROJECT_DIR}/src")
set(COWL_VECTOR_DIR "${COWL_LIB_DIR}/vector_t/include")
set(COWL_UHASH_DIR "${COWL_LIB_DIR}/uhash/include")
set(COWL_PRIVATE_HEADERS_DIR "${COWL_SRC_DIR}/include")
set(COWL_MODEL_DIR "${COWL_SRC_DIR}/model")
set(COWL_PARSER_DIR "${COWL_SRC_DIR}/parser")
set(COWL_UTIL_DIR "${COWL_SRC_DIR}/util")
set(COWL_FUNCTIONAL_PARSER_DIR "${COWL_PARSER_DIR}/functional")

set(COWL_DATA_DIR "${COWL_PROJECT_DIR}/data")
set(COWL_DOCS_DIR "${COWL_PROJECT_DIR}/docs")
set(COWL_EXAMPLES_DIR "${COWL_PROJECT_DIR}/examples")
set(COWL_TEST_DIR "${COWL_PROJECT_DIR}/test")

set(COWL_HEADERS_OUT_DIR "${COWL_OUTPUT_DIR}/include")
set(COWL_PARSER_OUT_DIR "${COWL_OUTPUT_DIR}/flex_bison")

file(MAKE_DIRECTORY "${COWL_PARSER_OUT_DIR}")

# Flex & Bison

set(COWL_FUNCTIONAL_LEXER_IN "${COWL_FUNCTIONAL_PARSER_DIR}/cowl_functional_lexer.l")
set(COWL_FUNCTIONAL_LEXER_HEADER "${COWL_PARSER_OUT_DIR}/cowl_functional_lexer.h")
set(COWL_FUNCTIONAL_LEXER_OUT "${COWL_PARSER_OUT_DIR}/cowl_functional_lexer.c")

set(COWL_FUNCTIONAL_PARSER_IN "${COWL_FUNCTIONAL_PARSER_DIR}/cowl_functional_parser.y")
set(COWL_FUNCTIONAL_PARSER_HEADER "${COWL_PARSER_OUT_DIR}/cowl_functional_parser.h")
set(COWL_FUNCTIONAL_PARSER_OUT "${COWL_PARSER_OUT_DIR}/cowl_functional_parser.c")

find_package(BISON 3.0 REQUIRED)
find_package(FLEX 2.6 REQUIRED)

# Header dirs

set(COWL_HEADERS_DIRS
    "${COWL_PUBLIC_HEADERS_DIR}"
    "${COWL_PRIVATE_HEADERS_DIR}"
    "${COWL_VECTOR_DIR}"
    "${COWL_UHASH_DIR}"
    "${COWL_MODEL_DIR}"
    "${COWL_PARSER_DIR}"
    "${COWL_UTIL_DIR}"
    "${COWL_PARSER_OUT_DIR}")

# Header files

set(COWL_LIB_HEADERS
    "${COWL_VECTOR_DIR}/vector.h"
    "${COWL_UHASH_DIR}/uhash.h")

file(GLOB COWL_PUBLIC_HEADERS
     "${COWL_PUBLIC_HEADERS_DIR}/*.h")

set(COWL_ALL_PUBLIC_HEADERS ${COWL_LIB_HEADERS} ${COWL_PUBLIC_HEADERS})

# Sources

file(GLOB COWL_SOURCES
     "${COWL_MODEL_DIR}/*.c"
     "${COWL_PARSER_DIR}/*.c"
     "${COWL_UTIL_DIR}/*.c")

###############
### Targets ###
###############

# Defaults

set(CMAKE_C_STANDARD 11)

set(COWL_DEFAULT_BUILD_TYPE "Release")

if (MSVC)
    set(COWL_DEFAULT_DEBUG_FLAGS /Zi /W4)
    set(COWL_DEFAULT_RELEASE_FLAGS /O2 /GL /W4)
else ()
    set(COWL_DEFAULT_DEBUG_FLAGS -g -Wall -Wextra)
    set(COWL_DEFAULT_RELEASE_FLAGS -O3 -flto -Wall -Wextra)
endif ()

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "No build type selected, default to ${COWL_DEFAULT_BUILD_TYPE}")
    set(CMAKE_BUILD_TYPE "${COWL_DEFAULT_BUILD_TYPE}" CACHE STRING
        "Build type (default ${COWL_DEFAULT_BUILD_TYPE})" FORCE)
endif ()

# Compiler flags

if (COWL_EMBEDDED)
    message(STATUS "Embedded build selected")
    set(COWL_DEFINES VECTOR_TINY UHASH_TINY)

    if (MSVC)
        set(COWL_DEFAULT_RELEASE_FLAGS /Os /GL /W4)
    else()
        set(COWL_DEFAULT_RELEASE_FLAGS -Os -flto -Wall -Wextra)
    endif()
else()
    message(STATUS "Desktop build selected")
    set(FLEX_FLAGS -Cfe)
endif()

if (NOT COWL_DEBUG_FLAGS)
    set(COWL_DEBUG_FLAGS ${COWL_DEFAULT_DEBUG_FLAGS})
endif ()

if (NOT COWL_RELEASE_FLAGS)
    set(COWL_RELEASE_FLAGS ${COWL_DEFAULT_RELEASE_FLAGS})
endif ()

# Flex & Bison

BISON_TARGET(COWL_FUNCTIONAL_PARSER "${COWL_FUNCTIONAL_PARSER_IN}" "${COWL_FUNCTIONAL_PARSER_OUT}"
             DEFINES_FILE "${COWL_FUNCTIONAL_PARSER_HEADER}")
FLEX_TARGET(COWL_FUNCTIONAL_LEXER "${COWL_FUNCTIONAL_LEXER_IN}" "${COWL_FUNCTIONAL_LEXER_OUT}"
            COMPILE_FLAGS ${FLEX_FLAGS}
            DEFINES_FILE "${COWL_FUNCTIONAL_LEXER_HEADER}")
ADD_FLEX_BISON_DEPENDENCY(COWL_FUNCTIONAL_LEXER COWL_FUNCTIONAL_PARSER)

# Static library

add_library(cowl-static STATIC
            ${COWL_SOURCES}
            ${FLEX_COWL_FUNCTIONAL_LEXER_OUTPUTS}
            ${BISON_COWL_FUNCTIONAL_PARSER_OUTPUT_SOURCE})

set_target_properties(cowl-static PROPERTIES
                      OUTPUT_NAME "cowl"
                      PUBLIC_HEADER "${COWL_ALL_PUBLIC_HEADERS}"
                      C_VISIBILITY_PRESET hidden
                      VISIBILITY_INLINES_HIDDEN ON)
target_compile_options(cowl-static PUBLIC
                       "$<$<CONFIG:DEBUG>:${COWL_DEBUG_FLAGS}>"
                       "$<$<CONFIG:RELEASE>:${COWL_RELEASE_FLAGS}>")
target_compile_definitions(cowl-static PUBLIC ${COWL_DEFINES})
target_include_directories(cowl-static PUBLIC ${COWL_HEADERS_DIRS})

# Shared library

add_library(cowl-shared SHARED
            ${COWL_SOURCES}
            ${FLEX_COWL_FUNCTIONAL_LEXER_OUTPUTS}
            ${BISON_COWL_FUNCTIONAL_PARSER_OUTPUT_SOURCE})

set_target_properties(cowl-shared PROPERTIES
                      OUTPUT_NAME "cowl"
                      PUBLIC_HEADER "${COWL_ALL_PUBLIC_HEADERS}"
                      C_VISIBILITY_PRESET hidden
                      VISIBILITY_INLINES_HIDDEN ON)
target_compile_options(cowl-shared PUBLIC
                       "$<$<CONFIG:DEBUG>:${COWL_DEBUG_FLAGS}>"
                       "$<$<CONFIG:RELEASE>:${COWL_RELEASE_FLAGS}>")
target_compile_definitions(cowl-shared PUBLIC ${COWL_DEFINES})
target_include_directories(cowl-shared PUBLIC ${COWL_HEADERS_DIRS})

# Subprojects

add_subdirectory("${COWL_DOCS_DIR}")
add_subdirectory("${COWL_EXAMPLES_DIR}")
add_subdirectory("${COWL_TEST_DIR}")

# Main target

option(COWL_BUILD_DOCS "Generate documentation" ON)

add_custom_target(cowl
                  COMMAND "${CMAKE_COMMAND}" -E remove_directory "${COWL_HEADERS_OUT_DIR}"
                  COMMAND "${CMAKE_COMMAND}" -E make_directory "${COWL_HEADERS_OUT_DIR}"
                  COMMAND ${CMAKE_COMMAND} -E copy
                          ${COWL_ALL_PUBLIC_HEADERS} "${COWL_HEADERS_OUT_DIR}"
                  COMMENT "Build Cowl")

if (COWL_BUILD_DOCS)
    add_dependencies(cowl cowl-docs)
else()
    message(STATUS "Skipping docs generation.")
endif()

add_dependencies(cowl cowl-static cowl-shared)
