/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_func_parser.h"
#include "cowl_editor.h"
#include "cowl_func_yylexer.h"

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
    if (parser) *parser = (CowlFuncParser) {0};
    return parser;
}

void cowl_func_parser_free(void *state) {
    ulib_free(state);
}

cowl_ret cowl_func_parser_parse(void *state, UIStream *stream, CowlEditor *editor) {
    CowlFuncParser *parser = state;
    parser->editor = editor;

    if (cowl_func_yylex_init(&parser->scanner)) {
        cowl_editor_handle_error_type(editor, COWL_ERR_MEM);
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
