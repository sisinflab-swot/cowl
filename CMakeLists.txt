cmake_minimum_required(VERSION 3.0)
project(cowl C)

# Compiler flags

set(CMAKE_C_STANDARD 11)

if (MSVC)
    set(COWL_DEBUG_FLAGS /Zi /W4)
    set(COWL_RELEASE_FLAGS /O2 /GL /W4)
else ()
    set(COWL_DEBUG_FLAGS -g -Wall -Wextra)
    set(COWL_RELEASE_FLAGS -O3 -flto -Wall -Wextra)
endif ()

# Directories

set(COWL_PUBLIC_HEADERS_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
set(COWL_LIB_DIR ${CMAKE_CURRENT_LIST_DIR}/lib)
set(COWL_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/src)
set(COWL_TEST_DIR ${CMAKE_CURRENT_LIST_DIR}/test)

# Header dirs

set(COWL_HEADERS_DIRS
    ${COWL_PUBLIC_HEADERS_DIR}
    ${COWL_LIB_DIR}/klib
    ${COWL_LIB_DIR}/khash_utils/include
    ${COWL_LIB_DIR}/vector_t/include
    ${COWL_SRC_DIR}/model)

# Header files

set(COWL_LIB_HEADERS
    ${COWL_LIB_DIR}/klib/khash.h
    ${COWL_LIB_DIR}/khash_utils/include/khash_utils.h
    ${COWL_LIB_DIR}/vector_t/include/vector.h)

file(GLOB COWL_PUBLIC_HEADERS
     ${COWL_PUBLIC_HEADERS_DIR}/*.h)

set(COWL_ALL_PUBLIC_HEADERS ${COWL_LIB_HEADERS} ${COWL_PUBLIC_HEADERS})

# Sources

file(GLOB COWL_SOURCES ${COWL_SRC_DIR}/model/*.c)

# Targets

# Static library

add_library(cowl-static STATIC "${COWL_SOURCES}")
set_target_properties(cowl-static PROPERTIES PUBLIC_HEADER "${COWL_ALL_PUBLIC_HEADERS}")
set_target_properties(cowl-static PROPERTIES OUTPUT_NAME "cowl")
target_include_directories(cowl-static PUBLIC ${COWL_HEADERS_DIRS})
target_compile_options(cowl-static PUBLIC "$<$<CONFIG:DEBUG>:${COWL_DEBUG_FLAGS}>")
target_compile_options(cowl-static PUBLIC "$<$<CONFIG:RELEASE>:${COWL_RELEASE_FLAGS}>")

install(TARGETS cowl-static
        ARCHIVE DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/include)

# Test
add_executable(cowl-test "${COWL_TEST_DIR}/test.c")
add_dependencies(cowl-test cowl-static)
target_include_directories(cowl-test PUBLIC ${COWL_HEADERS_DIRS})
target_link_libraries(cowl-test $<TARGET_FILE:cowl-static>)
