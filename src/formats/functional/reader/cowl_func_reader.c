/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <https://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 */

#include "cowl_change_handler.h"
#include "cowl_error.h"
#include "cowl_func_yylexer.h"
#include "cowl_func_yyparser.h"
#include "cowl_object.h"
#include "cowl_prefix_map.h"
#include "cowl_reader.h"
#include "cowl_ret.h"
#include "cowl_writer.h"
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

static cowl_ret func_read(void *ctx, UIStream *stream, CowlChangeHandler handler) {
    cowl_ret ret = COWL_ERR_MEM;

    CowlFuncState state = {
        .stream = stream,
        .prefix_map = cowl_prefix_map(),
        .handler = &handler,
        .error = ctx,
        .qstring = ustrbuf(),
    };

    if (!state.prefix_map) goto end;

    void *scanner;
    if (cowl_func_yylex_init(&scanner) != 0) goto end;
    cowl_func_yyset_in(NULL, scanner);
    cowl_func_yyset_extra(&state, scanner);
    ret = yyparse_to_cowl_ret(cowl_func_yyparse(scanner, &state));
    cowl_func_yylex_destroy(scanner);

end:
    cowl_release(state.prefix_map);
    ustrbuf_deinit(&state.qstring);
    return ret;
}

static CowlError const *last_error(void *ctx) {
    return ctx;
}

static void free_error(void *err) {
    cowl_error_deinit(err);
    ulib_free(err);
}

CowlReader *cowl_reader_functional(void) {
    CowlError *err = ulib_alloc(err);
    if (!err) return NULL;
    *err = cowl_error(COWL_OK, NULL);

    return cowl_reader((CowlReaderImpl){
        .ctx = err,
        .name = "functional",
        .read = func_read,
        .last_error = last_error,
        .free = free_error,
    });
}
