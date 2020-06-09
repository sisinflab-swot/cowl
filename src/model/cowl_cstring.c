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
    char *buf = malloc(length + 1);

    if (buf) {
        memcpy(buf, string, length);
        buf[length] = '\0';
    }

    return buf;
}
