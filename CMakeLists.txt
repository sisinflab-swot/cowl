#################
# Configuration #
#################

# CMake

cmake_minimum_required(VERSION 3.24)

# Project

set(COWL_VERSION_MAJOR 0)
set(COWL_VERSION_MINOR 7)
set(COWL_VERSION_PATCH 2)
set(COWL_VERSION "${COWL_VERSION_MAJOR}.${COWL_VERSION_MINOR}.${COWL_VERSION_PATCH}")

set(COWL_VENDOR "SisInf Lab, Polytechnic University of Bari")
set(COWL_VENDOR_URL "http://swot.sisinflab.poliba.it")
set(COWL_COPYRIGHT_YEAR "2019-2025")
set(COWL_GIT_URL "https://github.com/sisinflab-swot/cowl")

project(Cowl
        VERSION "${COWL_VERSION}"
        DESCRIPTION "A lightweight C API for working with OWL ontologies."
        HOMEPAGE_URL "${COWL_VENDOR_URL}/cowl"
        LANGUAGES C)

# Cache variables

option(COWL_EMBEDDED "Enable optimizations for embedded platforms" OFF)
option(COWL_LTO "Enable link-time optimization, if available" ON)
option(COWL_CLANG_TIDY "Enable clang-tidy, if available" OFF)
option(COWL_ENTITY_IDS "Associate increasing unique identifiers to entities" OFF)
set(COWL_LIBRARY_TYPE "STATIC" CACHE STRING "Type of library to build.")
set(COWL_READERS "functional" CACHE STRING "List of enabled built-in readers (semicolon-separated)")
set(COWL_WRITERS "functional" CACHE STRING "List of enabled built-in writers (semicolon-separated)")

# Directories

set(COWL_PROJECT_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(COWL_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}")
set(COWL_LIB_DIR "${COWL_PROJECT_DIR}/lib")
set(COWL_SRC_DIR "${COWL_PROJECT_DIR}/src")
set(COWL_PUBLIC_HEADERS_DIR "${COWL_PROJECT_DIR}/include")
set(COWL_PRIVATE_HEADERS_DIR "${COWL_SRC_DIR}")
set(COWL_FORMATS_DIR "${COWL_SRC_DIR}/formats")

set(COWL_DATA_DIR "${COWL_PROJECT_DIR}/data")
set(COWL_DOCS_DIR "${COWL_PROJECT_DIR}/docs")
set(COWL_EXAMPLES_DIR "${COWL_PROJECT_DIR}/examples")
set(COWL_TEST_DIR "${COWL_PROJECT_DIR}/test")
set(COWL_TOOLS_DIR "${COWL_PROJECT_DIR}/tools")

set(COWL_ULIB_DIR "${COWL_LIB_DIR}/ulib")
set(COWL_ULIB_UTILS_DIR "${COWL_ULIB_DIR}/utils")

set(COWL_HEADERS_OUT_DIR "${COWL_OUTPUT_DIR}/include")

# CMake settings

list(APPEND CMAKE_MODULE_PATH "${COWL_ULIB_UTILS_DIR}/cmake")

# Target settings

set(COWL_COMPILE_FEATURES c_std_11)

if(COWL_ENTITY_IDS)
    list(APPEND COWL_PUBLIC_DEFINES COWL_ENTITY_IDS=1)
endif()

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

if(COWL_CLANG_TIDY)
    find_package(ClangTidy REQUIRED)
endif()

# uLib

option(ULIB_TINY "" ${COWL_EMBEDDED})
option(ULIB_LTO "" ${COWL_LTO})

if(NOT TARGET ulib)
    add_subdirectory("${COWL_ULIB_DIR}" EXCLUDE_FROM_ALL)
endif()

# Sources

set(COWL_PUBLIC_HEADERS_DIRS "${COWL_PUBLIC_HEADERS_DIR}")
set(COWL_PRIVATE_HEADERS_DIRS "${COWL_SRC_DIR}")

file(GLOB COWL_PUBLIC_HEADERS CONFIGURE_DEPENDS "${COWL_PUBLIC_HEADERS_DIR}/*.h")
file(GLOB COWL_PRIVATE_HEADERS CONFIGURE_DEPENDS "${COWL_PRIVATE_HEADERS_DIR}/*.h")
file(GLOB COWL_SOURCES CONFIGURE_DEPENDS "${COWL_SRC_DIR}/*.c")

###########
# Targets #
###########

# Readers

add_custom_target(cowl-readers COMMENT "Generate builtin readers.")

if(COWL_READERS)
    foreach(READER IN LISTS COWL_READERS)
        string(TOUPPER "${READER}" READER_OPT)
        set(READER_OPT "COWL_READER_${READER_OPT}")
        string(TOLOWER "${READER}" READER)

        add_subdirectory("${COWL_FORMATS_DIR}/${READER}/reader")
        list(APPEND COWL_READER_DEFINES "${READER_OPT}")
    endforeach()

    list(APPEND COWL_PUBLIC_DEFINES ${COWL_READER_DEFINES})

    list(GET COWL_READERS 0 COWL_DEFAULT_READER)
    if(DEFINED COWL_DEFAULT_READER)
        list(APPEND COWL_PUBLIC_DEFINES COWL_DEFAULT_READER=${COWL_DEFAULT_READER})
    endif()
endif()

# Writers

add_custom_target(cowl-writers COMMENT "Generate builtin writers.")

if(COWL_WRITERS)
    foreach(WRITER IN LISTS COWL_WRITERS)
        string(TOUPPER "${WRITER}" WRITER_OPT)
        set(WRITER_OPT "COWL_WRITER_${WRITER_OPT}")
        string(TOLOWER "${WRITER}" WRITER)

        add_subdirectory("${COWL_FORMATS_DIR}/${WRITER}/writer")
        list(APPEND COWL_WRITER_DEFINES "${WRITER_OPT}")
    endforeach()

    list(APPEND COWL_PUBLIC_DEFINES ${COWL_WRITER_DEFINES})

    list(GET COWL_WRITERS 0 COWL_DEFAULT_WRITER)
    if(DEFINED COWL_DEFAULT_WRITER)
        list(APPEND COWL_PUBLIC_DEFINES COWL_DEFAULT_WRITER=${COWL_DEFAULT_WRITER})
    endif()
endif()

# Library

add_library(cowl ${COWL_LIBRARY_TYPE})
target_sources(cowl
               PRIVATE ${COWL_SOURCES}
               PRIVATE FILE_SET private_headers
                       TYPE HEADERS
                       BASE_DIRS ${COWL_PRIVATE_HEADERS_DIRS}
                       FILES ${COWL_PRIVATE_HEADERS}
               PUBLIC FILE_SET public_headers
                      TYPE HEADERS
                      BASE_DIRS ${COWL_PUBLIC_HEADERS_DIRS}
                      FILES ${COWL_PUBLIC_HEADERS})
set_target_properties(cowl PROPERTIES
                      C_VISIBILITY_PRESET hidden
                      VISIBILITY_INLINES_HIDDEN ON)
target_compile_features(cowl PRIVATE ${COWL_COMPILE_FEATURES})
target_compile_options(cowl PRIVATE ${COWL_WARNING_OPTIONS})
target_compile_definitions(cowl
                           PUBLIC ${COWL_PUBLIC_DEFINES}
                           PRIVATE ${COWL_PRIVATE_DEFINES})
target_link_libraries(cowl PUBLIC ulib)
add_dependencies(cowl cowl-readers cowl-writers)

if(COWL_LIBRARY_TYPE STREQUAL "SHARED")
    target_compile_definitions(cowl PUBLIC COWL_SHARED)
endif()

if(COWL_LTO_ENABLED)
    set_property(TARGET cowl PROPERTY INTERPROCEDURAL_OPTIMIZATION ON)
endif()

if(COWL_CLANG_TIDY)
    clang_tidy_check(cowl)
endif()

install(TARGETS cowl ulib FILE_SET public_headers)

# Subprojects

add_subdirectory("${COWL_DOCS_DIR}")
add_subdirectory("${COWL_EXAMPLES_DIR}")
add_subdirectory("${COWL_TEST_DIR}")
add_subdirectory("${COWL_TOOLS_DIR}")
