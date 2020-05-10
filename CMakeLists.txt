#################
# Configuration #
#################

# CMake

cmake_minimum_required(VERSION 3.12)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake" "${CMAKE_MODULE_PATH}")

# Project

project(Cowl
        VERSION 0.2.2
        DESCRIPTION "A lightweight C API for working with OWL ontologies."
        HOMEPAGE_URL "http://sisinflab.poliba.it/swottools/cowl"
        LANGUAGES C)

set(COWL_VENDOR "SisInf Lab, Polytechnic University of Bari")
set(COWL_COPYRIGHT_YEAR "2019-2020")
set(COWL_GIT_URL "https://github.com/sisinflab-swot/cowl")

# Directories

set(COWL_PROJECT_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(COWL_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}")
set(COWL_PUBLIC_HEADERS_DIR "${COWL_PROJECT_DIR}/include")
set(COWL_LIB_DIR "${COWL_PROJECT_DIR}/lib")
set(COWL_SRC_DIR "${COWL_PROJECT_DIR}/src")
set(COWL_PRIVATE_HEADERS_DIR "${COWL_SRC_DIR}/include")
set(COWL_MODEL_DIR "${COWL_SRC_DIR}/model")
set(COWL_IO_DIR "${COWL_SRC_DIR}/io")
set(COWL_PARSER_DIR "${COWL_IO_DIR}/parser")
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
find_package(FLEX 2.6.4 REQUIRED)

# Vector(T) and uHash

if(NOT TARGET vector)
    add_subdirectory("${COWL_LIB_DIR}/vector_t" EXCLUDE_FROM_ALL)
endif()

if(NOT TARGET uhash)
    add_subdirectory("${COWL_LIB_DIR}/uhash" EXCLUDE_FROM_ALL)
endif()

# Header dirs

get_target_property(COWL_VECTOR_HEADERS_DIRS vector INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(COWL_UHASH_HEADERS_DIRS uhash INTERFACE_INCLUDE_DIRECTORIES)

set(COWL_PUBLIC_HEADERS_DIRS "${COWL_PUBLIC_HEADERS_DIR}")
list(APPEND COWL_PUBLIC_HEADERS_DIRS ${COWL_VECTOR_HEADERS_DIRS} ${COWL_UHASH_HEADERS_DIRS})

set(COWL_PRIVATE_HEADERS_DIRS
    "${COWL_PRIVATE_HEADERS_DIR}"
    "${COWL_MODEL_DIR}"
    "${COWL_IO_DIR}"
    "${COWL_PARSER_DIR}"
    "${COWL_PARSER_OUT_DIR}")

# Header files

get_target_property(COWL_VECTOR_HEADERS vector INTERFACE_SOURCES)
get_target_property(COWL_UHASH_HEADERS uhash INTERFACE_SOURCES)

file(GLOB COWL_PUBLIC_HEADERS CONFIGURE_DEPENDS "${COWL_PUBLIC_HEADERS_DIR}/*.h")
list(APPEND COWL_PUBLIC_HEADERS ${COWL_VECTOR_HEADERS} ${COWL_UHASH_HEADERS})

# Sources

file(GLOB COWL_SOURCES CONFIGURE_DEPENDS
     "${COWL_MODEL_DIR}/*.c"
     "${COWL_IO_DIR}/*.c"
     "${COWL_PARSER_DIR}/*.c")

###############
### Targets ###
###############

# Options

option(COWL_EMBEDDED "Enable optimizations for embedded platforms" OFF)
option(COWL_LTO "Enable link-time optimization, if available" ON)

# Defaults

set(COWL_COMPILE_FEATURES c_std_11)
list(APPEND COWL_PUBLIC_DEFINES
     VECTOR_MALLOC=cowl_malloc
     VECTOR_REALLOC=cowl_realloc
     VECTOR_FREE=cowl_free
     UHASH_MALLOC=cowl_malloc
     UHASH_REALLOC=cowl_realloc
     UHASH_FREE=cowl_free)

if(MSVC)
    set(COWL_WARNING_OPTIONS /W4)
    list(APPEND COWL_PRIVATE_DEFINES COWL_DLL)
else()
    set(COWL_WARNING_OPTIONS -Wall -Wextra)
endif()

if(COWL_LTO)
    include(CheckIPOSupported)
    check_ipo_supported(RESULT COWL_LTO_ENABLED)
endif()

if(COWL_EMBEDDED)
    message(STATUS "Embedded build selected")
    list(APPEND COWL_PUBLIC_DEFINES COWL_TINY VECTOR_TINY UHASH_TINY)
else()
    message(STATUS "Desktop build selected")
    set(COWL_FLEX_FLAGS -Cfe)
endif()

# Flex & Bison

bison_target(COWL_FUNCTIONAL_PARSER "${COWL_FUNCTIONAL_PARSER_IN}" "${COWL_FUNCTIONAL_PARSER_OUT}"
             DEFINES_FILE "${COWL_FUNCTIONAL_PARSER_HEADER}")
flex_target(COWL_FUNCTIONAL_LEXER "${COWL_FUNCTIONAL_LEXER_IN}" "${COWL_FUNCTIONAL_LEXER_OUT}"
            COMPILE_FLAGS ${COWL_FLEX_FLAGS}
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
target_link_libraries(cowl-static PUBLIC vector uhash)
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
target_link_libraries(cowl-shared PUBLIC vector uhash)
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
