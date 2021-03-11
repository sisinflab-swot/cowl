#################
# Configuration #
#################

# CMake

cmake_minimum_required(VERSION 3.18)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake" "${CMAKE_MODULE_PATH}")

# Project

set(COWL_VERSION_MAJOR 0)
set(COWL_VERSION_MINOR 4)
set(COWL_VERSION_PATCH 1)
set(COWL_VERSION "${COWL_VERSION_MAJOR}.${COWL_VERSION_MINOR}.${COWL_VERSION_PATCH}")

project(Cowl
        VERSION "${COWL_VERSION}"
        DESCRIPTION "A lightweight C API for working with OWL ontologies."
        HOMEPAGE_URL "http://swot.sisinflab.poliba.it/cowl"
        LANGUAGES C)

set(COWL_VENDOR "SisInf Lab, Polytechnic University of Bari")
set(COWL_COPYRIGHT_YEAR "2019-2021")
set(COWL_GIT_URL "https://github.com/sisinflab-swot/cowl")

# Options

option(COWL_EMBEDDED "Enable optimizations for embedded platforms" OFF)
option(COWL_LTO "Enable link-time optimization, if available" ON)
option(COWL_DEBUG_LEAKS "Enable debugging of memory leaks (keep OFF in production builds)" OFF)
option(COWL_PARSER_FUNCTIONAL "Include functional syntax parser" ON)
set(COWL_USER_HEADERS "" CACHE STRING "User-specified header files")
set(COWL_USER_SOURCES "" CACHE STRING "User-specified source files")
set(COWL_MALLOC "malloc" CACHE STRING "malloc function override")
set(COWL_REALLOC "realloc" CACHE STRING "realloc function override")
set(COWL_FREE "free" CACHE STRING "free function override")

# Directories

set(COWL_PROJECT_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(COWL_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}")
set(COWL_PUBLIC_HEADERS_DIR "${COWL_PROJECT_DIR}/include")
set(COWL_LIB_DIR "${COWL_PROJECT_DIR}/lib")
set(COWL_SRC_DIR "${COWL_PROJECT_DIR}/src")
set(COWL_PRIVATE_HEADERS_DIR "${COWL_SRC_DIR}/include")
set(COWL_PARSER_DIR "${COWL_SRC_DIR}/parser")
set(COWL_FUNC_PARSER_DIR "${COWL_PARSER_DIR}/functional")

set(COWL_DATA_DIR "${COWL_PROJECT_DIR}/data")
set(COWL_DOCS_DIR "${COWL_PROJECT_DIR}/docs")
set(COWL_EXAMPLES_DIR "${COWL_PROJECT_DIR}/examples")
set(COWL_TEST_DIR "${COWL_PROJECT_DIR}/test")

set(COWL_HEADERS_OUT_DIR "${COWL_OUTPUT_DIR}/include")

# Target settings

set(COWL_COMPILE_FEATURES c_std_11)

if(COWL_DEBUG_LEAKS)
    file(GLOB COWL_LEAK_HEADERS CONFIGURE_DEPENDS "${COWL_TEST_DIR}/leak/*.h")
    file(GLOB COWL_LEAK_SOURCES CONFIGURE_DEPENDS "${COWL_TEST_DIR}/leak/*.c")
    list(APPEND COWL_USER_HEADERS ${COWL_LEAK_HEADERS})
    list(APPEND COWL_USER_SOURCES ${COWL_LEAK_SOURCES})
    set(COWL_MALLOC cowl_custom_malloc)
    set(COWL_REALLOC cowl_custom_realloc)
    set(COWL_FREE cowl_custom_free)
endif()

set(ULIB_MALLOC ${COWL_MALLOC})
set(ULIB_REALLOC ${COWL_REALLOC})
set(ULIB_FREE ${COWL_FREE})

list(APPEND COWL_PUBLIC_DEFINES
     cowl_malloc=${COWL_MALLOC}
     cowl_realloc=${COWL_REALLOC}
     cowl_free=${COWL_FREE})

list(APPEND COWL_PRIVATE_DEFINES
     COWL_VERSION_MAJOR=${COWL_VERSION_MAJOR}
     COWL_VERSION_MINOR=${COWL_VERSION_MINOR}
     COWL_VERSION_PATCH=${COWL_VERSION_PATCH})

if(MSVC)
    set(COWL_WARNING_OPTIONS /W3 /wd4996)
    list(APPEND COWL_PRIVATE_DEFINES COWL_DLL)
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
endif()

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
    "${COWL_PARSER_DIR}")

# Header files

file(GLOB COWL_PUBLIC_HEADERS CONFIGURE_DEPENDS "${COWL_PUBLIC_HEADERS_DIR}/*.h")
get_target_property(COWL_ULIB_HEADERS ulib INTERFACE_SOURCES)
list(APPEND COWL_PUBLIC_HEADERS ${COWL_ULIB_HEADERS})

# Sources

file(GLOB COWL_SOURCES CONFIGURE_DEPENDS
     "${COWL_SRC_DIR}/*.c"
     "${COWL_PARSER_DIR}/*.c")

list(APPEND COWL_SOURCES ${COWL_USER_SOURCES})

###############
### Targets ###
###############

# Parsers

add_custom_target(cowl-parsers
                  COMMENT "Generate builtin parsers.")

if(COWL_PARSER_FUNCTIONAL)
    add_subdirectory("${COWL_FUNC_PARSER_DIR}")
    add_dependencies(cowl-parsers cowl-func-parser)
endif()

# Copy headers

add_custom_target(cowl-headers
                  COMMAND "${CMAKE_COMMAND}" -E remove_directory "${COWL_HEADERS_OUT_DIR}"
                  COMMAND "${CMAKE_COMMAND}" -E make_directory "${COWL_HEADERS_OUT_DIR}"
                  COMMAND ${CMAKE_COMMAND} -E copy
                          ${COWL_PUBLIC_HEADERS} "${COWL_HEADERS_OUT_DIR}"
                  COMMENT "Copy headers to the build directory.")

# Static library

add_library(cowl-static STATIC EXCLUDE_FROM_ALL ${COWL_SOURCES})
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
target_precompile_headers(cowl-static PUBLIC ${COWL_USER_HEADERS})
target_link_libraries(cowl-static PUBLIC ulib)
add_dependencies(cowl-static cowl-parsers cowl-headers)

if(COWL_LTO_ENABLED)
    set_property(TARGET cowl-static PROPERTY INTERPROCEDURAL_OPTIMIZATION ON)
endif()

# Shared library

add_library(cowl-shared SHARED EXCLUDE_FROM_ALL ${COWL_SOURCES})
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
target_precompile_headers(cowl-shared PUBLIC ${COWL_USER_HEADERS})
target_link_libraries(cowl-shared PUBLIC ulib)
add_dependencies(cowl-shared cowl-parsers cowl-headers)

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
