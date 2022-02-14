/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_PARSER_CTX_PRIVATE_H
#define COWL_PARSER_CTX_PRIVATE_H

#include "cowl_parser_ctx.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlManager);

typedef struct CowlParserCtx {
    CowlManager *manager;
    CowlOntology *ontology;
    char const *description;
    void *state;
} CowlParserCtx;

void cowl_parser_ctx_handle_stream_error(CowlParserCtx *ctx, ustream_ret code);

COWL_END_DECLS

#endif // COWL_PARSER_CTX_PRIVATE_H
