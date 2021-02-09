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
#include "cowl_anon_ind.h"
#include "cowl_config_private.h"
#include "cowl_functional_lexer.h"
#include "cowl_input_stream.h"
#include "cowl_iri_private.h"
#include "cowl_macros.h"
#include "cowl_object_table_private.h"
#include "cowl_ontology_private.h"
#include "cowl_string_private.h"

static CowlParser* cowl_parser_alloc(void) {
    CowlParser *parser = cowl_alloc(parser);
    if (!parser) return NULL;

    *parser = (CowlParser) {
        .super = COWL_OBJECT_INIT(COWL_OT_PARSER),
        .prefix_ns_map = cowl_string_map_alloc(),
        .anon_ind_map = cowl_string_map_alloc()
    };

    return parser;
}

static void cowl_parser_free(CowlParser *parser) {
    if (!parser) return;

    uhash_foreach(CowlObjectTable, parser->prefix_ns_map, prefix, ns, {
        cowl_string_release(prefix);
        cowl_string_release(ns);
    });
    uhash_free(CowlObjectTable, parser->prefix_ns_map);

    uhash_foreach(CowlObjectTable, parser->anon_ind_map, id, ind, {
        cowl_string_release(id);
        cowl_anon_ind_release(ind);
    });
    uhash_free(CowlObjectTable, parser->anon_ind_map);

    if (parser->loader.free) parser->loader.free(parser->loader.ctx);
    if (parser->handler.free) parser->handler.free(parser->handler.ctx);

    cowl_free(parser);
}

CowlParser* cowl_parser_get(void) {
    return cowl_parser_alloc();
}

CowlParser* cowl_parser_retain(CowlParser *parser) {
    return cowl_object_incr_ref(parser);
}

void cowl_parser_release(CowlParser *parser) {
    if (parser && !cowl_object_decr_ref(parser)) {
        cowl_parser_free(parser);
    }
}

static CowlOntology* cowl_parser_parse(CowlParser *parser) {
    if (!parser->stream) return NULL;

    if (cowl_functional_lex_init(&parser->scanner)) {
        cowl_parser_handle_error_type(parser, COWL_ERR_MEM);
        return NULL;
    }

    parser->ontology = cowl_ontology_get();

    if (!parser->ontology) {
        cowl_parser_handle_error_type(parser, COWL_ERR_MEM);
        return NULL;
    }

    cowl_functional_set_in(NULL, parser->scanner);
    cowl_functional_set_extra(parser->stream, parser->scanner);
    cowl_ret ret = cowl_functional_parse(parser->scanner, parser) == 0 ? COWL_OK : COWL_ERR;
    cowl_functional_lex_destroy(parser->scanner);

    if (ret) {
        cowl_ontology_release(parser->ontology);
        parser->ontology = NULL;
    }

    return parser->ontology;
}

static CowlOntology* cowl_parser_parse_deinit(CowlParser *parser) {
    cowl_parser_parse(parser);
    cowl_ret ret = cowl_input_stream_deinit(parser->stream);
    if (ret) cowl_parser_handle_error_type(parser, ret);
    parser->stream = NULL;
    return parser->ontology;
}

CowlOntology* cowl_parser_parse_path(CowlParser *parser, char const *path) {
    CowlInputStream stream;
    parser->stream = &stream;

    cowl_ret ret;

    if ((ret = cowl_input_stream_from_path(parser->stream, path))) {
        cowl_parser_handle_error_type(parser, ret);
        parser->stream = NULL;
        return NULL;
    }

    return cowl_parser_parse_deinit(parser);
}

CowlOntology* cowl_parser_parse_file(CowlParser *parser, FILE *file) {
    CowlInputStream stream;
    parser->stream = &stream;

    cowl_ret ret;

    if ((ret = cowl_input_stream_from_file(parser->stream, file))) {
        cowl_parser_handle_error_type(parser, ret);
        parser->stream = NULL;
        return NULL;
    }

    return cowl_parser_parse_deinit(parser);
}

CowlOntology* cowl_parser_parse_cstring(CowlParser *parser, char const *cstring, size_t length) {
    CowlInputStream stream;
    parser->stream = &stream;

    cowl_ret ret;

    if ((ret = cowl_input_stream_from_cstring(parser->stream, cstring, length))) {
        cowl_parser_handle_error_type(parser, ret);
        parser->stream = NULL;
        return NULL;
    }

    return cowl_parser_parse_deinit(parser);
}

CowlOntology* cowl_parser_parse_stream(CowlParser *parser, CowlInputStream const *stream) {
    parser->stream = (CowlInputStream *)stream;
    CowlOntology *onto = cowl_parser_parse(parser);
    parser->stream = NULL;
    return onto;
}

void cowl_parser_set_import_loader(CowlParser *parser, CowlImportLoader loader) {
    parser->loader = loader;
}

void cowl_parser_set_error_handler(CowlParser *parser, CowlErrorHandler handler) {
    parser->handler = handler;
}

void cowl_parser_set_iri(CowlParser *parser, CowlIRI *iri) {
    cowl_ontology_set_iri(parser->ontology, iri);
}

void cowl_parser_set_version(CowlParser *parser, CowlIRI *version) {
    cowl_ontology_set_version(parser->ontology, version);
}

cowl_ret cowl_parser_add_import(CowlParser *parser, CowlIRI *iri) {
    CowlOntology *import = NULL;
    cowl_ret ret;

    if (!iri) {
        ret = COWL_ERR_MEM;
        goto err;
    }

    CowlImportLoader loader = parser->loader;
    if (!loader.load_ontology) loader = cowl_api_get_import_loader();
    if (!loader.load_ontology) return COWL_OK;

    import = loader.load_ontology(loader.ctx, iri);

    if (!import) {
        ret = COWL_ERR_IMPORT;
        goto err;
    }

    ret = cowl_ontology_add_import(parser->ontology, import);
    cowl_ontology_release(import);

err:
    if (ret) cowl_parser_handle_error_type(parser, ret);
    return ret;
}

cowl_ret cowl_parser_add_annot(CowlParser *parser, CowlAnnotation *annot) {
    cowl_ret ret = cowl_ontology_add_annot(parser->ontology, annot);
    if (ret) cowl_parser_handle_error_type(parser, ret);
    return ret;
}

cowl_ret cowl_parser_add_axiom(CowlParser *parser, CowlAxiom *axiom) {
    if (!axiom) {
        cowl_parser_handle_error_type(parser, COWL_ERR_MEM);
        return COWL_ERR_MEM;
    }

    cowl_ret ret = cowl_ontology_add_axiom(parser->ontology, axiom);

    if (ret) {
        cowl_parser_handle_error_type(parser, ret);
        return ret;
    }

    return COWL_OK;
}

cowl_ret cowl_parser_register_ns(CowlParser *parser, CowlString *prefix, CowlString *ns) {
    uhash_ret ret = uhmap_add(CowlObjectTable, parser->prefix_ns_map, prefix, ns, NULL);

    if (ret == UHASH_ERR) {
        cowl_parser_handle_error_type(parser, COWL_ERR_MEM);
        return COWL_ERR_MEM;
    }

    if (ret == UHASH_INSERTED) {
        cowl_string_retain(prefix);
        cowl_string_retain(ns);
    }

    return COWL_OK;
}

CowlIRI* cowl_parser_get_full_iri(CowlParser *parser, CowlRawString string) {
    cowl_uint ns_length = cowl_raw_string_index_of(string, ':') + 1;

    // We might use 'cowl_string_get_ns_rem' to obtain a prefix/suffix split, though
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

    CowlString *ns = uhmap_get(CowlObjectTable, parser->prefix_ns_map, &ns_str, NULL);
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
        CowlRawString err_str = cowl_raw_string_concat(cowl_array_size(comp), comp);
        cowl_parser_handle_error(parser, COWL_ERR_SYNTAX, err_str.cstring);
        cowl_raw_string_deinit(err_str);
    }

    cowl_string_release(rem);
    return iri;
}

CowlAnonInd* cowl_parser_get_anon_ind(CowlParser *parser, CowlRawString id) {
    uhash_uint idx;
    CowlString id_str = cowl_string_init(id);
    uhash_ret ret = uhash_put(CowlObjectTable, parser->anon_ind_map, &id_str, &idx);

    CowlAnonInd *ind = NULL;

    if (ret == UHASH_INSERTED) {
        CowlString *string = cowl_string_copy(&id_str);
        ind = cowl_anon_ind_get();

        if (string && ind) {
            uhash_key(parser->anon_ind_map, idx) = string;
            uhash_value(parser->anon_ind_map, idx) = cowl_anon_ind_retain(ind);
        } else {
            uhash_delete(CowlObjectTable, parser->anon_ind_map, idx);
            cowl_string_release(string);
            cowl_anon_ind_release(ind);
            ind = NULL;
        }
    } else if (ret == UHASH_PRESENT) {
        ind = uhash_value(parser->anon_ind_map, idx);
        cowl_anon_ind_retain(ind);
    }

    return ind;
}

static inline cowl_uint cowl_parser_get_line(CowlParser *parser) {
    if (!(parser->scanner && cowl_functional_get_lloc(parser->scanner))) return 0;
    return (cowl_uint)cowl_functional_get_lloc(parser->scanner)->last_line;
}

void cowl_parser_handle_error(CowlParser *parser, cowl_ret code, char const *description) {
    CowlErrorHandler handler = parser->handler;
    if (!handler.handle_error) handler = cowl_api_get_error_handler();
    if (!handler.handle_error) return;

    char const *temp = parser->stream->description;
    CowlString source = cowl_string_init(cowl_raw_string_init(temp, strlen(temp), false));

    temp = description;
    CowlString descr = cowl_string_init(cowl_raw_string_init(temp, strlen(temp), false));

    CowlError error = {
        .code = code,
        .location = {
            .line = cowl_parser_get_line(parser),
            .source = &source,
            .iri = cowl_ontology_get_id(parser->ontology).ontology_iri,
        },
        .description = &descr
    };

    handler.handle_error(handler.ctx, &error);
}

void cowl_parser_handle_error_type(CowlParser *parser, cowl_ret code) {
    cowl_parser_handle_error(parser, code, cowl_ret_to_cstring(code));
}
