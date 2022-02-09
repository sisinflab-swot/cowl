#################
# Configuration #
#################

# CMake

cmake_minimum_required(VERSION 3.18)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake" "${CMAKE_MODULE_PATH}")

# Project

set(COWL_VERSION_MAJOR 0)
set(COWL_VERSION_MINOR 5)
set(COWL_VERSION_PATCH 2)
set(COWL_VERSION "${COWL_VERSION_MAJOR}.${COWL_VERSION_MINOR}.${COWL_VERSION_PATCH}")

set(COWL_VENDOR "SisInf Lab, Polytechnic University of Bari")
set(COWL_VENDOR_URL "http://swot.sisinflab.poliba.it")
set(COWL_COPYRIGHT_YEAR "2019-2022")
set(COWL_GIT_URL "https://github.com/sisinflab-swot/cowl")

project(Cowl
        VERSION "${COWL_VERSION}"
        DESCRIPTION "A lightweight C API for working with OWL ontologies."
        HOMEPAGE_URL "${COWL_VENDOR_URL}/cowl"
        LANGUAGES C)

# Options

option(COWL_EMBEDDED "Enable optimizations for embedded platforms" OFF)
option(COWL_LTO "Enable link-time optimization, if available" ON)
option(COWL_STATIC "Generate static library target." ON)
option(COWL_SHARED "Generate shared library target." ON)
option(COWL_OBJECT "Generate object library target." OFF)
set(COWL_PARSERS "functional" CACHE STRING "List of enabled built-in parsers (semicolon-separated")
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

if(NOT TARGET ulib-static)
    option(ULIB_EMBEDDED "" ${COWL_EMBEDDED})
    option(ULIB_LTO "" ${COWL_LTO})
    add_subdirectory("${COWL_LIB_DIR}/ulib" EXCLUDE_FROM_ALL)
endif()

# Header dirs

set(COWL_PUBLIC_HEADERS_DIRS "${COWL_PUBLIC_HEADERS_DIR}")

set(COWL_PRIVATE_HEADERS_DIRS
    "${COWL_PRIVATE_HEADERS_DIR}"
    "${COWL_SRC_DIR}"
    "${COWL_PARSER_DIR}")

# Header files

file(GLOB COWL_PUBLIC_HEADERS CONFIGURE_DEPENDS "${COWL_PUBLIC_HEADERS_DIR}/*.h")
get_target_property(COWL_ULIB_HEADERS ulib-static PUBLIC_HEADER)
list(APPEND COWL_PUBLIC_HEADERS ${COWL_ULIB_HEADERS})

# Sources

file(GLOB COWL_SOURCES CONFIGURE_DEPENDS
     "${COWL_SRC_DIR}/*.c"
     "${COWL_PARSER_DIR}/*.c")

list(APPEND COWL_SOURCES ${COWL_USER_SOURCES})

###############
### Targets ###
###############

# Main target

add_custom_target(cowl ALL COMMENT "Build Cowl")

# Parsers

add_custom_target(cowl-parsers COMMENT "Generate builtin parsers.")

foreach(PARSER IN LISTS COWL_PARSERS)
    string(TOUPPER "${PARSER}" PARSER_OPT)
    set(PARSER_OPT "COWL_PARSER_${PARSER_OPT}")
    string(TOLOWER "${PARSER}" PARSER)

    add_subdirectory("${COWL_PARSER_DIR}/${PARSER}")
    list(APPEND COWL_PARSER_DEFINES "${PARSER_OPT}")
endforeach()

list(APPEND COWL_PUBLIC_DEFINES ${COWL_PARSER_DEFINES})

# Copy headers

add_custom_target(cowl-headers
                  COMMAND "${CMAKE_COMMAND}" -E remove_directory "${COWL_HEADERS_OUT_DIR}"
                  COMMAND "${CMAKE_COMMAND}" -E make_directory "${COWL_HEADERS_OUT_DIR}"
                  COMMAND ${CMAKE_COMMAND} -E copy
                          ${COWL_PUBLIC_HEADERS} "${COWL_HEADERS_OUT_DIR}"
                  COMMENT "Copy headers to the build directory.")

# Libraries

function(cowl_library_target NAME TYPE)
    add_library(${NAME} ${TYPE} EXCLUDE_FROM_ALL ${COWL_SOURCES})
    set_target_properties(${NAME} PROPERTIES
                          OUTPUT_NAME "cowl"
                          PUBLIC_HEADER "${COWL_PUBLIC_HEADERS}"
                          C_VISIBILITY_PRESET hidden
                          VISIBILITY_INLINES_HIDDEN ON)
    target_compile_features(${NAME} PRIVATE ${COWL_COMPILE_FEATURES})
    target_compile_options(${NAME} PRIVATE ${COWL_WARNING_OPTIONS})
    target_compile_definitions(${NAME}
                               PUBLIC ${COWL_PUBLIC_DEFINES}
                               PRIVATE ${COWL_PRIVATE_DEFINES})
    target_include_directories(${NAME}
                               PUBLIC ${COWL_PUBLIC_HEADERS_DIRS}
                               PRIVATE ${COWL_PRIVATE_HEADERS_DIRS})
    target_precompile_headers(${NAME} PUBLIC ${COWL_USER_HEADERS})
    target_link_libraries(${NAME} PUBLIC ulib-static)
    add_dependencies(${NAME} cowl-parsers cowl-headers)

    if(COWL_LTO_ENABLED)
        set_property(TARGET ${NAME} PROPERTY INTERPROCEDURAL_OPTIMIZATION ON)
    endif()

    add_dependencies(cowl ${NAME})
endfunction()

if(COWL_STATIC)
    cowl_library_target(cowl-static STATIC)
endif()

if(COWL_SHARED)
    cowl_library_target(cowl-shared SHARED)
    target_compile_definitions(cowl-shared PUBLIC COWL_SHARED)
endif()

if(COWL_OBJECT)
    cowl_library_target(cowl-object OBJECT)
endif()

# Subprojects

add_subdirectory("${COWL_DOCS_DIR}")
add_subdirectory("${COWL_EXAMPLES_DIR}")
add_subdirectory("${COWL_TEST_DIR}")
