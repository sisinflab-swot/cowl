# Packages

find_package(BISON 3.0 REQUIRED)
find_package(FLEX 2.6.4 REQUIRED)

# Directories

set(COWL_READER_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(COWL_READER_OUT_DIR "${CMAKE_CURRENT_BINARY_DIR}")

# Target settings

if(MSVC)
    list(APPEND COWL_FUNC_FLEX_FLAGS --wincompat)
endif()

if(NOT COWL_EMBEDDED)
    list(APPEND COWL_FUNC_FLEX_FLAGS -Cfe)
endif()

list(JOIN COWL_FUNC_FLEX_FLAGS " " COWL_FUNC_FLEX_FLAGS)

# Sources

file(GLOB COWL_FUNC_READER_SOURCES CONFIGURE_DEPENDS "${COWL_READER_SRC_DIR}/*.c")

set(COWL_FUNC_LEXER_IN "${COWL_READER_SRC_DIR}/cowl_functional.l")
set(COWL_FUNC_LEXER_HEADER "${COWL_READER_OUT_DIR}/cowl_func_yylexer.h")
set(COWL_FUNC_LEXER_OUT "${COWL_READER_OUT_DIR}/cowl_func_yylexer.c")

set(COWL_FUNC_PARSER_IN "${COWL_READER_SRC_DIR}/cowl_functional.y")
set(COWL_FUNC_PARSER_HEADER "${COWL_READER_OUT_DIR}/cowl_func_yyparser.h")
set(COWL_FUNC_PARSER_OUT "${COWL_READER_OUT_DIR}/cowl_func_yyparser.c")

###############
### Targets ###
###############

# Flex & Bison

bison_target(COWL_FUNC_PARSER "${COWL_FUNC_PARSER_IN}" "${COWL_FUNC_PARSER_OUT}"
             DEFINES_FILE "${COWL_FUNC_PARSER_HEADER}")
flex_target(COWL_FUNC_LEXER "${COWL_FUNC_LEXER_IN}" "${COWL_FUNC_LEXER_OUT}"
            COMPILE_FLAGS "${COWL_FUNC_FLEX_FLAGS}"
            DEFINES_FILE "${COWL_FUNC_LEXER_HEADER}")
add_flex_bison_dependency(COWL_FUNC_LEXER COWL_FUNC_PARSER)

set(COWL_FUNC_READER_GENERATED_SOURCES
    ${BISON_COWL_FUNC_PARSER_OUTPUTS}
    ${FLEX_COWL_FUNC_LEXER_OUTPUTS})
list(APPEND COWL_FUNC_READER_SOURCES ${COWL_FUNC_READER_GENERATED_SOURCES})

add_custom_target(cowl-functional-reader
                  DEPENDS ${COWL_FUNC_READER_GENERATED_SOURCES}
                  COMMENT "Generate the functional syntax reader.")
add_dependencies(cowl-readers cowl-functional-reader)

# Propagate changes in the parent project

list(APPEND COWL_PRIVATE_HEADERS_DIRS "${COWL_READER_OUT_DIR}")
list(APPEND COWL_SOURCES ${COWL_FUNC_READER_SOURCES})

set(COWL_PRIVATE_HEADERS_DIRS ${COWL_PRIVATE_HEADERS_DIRS} PARENT_SCOPE)
set(COWL_SOURCES ${COWL_SOURCES} PARENT_SCOPE)

set_source_files_properties(${COWL_FUNC_READER_SOURCES}
                            DIRECTORY "${COWL_PROJECT_DIR}"
                            PROPERTIES SKIP_LINTING ON)
set_source_files_properties(${COWL_FUNC_READER_GENERATED_SOURCES}
                            DIRECTORY "${COWL_PROJECT_DIR}"
                            PROPERTIES GENERATED ON)
