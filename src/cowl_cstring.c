/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_cstring.h"

char* cowl_strdup(char const *string, size_t length) {
    char *buf = cowl_malloc(length + 1);

    if (buf) {
        memcpy(buf, string, length);
        buf[length] = '\0';
    }

    return buf;
}

cowl_uint cowl_strtouint(char const *string, size_t length) {
    cowl_uint res = 0;

    for (char const *last = string + length; string < last; ++string) {
        if (*string < '0' || *string > '9') return COWL_UINT_MAX;
        res = res * 10 + (*string - '0');
    }

    return res;
}
