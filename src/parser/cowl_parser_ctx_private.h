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
#include "cowl_reader_private.h"

COWL_BEGIN_DECLS

typedef cowl_struct(CowlParserCtx) {
    CowlReader super;
} CowlParserCtx;

COWL_END_DECLS

#endif // COWL_PARSER_CTX_PRIVATE_H
