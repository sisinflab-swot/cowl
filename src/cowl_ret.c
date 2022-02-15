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

UString cowl_ret_to_ustring(cowl_ret ret) {
    switch (ret) {
        case COWL_OK: return ustring_literal("success");
        case COWL_ERR_IO: return ustring_literal("input/output error");
        case COWL_ERR_MEM: return ustring_literal("memory exhausted");
        case COWL_ERR_SYNTAX: return ustring_literal("syntax error");
        case COWL_ERR_IMPORT: return ustring_literal("import error");
        default: return ustring_literal("unknown error");
    }
}

cowl_ret cowl_ret_from_ustream(ustream_ret ret) {
    switch (ret) {
        case USTREAM_OK: return COWL_OK;
        case USTREAM_ERR_BOUNDS:
        case USTREAM_ERR_IO: return COWL_ERR_IO;
        case USTREAM_ERR_MEM: return COWL_ERR_MEM;
        default: return COWL_ERR;
    }
}

cowl_ret cowl_ret_from_uvec(uvec_ret ret) {
    return ret == UVEC_ERR ? COWL_ERR_MEM : COWL_OK;
}

cowl_ret cowl_ret_from_uhash(uhash_ret ret) {
    return ret == UHASH_ERR ? COWL_ERR_MEM : COWL_OK;
}

CowlString* cowl_ret_to_string(cowl_ret ret) {
    return cowl_string_get(ustring_dup(cowl_ret_to_ustring(ret)));
}
