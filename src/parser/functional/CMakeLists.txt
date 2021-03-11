# Packages

find_package(BISON 3.0 REQUIRED)
find_package(FLEX 2.6.4 REQUIRED)

# Directories

set(COWL_FUNC_PARSER_OUT_DIR "${COWL_OUTPUT_DIR}/functional")
file(MAKE_DIRECTORY "${COWL_FUNC_PARSER_OUT_DIR}")

# Target settings

list(APPEND COWL_PUBLIC_DEFINES COWL_PARSER_FUNCTIONAL)

if(MSVC)
    list(APPEND COWL_FUNC_FLEX_FLAGS --wincompat)
endif()

if(NOT COWL_EMBEDDED)
    list(APPEND COWL_FUNC_FLEX_FLAGS -Cfe)
endif()

list(JOIN COWL_FUNC_FLEX_FLAGS " " COWL_FUNC_FLEX_FLAGS)

# Header dirs

list(APPEND COWL_PRIVATE_HEADERS_DIRS
     "${COWL_FUNC_PARSER_DIR}"
     "${COWL_FUNC_PARSER_OUT_DIR}")

# Sources

file(GLOB COWL_FUNC_PARSER_SOURCES CONFIGURE_DEPENDS
     "${COWL_FUNC_PARSER_DIR}/*.c")
list(APPEND COWL_SOURCES ${COWL_FUNC_PARSER_SOURCES})

set(COWL_FUNC_LEXER_IN "${COWL_FUNC_PARSER_DIR}/cowl_functional.l")
set(COWL_FUNC_LEXER_HEADER "${COWL_FUNC_PARSER_OUT_DIR}/cowl_func_yylexer.h")
set(COWL_FUNC_LEXER_OUT "${COWL_FUNC_PARSER_OUT_DIR}/cowl_func_yylexer.c")

set(COWL_FUNC_PARSER_IN "${COWL_FUNC_PARSER_DIR}/cowl_functional.y")
set(COWL_FUNC_PARSER_HEADER "${COWL_FUNC_PARSER_OUT_DIR}/cowl_func_yyparser.h")
set(COWL_FUNC_PARSER_OUT "${COWL_FUNC_PARSER_OUT_DIR}/cowl_func_yyparser.c")

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

add_custom_target(cowl-func-parser
                  DEPENDS
                  ${FLEX_COWL_FUNC_LEXER_OUTPUTS}
                  ${BISON_COWL_FUNC_PARSER_OUTPUT_SOURCE}
                  COMMENT "Generate the functional syntax parser.")

# Propagate changes in the parent project

list(APPEND COWL_SOURCES
     ${FLEX_COWL_FUNC_LEXER_OUTPUTS}
     ${BISON_COWL_FUNC_PARSER_OUTPUT_SOURCE})

set(COWL_PUBLIC_DEFINES ${COWL_PUBLIC_DEFINES} PARENT_SCOPE)
set(COWL_PRIVATE_HEADERS_DIRS ${COWL_PRIVATE_HEADERS_DIRS} PARENT_SCOPE)
set(COWL_SOURCES ${COWL_SOURCES} PARENT_SCOPE)

set_source_files_properties(${FLEX_COWL_FUNC_LEXER_OUTPUTS}
                            ${BISON_COWL_FUNC_PARSER_OUTPUT_SOURCE}
                            DIRECTORY "${COWL_PROJECT_DIR}"
                            PROPERTIES GENERATED ON)
