/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_attrs.h"
#include "cowl_change_handler.h"
#include "cowl_func_yylexer.h"
#include "cowl_func_yyparser.h"
#include "cowl_object.h"
#include "cowl_prefix_map.h"
#include "cowl_reader.h"
#include "cowl_ret.h"
#include "ulib.h"
#include <stddef.h>

static inline cowl_ret yyparse_to_cowl_ret(int ret) {
    switch (ret) {
        case 0: return COWL_OK;
        case 1: return COWL_ERR_SYNTAX;
        case 2: return COWL_ERR_MEM;
        default: return COWL_ERR;
    }
}

static cowl_ret func_read(cowl_unused void *ctx, UIStream *stream, CowlChangeHandler handler) {
    cowl_ret ret = COWL_ERR_MEM;

    CowlPrefixMap *pm = cowl_prefix_map();
    if (!pm) goto end;

    void *scanner;
    if (cowl_func_yylex_init(&scanner) != 0) goto end;
    cowl_func_yyset_in(NULL, scanner);
    cowl_func_yyset_extra(stream, scanner);
    ret = yyparse_to_cowl_ret(cowl_func_yyparse(scanner, pm, &handler));
    cowl_func_yylex_destroy(scanner);

end:
    cowl_release(pm);
    return ret;
}

CowlReader *cowl_reader_functional(void) {
    return cowl_reader((CowlReaderImpl){
        .name = "functional",
        .read = func_read,
    });
}
