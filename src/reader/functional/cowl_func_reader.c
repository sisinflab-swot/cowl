/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_func_yylexer.h"
#include "cowl_reader.h"

static cowl_ret cowl_func_reader_read(UIStream *istream, CowlStream *stream) {
    void *scanner;
    if (cowl_func_yylex_init(&scanner) != 0) return COWL_ERR_MEM;
    cowl_func_yyset_in(NULL, scanner);
    cowl_func_yyset_extra(istream, scanner);
    cowl_ret ret = cowl_func_yyparse(scanner, stream) == 0 ? COWL_OK : COWL_ERR;
    cowl_func_yylex_destroy(scanner);
    return ret;
}

static CowlReader const cowl_func_reader = {
    .name = "functional",
    .read = cowl_func_reader_read,
};

CowlReader cowl_reader_functional(void) {
    return cowl_func_reader;
}
