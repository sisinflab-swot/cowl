/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_xml_utils.h"

#define IS_NCNAME_START_CHAR(C)                                                                     \
    (((C) >= 'A' && (C) <= 'Z') || (C) == '_' || ((C) >= 'a' && (C) <= 'z') ||                      \
     ((C) >= 0xC0 && (C) <= 0xD6) || ((C) >= 0xD8 && (C) <= 0xF6) || ((C) >= 0xF8))

#define IS_NCNAME_NON_START_CHAR(C) \
    ((C) == '-' || (C) == '.' || ((C) >= '0' && (C) <= '9') || (C) == 0xB7)

ulib_uint cowl_xml_ns_length(UString string) {
    // This is currently not completely compliant with the NCName specification.
    // TODO: account for Unicode code points.
    ulib_uint ns_length = ustring_length(string);
    char const *cstring = ustring_data(string);

    for (ulib_uint i = ns_length; i-- != 0;) {
        unsigned char ch = (unsigned char)cstring[i];
        if (IS_NCNAME_START_CHAR(ch)) {
            ns_length = i;
        } else if (!IS_NCNAME_NON_START_CHAR(ch)) {
            break;
        }
    }

    return ns_length;
}
