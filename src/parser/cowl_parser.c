/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_parser_private.h"
#include "cowl_annotation_vec.h"
#include "cowl_functional_lexer.h"
#include "cowl_functional_parser.h"
#include "cowl_iri_private.h"
#include "cowl_ontology_private.h"
#include "cowl_string_private.h"

UHASH_IMPL(CowlNodeIdMap, cowl_string_hash, cowl_string_equals)

static CowlParser* cowl_parser_alloc(void) {
    CowlParser init = {
        .super = COWL_OBJECT_INIT,
        .prefix_ns_map = uhmap_alloc(CowlStringTable),
        .node_id_map = uhmap_alloc(CowlNodeIdMap),
        .ontology = cowl_ontology_get(),
        .errors = NULL
    };
    cowl_struct(CowlParser) *parser = malloc(sizeof(*parser));
    memcpy(parser, &init, sizeof(*parser));
    return parser;
}

static void cowl_parser_free(CowlParser *parser) {
    if (!parser) return;

    uhash_foreach(CowlStringTable, parser->prefix_ns_map, prefix, ns, {
        cowl_string_release(prefix);
        cowl_string_release(ns);
    });
    uhash_free(CowlStringTable, parser->prefix_ns_map);

    uhash_foreach_key(CowlNodeIdMap, parser->node_id_map, id, cowl_string_release(id));
    uhash_free(CowlNodeIdMap, parser->node_id_map);
    if (parser->loader.free) parser->loader.free(parser->loader.ctx);

    free((void *)parser);
}

CowlParser* cowl_parser_get(void) {
    return cowl_parser_alloc();
}

CowlParser* cowl_parser_retain(CowlParser *parser) {
    return cowl_object_retain(parser);
}

void cowl_parser_release(CowlParser *parser) {
    if (parser && !cowl_object_release(parser)) {
        cowl_parser_free(parser);
    }
}

CowlOntology* cowl_parser_parse_ontology(CowlParser *parser, char const *path,
                                         Vector(CowlError) *errors) {
    ((cowl_struct(CowlParser)*)parser)->errors = errors;

    yyscan_t scanner;
    cowl_functional_lex_init(&scanner);

    FILE *yyin = fopen(path, "r");
    bool error;

    if (!yyin) {
        cowl_parser_log_error(parser, COWL_ERR_ONTOLOGY_LOAD, strdup(strerror(errno)), 0);
        error = true;
        goto end;
    }

    cowl_functional_set_in(yyin, scanner);
    error = cowl_functional_parse(scanner, parser) != 0;

end:
    fclose(yyin);
    cowl_functional_lex_destroy(scanner);

    if (error) {
        cowl_ontology_release(parser->ontology);
        ((cowl_struct(CowlParser) *)parser)->ontology = NULL;
    }

    return parser->ontology;
}

void cowl_parser_set_imports_loader(CowlParser *parser, CowlImportsLoader loader) {
    ((cowl_struct(CowlParser) *)parser)->loader = loader;
}

void cowl_parser_set_id(CowlParser *parser, CowlOntologyID *id) {
    cowl_ontology_set_id(parser->ontology, id);
}

void cowl_parser_set_imports(CowlParser *parser, Vector(CowlOntologyPtr) *imports) {
    cowl_ontology_set_imports(parser->ontology, imports);
}

void cowl_parser_set_annotations(CowlParser *parser, Vector(CowlAnnotationPtr) *annot) {
    cowl_ontology_set_annot(parser->ontology, annot);
}

void cowl_parser_add_axiom(CowlParser *parser, CowlAxiom *axiom) {
    if (axiom) cowl_ontology_add_axiom(parser->ontology, axiom);
}

void cowl_parser_register_ns(CowlParser *parser, CowlString *prefix, CowlString *ns) {
    if (uhmap_add(CowlStringTable, parser->prefix_ns_map, prefix, ns, NULL) == UHASH_INSERTED) {
        cowl_string_retain(prefix);
        cowl_string_retain(ns);
    }
}

CowlOntology* cowl_parser_load_import(CowlParser *parser, CowlIRI *iri) {
    CowlImportsLoader loader = parser->loader;
    return loader.load_ontology ? loader.load_ontology(loader.ctx, iri, parser->errors) : NULL;
}

CowlIRI* cowl_parser_get_full_iri(CowlParser *parser,
                                  char const *cstring, cowl_uint_t length) {
    CowlString *parts[2] = { NULL };
    cowl_string_split_two(cstring, length, ':', parts);

    CowlString *ns = uhmap_get(CowlStringTable, parser->prefix_ns_map, parts[0], NULL);
    CowlIRI *iri = ns ? cowl_iri_get(ns, parts[1]) : NULL;

    cowl_string_release(parts[0]);
    cowl_string_release(parts[1]);

    return iri;
}

CowlNodeID cowl_parser_get_node_id(CowlParser *parser, CowlString *id) {
    uhash_ret_t ret;
    uhash_uint_t idx = uhash_put(CowlNodeIdMap, parser->node_id_map, id, &ret);
    CowlNodeID node_id;

    if (ret == UHASH_INSERTED) {
        node_id = cowl_node_id_get_unique();
        cowl_string_retain(id);
        uhash_value(parser->node_id_map, idx) = node_id;
    } else {
        node_id = uhash_value(parser->node_id_map, idx);
    }

    return node_id;
}

void cowl_parser_log_error(CowlParser *parser, CowlErrorCode code,
                           char const *description, cowl_uint_t line) {
    if (!parser->errors) return;
    CowlError error = cowl_error_init_cstring(code, description, line);
    vector_push(CowlError, parser->errors, error);
}
