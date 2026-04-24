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
#include "ulib.h"

UString cowl_ret_to_string(cowl_ret ret) {
    if (ret == COWL_ERR_SYNTAX) return ustring_literal("syntax error");
    return ulib_ret_to_string(ret);
}
