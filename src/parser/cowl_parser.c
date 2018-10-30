/// @author Ivano Bilenchi

#include "cowl_parser.h"
#include "cowl_functional_lexer.h"
#include "cowl_functional_parser.h"
#include "cowl_ontology_builder.h"
#include "cowl_string_private.h"

CowlOntology* cowl_parse_ontology(char const *path) {
    yyscan_t scanner;
    yylex_init(&scanner);

    CowlOntoBuilder *builder = cowl_onto_builder_alloc();

    FILE *yyin = fopen(path, "r");
    yyset_in(yyin, scanner);

    yyparse(scanner, builder);
    CowlOntology *ontology = cowl_onto_builder_build(builder);

    yylex_destroy(scanner);
    cowl_onto_builder_free(builder);

    return ontology;
}
