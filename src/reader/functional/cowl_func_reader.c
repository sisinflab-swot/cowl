/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_editor.h"
#include "cowl_reader.h"
#include "cowl_func_yylexer.h"

static void* cowl_func_reader_alloc(void) {
    void *scanner;
    return cowl_func_yylex_init(&scanner) == 0 ? scanner : NULL;
}

static void cowl_func_reader_free(void *scanner) {
    cowl_func_yylex_destroy(scanner);
}

static cowl_ret cowl_func_reader_read(void *scanner, UIStream *stream, CowlEditor *editor) {
    cowl_func_yyset_in(NULL, scanner);
    cowl_func_yyset_extra(stream, scanner);
    return cowl_func_yyparse(scanner, editor) == 0 ? COWL_OK : COWL_ERR;
}

static CowlReader const cowl_func_reader = {
    .name = "functional",
    .alloc = cowl_func_reader_alloc,
    .free = cowl_func_reader_free,
    .read = cowl_func_reader_read,
};

CowlReader cowl_reader_functional(void) {
    return cowl_func_reader;
}
