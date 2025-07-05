/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_ret.h"
#include "cowl_string.h"
#include "ulib.h"

UString cowl_ret_to_ustring(cowl_ret ret) {
    switch (ret) {
        case COWL_OK: return ustring_literal("success");
        case COWL_ERR_IO: return ustring_literal("input/output error");
        case COWL_ERR_MEM: return ustring_literal("memory exhausted");
        case COWL_ERR_SYNTAX: return ustring_literal("syntax error");
        default: return ustring_literal("error");
    }
}

cowl_ret cowl_ret_from_ulib(ulib_ret ret) {
    switch (ret) {
        case ULIB_OK:
        case ULIB_NO: return COWL_OK;
        case ULIB_ERR_IO: return COWL_ERR_IO;
        case ULIB_ERR_MEM: return COWL_ERR_MEM;
        default: return COWL_ERR;
    }
}

CowlString *cowl_ret_to_string(cowl_ret ret) {
    return cowl_string_opt(cowl_ret_to_ustring(ret), COWL_SO_COPY);
}
