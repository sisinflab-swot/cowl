/// @author Ivano Bilenchi

#include "cowl_parser.h"
#include "cowl_error_private.h"
#include "cowl_functional_lexer.h"
#include "cowl_functional_parser.h"
#include "cowl_iri_private.h"
#include "cowl_ontology_private.h"
#include "cowl_parser_private.h"
#include "cowl_string_private.h"

#include <errno.h>

UHASH_MAP_IMPL(CowlPrefixNsMap, CowlString*, CowlString*, cowl_string_hash, cowl_string_equals)

CowlParser* cowl_parser_alloc(void) {
    CowlParser init = {
        .prefix_ns_map = uhash_alloc(CowlPrefixNsMap),
        .ontology = cowl_ontology_get(),
        .errors = vector_alloc(CowlError)
    };
    struct CowlParser *parser = malloc(sizeof(*parser));
    memcpy(parser, &init, sizeof(*parser));
    return parser;
}

void cowl_parser_free(CowlParser *parser) {
    if (!parser) return;

    uhash_foreach(CowlPrefixNsMap, parser->prefix_ns_map, prefix, ns, {
        cowl_string_release(prefix);
        cowl_string_release(ns);
    });
    uhash_free(CowlPrefixNsMap, parser->prefix_ns_map);

    vector_foreach(CowlError, parser->errors, error, cowl_error_deinit(error));
    vector_free(CowlError, parser->errors);

    free((void *)parser);
}

CowlOntology* cowl_parser_parse_ontology(CowlParser *parser, char const *path) {
    yyscan_t scanner;
    yylex_init(&scanner);

    FILE *yyin = fopen(path, "r");

    if (!yyin) {
        cowl_parser_log_error(parser, CEC_ONTOLOGY_LOAD, strdup(strerror(errno)), 0);
        cowl_ontology_release(parser->ontology);
        ((struct CowlParser *)parser)->ontology = NULL;
        goto end;
    }

    yyset_in(yyin, scanner);
    yyparse(scanner, parser);

end:
    fclose(yyin);
    yylex_destroy(scanner);
    return parser->ontology;
}

cowl_uint_t cowl_parser_get_error_count(CowlParser *parser) {
    return vector_count(parser->errors);
}

Vector(CowlError) const* cowl_parser_get_errors(CowlParser *parser) {
    return parser->errors;
}

CowlError cowl_parser_get_last_error(CowlParser *parser) {
    return vector_last(parser->errors);
}

void cowl_parser_set_id(CowlParser *parser, CowlOntologyId *id) {
    cowl_ontology_set_id(parser->ontology, id);
}

void cowl_parser_add_axiom(CowlParser *parser, CowlAxiom *axiom) {
    if (axiom) cowl_ontology_add_axiom(parser->ontology, axiom);
}

void cowl_parser_register_ns(CowlParser *parser, CowlString *prefix, CowlString *ns) {
    if (uhmap_add(CowlPrefixNsMap, parser->prefix_ns_map, prefix, ns, NULL) == UHASH_INSERTED) {
        cowl_string_retain(prefix);
        cowl_string_retain(ns);
    }
}

CowlIRI* cowl_parser_get_full_iri(CowlParser *parser,
                                  char const *cstring, cowl_uint_t length) {
    CowlString *parts[2] = { NULL };
    cowl_string_split_two(cstring, length, ':', parts);

    CowlString *ns = uhmap_get(CowlPrefixNsMap, parser->prefix_ns_map, parts[0], NULL);
    CowlIRI *iri = ns ? cowl_iri_get(ns, parts[1]) : NULL;

    cowl_string_release(parts[0]);
    cowl_string_release(parts[1]);

    return iri;
}

void cowl_parser_log_error(CowlParser *parser, CowlErrorCode code,
                           char const *description, cowl_uint_t line) {
    CowlError error = cowl_error_init(code, description, line);
    vector_push(CowlError, parser->errors, error);
}
