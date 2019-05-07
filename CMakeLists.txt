cmake_minimum_required(VERSION 3.0)
project(cowl C)

#################
# Configuration #
#################

# Project metadata

set(COWL_NAME "Cowl")
set(COWL_DESCRIPTION "C API to work with OWL ontologies.")
set(COWL_VERSION "1.0.0")

# Directories

set(COWL_PUBLIC_HEADERS_DIR "${CMAKE_CURRENT_LIST_DIR}/include")
set(COWL_LIB_DIR "${CMAKE_CURRENT_LIST_DIR}/lib")
set(COWL_VECTOR_DIR "${COWL_LIB_DIR}/vector_t/include")
set(COWL_UHASH_DIR "${COWL_LIB_DIR}/uhash/include")
set(COWL_SRC_DIR "${CMAKE_CURRENT_LIST_DIR}/src")
set(COWL_PRIVATE_HEADERS_DIR "${COWL_SRC_DIR}/include")
set(COWL_MODEL_DIR "${COWL_SRC_DIR}/model")
set(COWL_PARSER_DIR "${COWL_SRC_DIR}/parser")
set(COWL_LOGGER_DIR "${COWL_SRC_DIR}/logger")
set(COWL_PARSER_OUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/flex_bison")
set(COWL_FUNCTIONAL_PARSER_DIR "${COWL_PARSER_DIR}/functional")
set(COWL_TEST_DIR "${CMAKE_CURRENT_LIST_DIR}/test")
set(COWL_TEST_DATA_DIR "${COWL_TEST_DIR}/data")

# Build dir setup

file(MAKE_DIRECTORY "${COWL_PARSER_OUT_DIR}")

file(GLOB COWL_TEST_DATA "${COWL_TEST_DATA_DIR}/*.owl")
file(COPY ${COWL_TEST_DATA} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

# Flex & Bison

set(COWL_FUNCTIONAL_LEXER_IN "${COWL_FUNCTIONAL_PARSER_DIR}/cowl_functional_lexer.l")
set(COWL_FUNCTIONAL_LEXER_HEADER "${COWL_PARSER_OUT_DIR}/cowl_functional_lexer.h")
set(COWL_FUNCTIONAL_LEXER_OUT "${COWL_PARSER_OUT_DIR}/cowl_functional_lexer.c")

set(COWL_FUNCTIONAL_PARSER_IN "${COWL_FUNCTIONAL_PARSER_DIR}/cowl_functional_parser.y")
set(COWL_FUNCTIONAL_PARSER_HEADER "${COWL_PARSER_OUT_DIR}/cowl_functional_parser.h")
set(COWL_FUNCTIONAL_PARSER_OUT "${COWL_PARSER_OUT_DIR}/cowl_functional_parser.c")

find_package(BISON 3.1 REQUIRED)
find_package(FLEX 2.6 REQUIRED)

BISON_TARGET(COWL_FUNCTIONAL_PARSER "${COWL_FUNCTIONAL_PARSER_IN}" "${COWL_FUNCTIONAL_PARSER_OUT}"
             DEFINES_FILE "${COWL_FUNCTIONAL_PARSER_HEADER}")
FLEX_TARGET(COWL_FUNCTIONAL_LEXER "${COWL_FUNCTIONAL_LEXER_IN}" "${COWL_FUNCTIONAL_LEXER_OUT}"
            DEFINES_FILE "${COWL_FUNCTIONAL_LEXER_HEADER}")
ADD_FLEX_BISON_DEPENDENCY(COWL_FUNCTIONAL_LEXER COWL_FUNCTIONAL_PARSER)

# Header dirs

set(COWL_HEADERS_DIRS
    "${COWL_PUBLIC_HEADERS_DIR}"
    "${COWL_PRIVATE_HEADERS_DIR}"
    "${COWL_VECTOR_DIR}"
    "${COWL_UHASH_DIR}"
    "${COWL_MODEL_DIR}"
    "${COWL_PARSER_DIR}"
    "${COWL_LOGGER_DIR}"
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
     "${COWL_LOGGER_DIR}/*.c")

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

if (NOT COWL_DEBUG_FLAGS)
    set(COWL_DEBUG_FLAGS ${COWL_DEFAULT_DEBUG_FLAGS})
endif ()

if (NOT COWL_RELEASE_FLAGS)
    set(COWL_RELEASE_FLAGS ${COWL_DEFAULT_RELEASE_FLAGS})
endif ()

if (COWL_EMBEDDED)
    message(STATUS "Embedded build selected")
    set(COWL_DEFINES VECTOR_TINY UHASH_TINY)
endif()

# Static library

add_library(cowl-static STATIC
            ${COWL_SOURCES}
            ${FLEX_COWL_FUNCTIONAL_LEXER_OUTPUTS}
            ${BISON_COWL_FUNCTIONAL_PARSER_OUTPUT_SOURCE})

set_target_properties(cowl-static PROPERTIES
                      OUTPUT_NAME "cowl"
                      PUBLIC_HEADER "${COWL_ALL_PUBLIC_HEADERS}")
target_compile_options(cowl-static PUBLIC
                       "$<$<CONFIG:DEBUG>:${COWL_DEBUG_FLAGS}>"
                       "$<$<CONFIG:RELEASE>:${COWL_RELEASE_FLAGS}>")
target_compile_definitions(cowl-static PUBLIC ${COWL_DEFINES})
target_include_directories(cowl-static PUBLIC ${COWL_HEADERS_DIRS})

install(TARGETS cowl-static
        ARCHIVE DESTINATION "${CMAKE_CURRENT_BINARY_DIR}"
        PUBLIC_HEADER DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/include")

# Shared library

add_library(cowl-shared SHARED
            ${COWL_SOURCES}
            ${FLEX_COWL_FUNCTIONAL_LEXER_OUTPUTS}
            ${BISON_COWL_FUNCTIONAL_PARSER_OUTPUT_SOURCE})

set_target_properties(cowl-shared PROPERTIES
                      OUTPUT_NAME "cowl"
                      PUBLIC_HEADER "${COWL_ALL_PUBLIC_HEADERS}")
target_compile_options(cowl-shared PUBLIC
                       "$<$<CONFIG:DEBUG>:${COWL_DEBUG_FLAGS}>"
                       "$<$<CONFIG:RELEASE>:${COWL_RELEASE_FLAGS}>")
target_compile_definitions(cowl-shared PUBLIC ${COWL_DEFINES})
target_include_directories(cowl-shared PUBLIC ${COWL_HEADERS_DIRS})

install(TARGETS cowl-shared
        LIBRARY DESTINATION "${CMAKE_CURRENT_BINARY_DIR}"
        PUBLIC_HEADER DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/include")

# Test

add_executable(cowl-test "${COWL_TEST_DIR}/test.c")
add_dependencies(cowl-test cowl-static)
target_compile_definitions(cowl-test PUBLIC ${COWL_DEFINES})
target_include_directories(cowl-test PUBLIC "${COWL_HEADERS_DIRS}")
target_link_libraries(cowl-test cowl-static)
