/// @author Ivano Bilenchi

#include "cowl_parser.h"
#include "cowl_functional_lexer.h"
#include "cowl_functional_parser.h"
#include "cowl_string_private.h"

CowlOntology* cowl_parse_ontology(char const *path) {
    yyscan_t scanner;
    yylex_init(&scanner);

    FILE *yyin = fopen(path, "r");
    yyset_in(yyin, scanner);

    yyparse(scanner);
    yylex_destroy(scanner);
    return NULL;
}
