/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_xml_utils.h"

#define IS_NCNAME_START_CHAR(CH)                                                                    \
    ((CH >= 'A' && CH <= 'Z') || CH == '_' || (CH >= 'a' && CH <= 'z') ||                           \
     (CH >= 0xC0 && CH <= 0xD6) || (CH >= 0xD8 && CH <= 0xF6) || (CH >= 0xF8))

#define IS_NCNAME_NON_START_CHAR(CH) \
    (CH == '-' || CH == '.' || (CH >= '0' && CH <= '9') || CH == 0xB7)

cowl_uint_t cowl_xml_ns_length(CowlRawString string) {
    // This is currently not completely compliant with the NCName specification.
    // TODO: account for Unicode code points.
    cowl_uint_t ns_length = string.length;

    for (cowl_uint_t i = string.length; i-- != 0;) {
        unsigned char ch = string.cstring[i];
        if (IS_NCNAME_START_CHAR(ch)) {
            ns_length = i;
        } else if (!IS_NCNAME_NON_START_CHAR(ch)) {
            break;
        }
    }

    return ns_length;
}
