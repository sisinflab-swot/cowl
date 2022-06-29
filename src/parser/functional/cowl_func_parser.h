/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_FUNC_PARSER_H
#define COWL_FUNC_PARSER_H

#include "cowl_parser.h"

COWL_BEGIN_DECLS

typedef struct CowlFuncParser {
    CowlEditor *editor;
    void *scanner;
} CowlFuncParser;

void* cowl_func_parser_alloc(void);
void cowl_func_parser_free(void *state);
cowl_ret cowl_func_parser_parse(void *state, UIStream *stream, CowlEditor *editor);
ulib_uint cowl_func_parser_get_line(void *state);

COWL_END_DECLS

#endif // COWL_FUNC_PARSER_H
