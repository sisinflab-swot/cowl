/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_FUNC_PARSER_H
#define COWL_FUNC_PARSER_H

#include "cowl_parser.h"
#include "cowl_raw_string.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlAnonInd);
cowl_struct_decl(CowlIRI);
cowl_hash_decl(CowlObjectTable);

typedef cowl_struct(CowlFuncParser) {
    CowlParserCtx *ctx;
    UHash(CowlObjectTable) *prefix_ns_map;
    UHash(CowlObjectTable) *anon_ind_map;
    void *scanner;
} CowlFuncParser;

void* cowl_func_parser_alloc(void);
void cowl_func_parser_free(void *state);
cowl_ret cowl_func_parser_parse(void *state, CowlParserCtx *ctx);
cowl_uint cowl_func_parser_get_line(void *state);

cowl_ret cowl_func_parser_register_ns(CowlFuncParser *parser, CowlString *prefix, CowlString *ns);
CowlIRI* cowl_func_parser_get_full_iri(CowlFuncParser *parser, CowlRawString string);
CowlAnonInd* cowl_func_parser_get_anon_ind(CowlFuncParser *parser, CowlRawString id);

COWL_END_DECLS

#endif // COWL_FUNC_PARSER_H
