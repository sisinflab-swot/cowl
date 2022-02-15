/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_func_parser.h"
#include "cowl_anon_ind.h"
#include "cowl_func_yylexer.h"
#include "cowl_iri.h"
#include "cowl_object_table_private.h"
#include "cowl_parser_ctx.h"
#include "cowl_string_private.h"

static CowlParser const cowl_func_parser = {
    .name = "functional",
    .alloc = cowl_func_parser_alloc,
    .free = cowl_func_parser_free,
    .parse = cowl_func_parser_parse,
    .get_line = cowl_func_parser_get_line
};

CowlParser cowl_parser_get_functional(void) {
    return cowl_func_parser;
}

void* cowl_func_parser_alloc(void) {
    CowlFuncParser *parser = ulib_alloc(parser);
    UHash(CowlObjectTable) *prefix_ns_map = cowl_string_map_alloc();
    UHash(CowlObjectTable) *anon_ind_map = cowl_string_map_alloc();

    if (!(parser && anon_ind_map && prefix_ns_map)) {
        ulib_free(parser);
        uhash_free(CowlObjectTable, prefix_ns_map);
        uhash_free(CowlObjectTable, anon_ind_map);
        return NULL;
    }

    *parser = (CowlFuncParser) {
        .prefix_ns_map = prefix_ns_map,
        .anon_ind_map = anon_ind_map
    };

    return parser;
}

void cowl_func_parser_free(void *state) {
    if (!state) return;

    CowlFuncParser *parser = state;

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

    ulib_free(parser);
}

cowl_ret cowl_func_parser_parse(void *state, UIStream *stream, CowlParserCtx *ctx) {
    CowlFuncParser *parser = state;
    parser->ctx = ctx;

    if (cowl_func_yylex_init(&parser->scanner)) {
        cowl_parser_ctx_handle_error_type(ctx, COWL_ERR_MEM);
        return COWL_ERR_MEM;
    }

    cowl_func_yyset_in(NULL, parser->scanner);
    cowl_func_yyset_extra(stream, parser->scanner);
    cowl_ret ret = cowl_func_yyparse(parser->scanner, parser) == 0 ? COWL_OK : COWL_ERR;
    cowl_func_yylex_destroy(parser->scanner);

    return ret;
}

ulib_uint cowl_func_parser_get_line(void *state) {
    CowlFuncParser *parser = state;
    if (!(parser->scanner && cowl_func_yyget_lloc(parser->scanner))) return 0;
    return (ulib_uint)cowl_func_yyget_lloc(parser->scanner)->last_line;
}

cowl_ret cowl_func_parser_register_ns(CowlFuncParser *parser, CowlString *prefix, CowlString *ns) {
    uhash_ret ret = uhmap_add(CowlObjectTable, parser->prefix_ns_map, prefix, ns, NULL);

    if (ret == UHASH_ERR) {
        cowl_parser_ctx_handle_error_type(parser->ctx, COWL_ERR_MEM);
        return COWL_ERR_MEM;
    }

    if (ret == UHASH_INSERTED) {
        cowl_string_retain(prefix);
        cowl_string_retain(ns);
    }

    return COWL_OK;
}

CowlIRI* cowl_func_parser_get_full_iri(CowlFuncParser *parser, UString string) {
    ulib_uint ns_length = ustring_index_of(string, ':') + 1;
    char const *str = ustring_data(string);
    ulib_uint str_length = ustring_length(string);

    // We might use 'cowl_string_get_ns_rem' to obtain a prefix/suffix split, though
    // this involves two allocations: one for the prefix, and one for the suffix.
    // Since we only need the prefix for a hash table lookup, we can avoid its allocation
    // on the heap and keep it on the stack instead.
    UString raw_ns = ustring_wrap(str, ns_length);
    CowlString ns_str = cowl_string_init(raw_ns);

    // If the remainder is empty, another slight optimization involves
    // using a shared empty string instance.
    CowlString *rem;

    if (ns_length < str_length) {
        rem = cowl_string_get(ustring_copy(str + ns_length, str_length - ns_length));
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
        UString comp[] = {
            ustring_literal("no namespace mapping for "),
            raw_ns
        };
        UString err_str = ustring_concat(comp, ulib_array_count(comp));
        cowl_parser_ctx_handle_error(parser->ctx, COWL_ERR_SYNTAX, err_str);
        ustring_deinit(err_str);
    }

    cowl_string_release(rem);
    return iri;
}

CowlAnonInd* cowl_func_parser_get_anon_ind(CowlFuncParser *parser, UString id) {
    ulib_uint idx;
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
