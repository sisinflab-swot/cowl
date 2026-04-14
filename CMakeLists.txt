# CMake

cmake_minimum_required(VERSION 3.24)

# Project

set(COWL_VERSION_MAJOR 0)
set(COWL_VERSION_MINOR 7)
set(COWL_VERSION_PATCH 4)
set(COWL_VERSION "${COWL_VERSION_MAJOR}.${COWL_VERSION_MINOR}.${COWL_VERSION_PATCH}")

set(COWL_VENDOR "SisInf Lab, Polytechnic University of Bari")
set(COWL_VENDOR_URL "http://swot.sisinflab.poliba.it")
set(COWL_COPYRIGHT_YEAR "2019-2026")
set(COWL_GIT_URL "https://github.com/sisinflab-swot/cowl")

project(
    Cowl
    VERSION "${COWL_VERSION}"
    DESCRIPTION "A lightweight C library for working with OWL ontologies."
    HOMEPAGE_URL "${COWL_VENDOR_URL}/cowl"
    LANGUAGES C
)

# Cache variables

option(COWL_DOCS "Enable the documentation targets" OFF)
option(COWL_TESTS "Enable the test targets" ${PROJECT_IS_TOP_LEVEL})
option(COWL_CPP_TESTS "Enable the C++ test targets" ${PROJECT_IS_TOP_LEVEL})
option(COWL_BENCHMARKS "Enable the benchmark targets" ${PROJECT_IS_TOP_LEVEL})
option(COWL_EXAMPLES "Enable the example targets" ${PROJECT_IS_TOP_LEVEL})
option(COWL_TOOLS "Enable the tool targets" ${PROJECT_IS_TOP_LEVEL})
option(COWL_EMBEDDED "Enable optimizations for embedded platforms" OFF)
option(COWL_LTO "Enable link-time optimization, if available" ON)
option(COWL_CLANG_TIDY "Enable clang-tidy, if available" OFF)
option(COWL_ENTITY_IDS "Associate increasing unique identifiers to entities" OFF)
set(COWL_LIBRARY_TYPE "STATIC" CACHE STRING "Type of library to build.")
set(COWL_READERS "all" CACHE STRING "List of enabled built-in readers (semicolon-separated)")
set(COWL_WRITERS "all" CACHE STRING "List of enabled built-in writers (semicolon-separated)")
set(COWL_DEFAULT_READER "" CACHE STRING "Default reader.")
set(COWL_DEFAULT_WRITER "" CACHE STRING "Default writer.")

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
set(COWL_BENCH_DIR "${COWL_PROJECT_DIR}/bench")
set(COWL_EXAMPLES_DIR "${COWL_PROJECT_DIR}/examples")
set(COWL_TEST_DIR "${COWL_PROJECT_DIR}/test")
set(COWL_TOOLS_DIR "${COWL_PROJECT_DIR}/tools")

set(COWL_ULIB_DIR "${COWL_LIB_DIR}/ulib")
set(COWL_ULIB_UTILS_DIR "${COWL_ULIB_DIR}/utils")

# CMake settings

list(APPEND CMAKE_MODULE_PATH "${COWL_ULIB_UTILS_DIR}/cmake")

# Target settings

set(COWL_COMPILE_FEATURES c_std_11)

if(COWL_ENTITY_IDS)
    list(APPEND COWL_PUBLIC_DEFINES COWL_ENTITY_IDS=1)
endif()

list(
    APPEND COWL_PRIVATE_DEFINES
    COWL_BUILDING
    COWL_VERSION_MAJOR=${COWL_VERSION_MAJOR}
    COWL_VERSION_MINOR=${COWL_VERSION_MINOR}
    COWL_VERSION_PATCH=${COWL_VERSION_PATCH}
)

if(MSVC)
    set(COWL_WARNING_OPTIONS /W3 /wd4996)
else()
    set(COWL_WARNING_OPTIONS -Wall -Wextra -Wpedantic)
endif()

if(COWL_LTO)
    include(CheckIPOSupported)
    check_ipo_supported(RESULT COWL_LTO_ENABLED)
else()
    set(COWL_LTO_ENABLED OFF)
endif()

if(COWL_CLANG_TIDY)
    find_package(ClangTidy REQUIRED)
endif()

# uLib

option(ULIB_TINY "" ${COWL_EMBEDDED})
option(ULIB_LTO "" ${COWL_LTO})
option(ULIB_DOCS "" ${COWL_DOCS})

if(NOT TARGET ulib)
    add_subdirectory("${COWL_ULIB_DIR}" EXCLUDE_FROM_ALL)
endif()

# Sources

set(COWL_PUBLIC_HEADERS_DIRS "${COWL_PUBLIC_HEADERS_DIR}")
set(COWL_PRIVATE_HEADERS_DIRS "${COWL_PRIVATE_HEADERS_DIR}")

file(GLOB COWL_PUBLIC_HEADERS CONFIGURE_DEPENDS "${COWL_PUBLIC_HEADERS_DIR}/*.h")
file(GLOB COWL_PRIVATE_HEADERS CONFIGURE_DEPENDS "${COWL_PRIVATE_HEADERS_DIR}/*.h")
file(GLOB COWL_SOURCES CONFIGURE_DEPENDS "${COWL_SRC_DIR}/*.c")

# Readers

add_custom_target(cowl-readers COMMENT "Generate builtin readers.")

if(COWL_READERS STREQUAL "all")
    file(GLOB COWL_READERS "${COWL_FORMATS_DIR}/*/reader")
    list(TRANSFORM COWL_READERS REPLACE "^${COWL_FORMATS_DIR}/" "")
    list(TRANSFORM COWL_READERS REPLACE "/reader$" "")
endif()

if(COWL_READERS)
    foreach(reader IN LISTS COWL_READERS)
        string(TOUPPER "${reader}" reader_opt)
        set(reader_opt "COWL_READER_${reader_opt}")
        string(TOLOWER "${reader}" reader)
        add_subdirectory("${COWL_FORMATS_DIR}/${reader}/reader")
        list(APPEND COWL_READER_DEFINES "${reader_opt}")
    endforeach()
    list(APPEND COWL_PUBLIC_DEFINES ${COWL_READER_DEFINES})
endif()

if(COWL_DEFAULT_READER AND COWL_DEFAULT_READER IN_LIST COWL_READERS)
    list(APPEND COWL_PUBLIC_DEFINES COWL_DEFAULT_READER=${COWL_DEFAULT_READER})
endif()

# Writers

add_custom_target(cowl-writers COMMENT "Generate builtin writers.")

if(COWL_WRITERS STREQUAL "all")
    file(GLOB COWL_WRITERS "${COWL_FORMATS_DIR}/*/writer")
    list(TRANSFORM COWL_WRITERS REPLACE "^${COWL_FORMATS_DIR}/" "")
    list(TRANSFORM COWL_WRITERS REPLACE "/writer$" "")
endif()

if(COWL_WRITERS)
    foreach(writer IN LISTS COWL_WRITERS)
        string(TOUPPER "${writer}" writer_opt)
        set(writer_opt "COWL_WRITER_${writer_opt}")
        string(TOLOWER "${writer}" writer)
        add_subdirectory("${COWL_FORMATS_DIR}/${writer}/writer")
        list(APPEND COWL_WRITER_DEFINES "${writer_opt}")
    endforeach()
    list(APPEND COWL_PUBLIC_DEFINES ${COWL_WRITER_DEFINES})
endif()

if(COWL_DEFAULT_WRITER AND COWL_DEFAULT_WRITER IN_LIST COWL_WRITERS)
    list(APPEND COWL_PUBLIC_DEFINES COWL_DEFAULT_WRITER=${COWL_DEFAULT_WRITER})
endif()

# Library

add_library(cowl ${COWL_LIBRARY_TYPE})
target_sources(
    cowl
    PRIVATE ${COWL_SOURCES}
    PRIVATE FILE_SET private_headers
            TYPE HEADERS
            BASE_DIRS ${COWL_PRIVATE_HEADERS_DIRS}
            FILES ${COWL_PRIVATE_HEADERS}
    PUBLIC FILE_SET public_headers
            TYPE HEADERS
            BASE_DIRS ${COWL_PUBLIC_HEADERS_DIRS}
            FILES ${COWL_PUBLIC_HEADERS}
)
set_target_properties(
    cowl PROPERTIES
    C_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN ON
    INTERPROCEDURAL_OPTIMIZATION ${COWL_LTO_ENABLED}
)
target_compile_features(cowl PRIVATE ${COWL_COMPILE_FEATURES})
target_compile_options(cowl PRIVATE ${COWL_WARNING_OPTIONS})
target_compile_definitions(
    cowl
    PUBLIC ${COWL_PUBLIC_DEFINES}
    PRIVATE ${COWL_PRIVATE_DEFINES}
)
target_link_libraries(cowl PUBLIC ulib)
add_dependencies(cowl cowl-readers cowl-writers)

if(COWL_LIBRARY_TYPE STREQUAL "SHARED")
    target_compile_definitions(cowl PUBLIC COWL_SHARED)
endif()

if(COWL_CLANG_TIDY)
    clang_tidy_check(cowl)
endif()

install(TARGETS cowl ulib FILE_SET public_headers)

# Subprojects

if(COWL_DOCS)
    add_subdirectory("${COWL_DOCS_DIR}")
endif()

if(COWL_TESTS)
    enable_testing()
    add_subdirectory("${COWL_TEST_DIR}")
endif()

if(COWL_BENCHMARKS)
    add_subdirectory("${COWL_BENCH_DIR}")
endif()

if(COWL_EXAMPLES)
    add_subdirectory("${COWL_EXAMPLES_DIR}")
endif()

if(COWL_TOOLS)
    add_subdirectory("${COWL_TOOLS_DIR}")
endif()
