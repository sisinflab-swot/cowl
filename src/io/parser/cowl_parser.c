/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_parser_private.h"
#include "cowl_alloc.h"
#include "cowl_annotation_vec.h"
#include "cowl_functional_lexer.h"
#include "cowl_functional_parser.h"
#include "cowl_iri_private.h"
#include "cowl_ontology_private.h"
#include "cowl_string_private.h"

UHASH_IMPL(CowlNodeIdMap, cowl_string_hash, cowl_string_equals)

static CowlParser* cowl_parser_alloc(void) {
    CowlParser *parser = cowl_alloc(parser);
    if (!parser) return NULL;

    *parser = (CowlParser) {
        .super = COWL_OBJECT_INIT,
        .prefix_ns_map = uhmap_alloc(CowlStringTable),
        .node_id_map = uhmap_alloc(CowlNodeIdMap),
        .ontology = cowl_ontology_get()
    };

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

    cowl_free(parser);
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
    parser->errors = errors;

    if (cowl_functional_lex_init(&parser->scanner)) return NULL;

    FILE *yyin = fopen(path, "r");
    bool error;

    if (yyin) {
        cowl_functional_set_in(yyin, parser->scanner);
        error = cowl_functional_parse(parser->scanner, parser) != 0;
    } else {
        cowl_parser_log_error(parser, COWL_ERR_IO, strdup(strerror(errno)));
        error = true;
    }

    fclose(yyin);
    cowl_functional_lex_destroy(parser->scanner);

    if (error) {
        cowl_ontology_release(parser->ontology);
        parser->ontology = NULL;
    }

    return parser->ontology;
}

void cowl_parser_set_imports_loader(CowlParser *parser, CowlImportsLoader loader) {
    parser->loader = loader;
}

void cowl_parser_set_id(CowlParser *parser, CowlOntologyID id) {
    cowl_ontology_set_id(parser->ontology, id);
}

cowl_ret_t cowl_parser_set_imports(CowlParser *parser, Vector(CowlOntologyPtr) *imports) {
    cowl_ret_t ret = cowl_ontology_set_imports(parser->ontology, imports);
    if (ret) cowl_parser_log_error_type(parser, ret);
    return ret;
}

cowl_ret_t cowl_parser_set_annotations(CowlParser *parser, Vector(CowlAnnotationPtr) *annot) {
    cowl_ret_t ret = cowl_ontology_set_annot(parser->ontology, annot);
    if (ret) cowl_parser_log_error_type(parser, ret);
    return ret;
}

cowl_ret_t cowl_parser_add_axiom(CowlParser *parser, CowlAxiom *axiom) {
    if (!axiom) {
        cowl_parser_log_error_type(parser, COWL_ERR_MEM);
        return COWL_ERR_MEM;
    }

    cowl_ret_t ret = cowl_ontology_add_axiom(parser->ontology, axiom);

    if (ret) {
        cowl_parser_log_error_type(parser, ret);
        return ret;
    }

    return COWL_OK;
}

cowl_ret_t cowl_parser_register_ns(CowlParser *parser, CowlString *prefix, CowlString *ns) {
    uhash_ret_t ret = uhmap_add(CowlStringTable, parser->prefix_ns_map, prefix, ns, NULL);

    if (ret == UHASH_ERR) {
        cowl_parser_log_error_type(parser, COWL_ERR_MEM);
        return COWL_ERR_MEM;
    }

    if (ret == UHASH_INSERTED) {
        cowl_string_retain(prefix);
        cowl_string_retain(ns);
    }

    return COWL_OK;
}

cowl_ret_t cowl_parser_load_import(CowlParser *parser, CowlIRI *iri, CowlOntology **import) {
    *import = NULL;

    if (!iri) {
        cowl_parser_log_error_type(parser, COWL_ERR_MEM);
        return COWL_ERR_MEM;
    }

    CowlImportsLoader loader = parser->loader;
    if (!loader.load_ontology) return COWL_OK;

    cowl_uint_t n_errors = vector_count(parser->errors);
    *import = loader.load_ontology(loader.ctx, iri, parser->errors);

    if (parser->errors && vector_count(parser->errors) > n_errors) {
        // Errors occurred while parsing the imported ontology.
        cowl_ret_t ret = vector_last(parser->errors).code;
        cowl_parser_log_error_type(parser, ret);
        return ret;
    }

    return COWL_OK;
}

CowlIRI* cowl_parser_get_full_iri(CowlParser *parser, CowlRawString string) {
    cowl_uint_t ns_length = cowl_raw_string_index_of(string, ':') + 1;

    // We might use 'cowl_string_split_two' to obtain a prefix/suffix split, though
    // this involves two allocations: one for the prefix, and one for the suffix.
    // Since we only need the prefix for a hash table lookup, we can avoid its allocation
    // on the heap and keep it on the stack instead.
    CowlRawString raw_ns = cowl_raw_string_init(string.cstring, ns_length, false);
    CowlString ns_str = cowl_string_init(raw_ns);

    // If the remainder is empty, another slight optimization involves
    // using a shared empty string instance.
    CowlString *rem;

    if (ns_length < string.length) {
        rem = cowl_string_get(string.cstring + ns_length, string.length - ns_length, true);
    } else {
        rem = cowl_string_get_empty();
    }

    if (!rem) return NULL;

    CowlString *ns = uhmap_get(CowlStringTable, parser->prefix_ns_map, &ns_str, NULL);
    CowlIRI *iri = NULL;

    if (ns) {
        iri = cowl_iri_get(ns, rem);
    } else {
        // We couldn't find a namespace mapping for the specified short namespace.
        iri = NULL;
        CowlRawString comp[] = {
            cowl_raw_string_init_static("no namespace mapping for ", false),
            raw_ns
        };
        CowlRawString err_str = cowl_raw_string_concat(2, comp);
        cowl_parser_log_error(parser, COWL_ERR_SYNTAX, err_str.cstring);
        cowl_raw_string_deinit(err_str);
    }

    cowl_string_release(rem);
    return iri;
}

CowlNodeID cowl_parser_get_node_id(CowlParser *parser, CowlRawString id) {
    uhash_uint_t idx;
    CowlString id_str = cowl_string_init(id);
    uhash_ret_t ret = uhash_put(CowlNodeIdMap, parser->node_id_map, &id_str, &idx);

    CowlNodeID node_id = COWL_NODE_ID_NULL;

    if (ret == UHASH_INSERTED) {
        CowlString *string = cowl_string_copy(&id_str);

        if (string) {
            node_id = cowl_node_id_get_unique();
            uhash_key(parser->node_id_map, idx) = string;
            uhash_value(parser->node_id_map, idx) = node_id;
        } else {
            uhash_delete(CowlNodeIdMap, parser->node_id_map, idx);
        }
    } else if (ret == UHASH_PRESENT) {
        node_id = uhash_value(parser->node_id_map, idx);
    }

    return node_id;
}

static inline cowl_uint_t cowl_parser_get_line(CowlParser *parser) {
    if (!(parser->scanner && cowl_functional_get_lloc(parser->scanner))) return 0;
    return (cowl_uint_t)cowl_functional_get_lloc(parser->scanner)->last_line;
}

void cowl_parser_log_error(CowlParser *parser, cowl_ret_t code, char const *description) {
    if (!parser->errors) return;
    CowlError error = cowl_error_init_cstring(code, description, cowl_parser_get_line(parser));
    vector_push(CowlError, parser->errors, error);
}

void cowl_parser_log_error_type(CowlParser *parser, cowl_ret_t code) {
    cowl_parser_log_error(parser, code, cowl_ret_t_to_cstring(code));
}
