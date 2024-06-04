/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_cstring.h"
#include "ulib.h"
#include <stddef.h>

size_t cowl_str_from_uint(ulib_uint uint, char *buf) {
    char *cur = buf;

    do {
        *(cur++) = (char)(uint % 10 + '0');
        uint /= 10;
    } while (uint);

    *cur = '\0';
    size_t const len = cur - buf;

    while (cur > buf) {
        char tmp = *(--cur);
        *cur = *buf;
        *(buf++) = tmp;
    }

    return len;
}

ulib_uint cowl_str_to_uint(char const *string, size_t length) {
    ulib_uint res = 0;

    for (char const *last = string + length; string < last; ++string) {
        if (*string < '0' || *string > '9') return (ulib_uint)-1;
        res = res * 10 + (*string - '0');
    }

    return res;
}
