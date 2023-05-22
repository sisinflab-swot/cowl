/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_STRING_PRIVATE_H
#define COWL_STRING_PRIVATE_H

#include "cowl_object_private.h"
#include "cowl_string.h"

COWL_BEGIN_DECLS

struct CowlString {
    CowlObject super;
    ulib_uint hash;
    UString raw_string;
};

cowl_ret cowl_string_api_init(void);
void cowl_string_api_deinit(void);

CowlString cowl_string_init(UString raw_string);
CowlString *cowl_string_copy(CowlString *string);
void cowl_string_free(CowlString *string);
cowl_ret cowl_string_get_ns_rem(UString string, ulib_uint ns_length, CowlString **out);

COWL_END_DECLS

#endif // COWL_STRING_PRIVATE_H
