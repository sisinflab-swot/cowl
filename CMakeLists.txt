#################
# Configuration #
#################

# CMake

cmake_minimum_required(VERSION 3.16)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake" "${CMAKE_MODULE_PATH}")

# Project

set(COWL_VERSION_MAJOR 0)
set(COWL_VERSION_MINOR 4)
set(COWL_VERSION_PATCH 0)
set(COWL_VERSION "${COWL_VERSION_MAJOR}.${COWL_VERSION_MINOR}.${COWL_VERSION_PATCH}")

project(Cowl
        VERSION "${COWL_VERSION}"
        DESCRIPTION "A lightweight C API for working with OWL ontologies."
        HOMEPAGE_URL "http://swot.sisinflab.poliba.it/cowl"
        LANGUAGES C)

set(COWL_VENDOR "SisInf Lab, Polytechnic University of Bari")
set(COWL_COPYRIGHT_YEAR "2019-2020")
set(COWL_GIT_URL "https://github.com/sisinflab-swot/cowl")

# Options

option(COWL_EMBEDDED "Enable optimizations for embedded platforms" OFF)
option(COWL_LTO "Enable link-time optimization, if available" ON)
option(COWL_DEBUG_LEAKS "Enable debugging of memory leaks. Keep off in production builds." OFF)
set(COWL_ALLOC_HEADERS "" CACHE STRING "Header files that declare custom allocation primitives.")
set(COWL_ALLOC_SOURCES "" CACHE STRING "Source files that implement custom allocation primitives.")

# Directories

set(COWL_PROJECT_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(COWL_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}")
set(COWL_PUBLIC_HEADERS_DIR "${COWL_PROJECT_DIR}/include")
set(COWL_LIB_DIR "${COWL_PROJECT_DIR}/lib")
set(COWL_SRC_DIR "${COWL_PROJECT_DIR}/src")
set(COWL_PRIVATE_HEADERS_DIR "${COWL_SRC_DIR}/include")
set(COWL_PARSER_DIR "${COWL_SRC_DIR}/parser")
set(COWL_FUNCTIONAL_PARSER_DIR "${COWL_PARSER_DIR}/functional")

set(COWL_DATA_DIR "${COWL_PROJECT_DIR}/data")
set(COWL_DOCS_DIR "${COWL_PROJECT_DIR}/docs")
set(COWL_EXAMPLES_DIR "${COWL_PROJECT_DIR}/examples")
set(COWL_TEST_DIR "${COWL_PROJECT_DIR}/test")

set(COWL_HEADERS_OUT_DIR "${COWL_OUTPUT_DIR}/include")
set(COWL_PARSER_OUT_DIR "${COWL_OUTPUT_DIR}/flex_bison")

file(MAKE_DIRECTORY "${COWL_PARSER_OUT_DIR}")

# Target settings

set(COWL_COMPILE_FEATURES c_std_11)

if(COWL_DEBUG_LEAKS)
    file(GLOB COWL_ALLOC_HEADERS CONFIGURE_DEPENDS "${COWL_TEST_DIR}/leak/*.h")
    file(GLOB COWL_ALLOC_SOURCES CONFIGURE_DEPENDS "${COWL_TEST_DIR}/leak/*.c")
endif()

if(COWL_ALLOC_HEADERS)
    set(COWL_MALLOC_FN cowl_custom_malloc)
    set(COWL_REALLOC_FN cowl_custom_realloc)
    set(COWL_FREE_FN cowl_custom_free)
else()
    set(COWL_MALLOC_FN malloc)
    set(COWL_REALLOC_FN realloc)
    set(COWL_FREE_FN free)
endif()

set(ULIB_MALLOC ${COWL_MALLOC_FN})
set(ULIB_REALLOC ${COWL_REALLOC_FN})
set(ULIB_FREE ${COWL_FREE_FN})

list(APPEND COWL_PUBLIC_DEFINES
     cowl_malloc=${COWL_MALLOC_FN}
     cowl_realloc=${COWL_REALLOC_FN}
     cowl_free=${COWL_FREE_FN})

list(APPEND COWL_PRIVATE_DEFINES
     COWL_VERSION_MAJOR=${COWL_VERSION_MAJOR}
     COWL_VERSION_MINOR=${COWL_VERSION_MINOR}
     COWL_VERSION_PATCH=${COWL_VERSION_PATCH})

if(MSVC)
    set(COWL_WARNING_OPTIONS /W3 /wd4996)
    list(APPEND COWL_PRIVATE_DEFINES COWL_DLL)
    list(APPEND COWL_FLEX_FLAGS --wincompat)
else()
    set(COWL_WARNING_OPTIONS -Wall -Wextra)
endif()

if(COWL_LTO)
    include(CheckIPOSupported)
    check_ipo_supported(RESULT COWL_LTO_ENABLED)
endif()

if(COWL_EMBEDDED)
    list(APPEND COWL_PUBLIC_DEFINES COWL_TINY)
    set(ULIB_EMBEDDED ON)
else()
    list(APPEND COWL_FLEX_FLAGS -Cfe)
endif()

list(JOIN COWL_FLEX_FLAGS " " COWL_FLEX_FLAGS)

# Flex & Bison

set(COWL_FUNCTIONAL_LEXER_IN "${COWL_FUNCTIONAL_PARSER_DIR}/cowl_functional_lexer.l")
set(COWL_FUNCTIONAL_LEXER_HEADER "${COWL_PARSER_OUT_DIR}/cowl_functional_lexer.h")
set(COWL_FUNCTIONAL_LEXER_OUT "${COWL_PARSER_OUT_DIR}/cowl_functional_lexer.c")

set(COWL_FUNCTIONAL_PARSER_IN "${COWL_FUNCTIONAL_PARSER_DIR}/cowl_functional_parser.y")
set(COWL_FUNCTIONAL_PARSER_HEADER "${COWL_PARSER_OUT_DIR}/cowl_functional_parser.h")
set(COWL_FUNCTIONAL_PARSER_OUT "${COWL_PARSER_OUT_DIR}/cowl_functional_parser.c")

find_package(BISON 3.0 REQUIRED)
find_package(FLEX 2.6.4 REQUIRED)

# uLib

if(NOT TARGET ulib)
    add_subdirectory("${COWL_LIB_DIR}/ulib" EXCLUDE_FROM_ALL)
endif()

# Header dirs

get_target_property(COWL_ULIB_HEADERS_DIRS ulib INTERFACE_INCLUDE_DIRECTORIES)
set(COWL_PUBLIC_HEADERS_DIRS "${COWL_PUBLIC_HEADERS_DIR}" ${COWL_ULIB_HEADERS_DIRS})

set(COWL_PRIVATE_HEADERS_DIRS
    "${COWL_PRIVATE_HEADERS_DIR}"
    "${COWL_SRC_DIR}"
    "${COWL_PARSER_DIR}"
    "${COWL_PARSER_OUT_DIR}")

# Header files

file(GLOB COWL_PUBLIC_HEADERS CONFIGURE_DEPENDS "${COWL_PUBLIC_HEADERS_DIR}/*.h")
get_target_property(COWL_ULIB_HEADERS ulib INTERFACE_SOURCES)
list(APPEND COWL_PUBLIC_HEADERS ${COWL_ULIB_HEADERS})

# Sources

file(GLOB COWL_SOURCES CONFIGURE_DEPENDS
     "${COWL_SRC_DIR}/*.c"
     "${COWL_PARSER_DIR}/*.c")

list(APPEND COWL_SOURCES ${COWL_ALLOC_SOURCES})

###############
### Targets ###
###############

# Flex & Bison

bison_target(COWL_FUNCTIONAL_PARSER "${COWL_FUNCTIONAL_PARSER_IN}" "${COWL_FUNCTIONAL_PARSER_OUT}"
             DEFINES_FILE "${COWL_FUNCTIONAL_PARSER_HEADER}")
flex_target(COWL_FUNCTIONAL_LEXER "${COWL_FUNCTIONAL_LEXER_IN}" "${COWL_FUNCTIONAL_LEXER_OUT}"
            COMPILE_FLAGS "${COWL_FLEX_FLAGS}"
            DEFINES_FILE "${COWL_FUNCTIONAL_LEXER_HEADER}")
add_flex_bison_dependency(COWL_FUNCTIONAL_LEXER COWL_FUNCTIONAL_PARSER)

# Copy headers

add_custom_target(cowl-headers
                  COMMAND "${CMAKE_COMMAND}" -E remove_directory "${COWL_HEADERS_OUT_DIR}"
                  COMMAND "${CMAKE_COMMAND}" -E make_directory "${COWL_HEADERS_OUT_DIR}"
                  COMMAND ${CMAKE_COMMAND} -E copy
                          ${COWL_PUBLIC_HEADERS} "${COWL_HEADERS_OUT_DIR}"
                  COMMENT "Copy headers to the build directory.")

# Static library

add_library(cowl-static STATIC EXCLUDE_FROM_ALL
            ${COWL_SOURCES}
            ${FLEX_COWL_FUNCTIONAL_LEXER_OUTPUTS}
            ${BISON_COWL_FUNCTIONAL_PARSER_OUTPUT_SOURCE})

set_target_properties(cowl-static PROPERTIES
                      OUTPUT_NAME "cowl"
                      PUBLIC_HEADER "${COWL_PUBLIC_HEADERS}"
                      C_VISIBILITY_PRESET hidden
                      VISIBILITY_INLINES_HIDDEN ON)
target_compile_features(cowl-static PRIVATE ${COWL_COMPILE_FEATURES})
target_compile_options(cowl-static PRIVATE ${COWL_WARNING_OPTIONS})
target_compile_definitions(cowl-static
                           PUBLIC ${COWL_PUBLIC_DEFINES}
                           PRIVATE ${COWL_PRIVATE_DEFINES})
target_include_directories(cowl-static
                           PUBLIC ${COWL_PUBLIC_HEADERS_DIRS}
                           PRIVATE ${COWL_PRIVATE_HEADERS_DIRS})
target_precompile_headers(cowl-static PUBLIC ${COWL_ALLOC_HEADERS})
target_link_libraries(cowl-static PUBLIC ulib)
add_dependencies(cowl-static cowl-headers)

if(COWL_LTO_ENABLED)
    set_property(TARGET cowl-static PROPERTY INTERPROCEDURAL_OPTIMIZATION ON)
endif()

# Shared library

add_library(cowl-shared SHARED EXCLUDE_FROM_ALL
            ${COWL_SOURCES}
            ${FLEX_COWL_FUNCTIONAL_LEXER_OUTPUTS}
            ${BISON_COWL_FUNCTIONAL_PARSER_OUTPUT_SOURCE})

set_target_properties(cowl-shared PROPERTIES
                      OUTPUT_NAME "cowl"
                      PUBLIC_HEADER "${COWL_PUBLIC_HEADERS}"
                      C_VISIBILITY_PRESET hidden
                      VISIBILITY_INLINES_HIDDEN ON)
target_compile_features(cowl-shared PRIVATE ${COWL_COMPILE_FEATURES})
target_compile_options(cowl-shared PRIVATE ${COWL_WARNING_OPTIONS})
target_compile_definitions(cowl-shared
                           PUBLIC ${COWL_PUBLIC_DEFINES}
                           PRIVATE ${COWL_PRIVATE_DEFINES})
target_include_directories(cowl-shared
                           PUBLIC ${COWL_PUBLIC_HEADERS_DIRS}
                           PRIVATE ${COWL_PRIVATE_HEADERS_DIRS})
target_precompile_headers(cowl-shared PUBLIC ${COWL_ALLOC_HEADERS})
target_link_libraries(cowl-shared PUBLIC ulib)
add_dependencies(cowl-shared cowl-headers)

if(COWL_LTO_ENABLED)
    set_property(TARGET cowl-shared PROPERTY INTERPROCEDURAL_OPTIMIZATION ON)
endif()

# Subprojects

add_subdirectory("${COWL_DOCS_DIR}")
add_subdirectory("${COWL_EXAMPLES_DIR}")
add_subdirectory("${COWL_TEST_DIR}")

# Main target

add_custom_target(cowl ALL COMMENT "Build Cowl")
add_dependencies(cowl cowl-static cowl-shared)
