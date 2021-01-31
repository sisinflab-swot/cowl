/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_STRING_PRIVATE_H
#define COWL_STRING_PRIVATE_H

#include "cowl_string.h"
#include "cowl_object_private.h"
#include "cowl_raw_string.h"

COWL_BEGIN_DECLS

cowl_struct(CowlString) {
    CowlHashObject super;
    CowlRawString raw_string;
};

cowl_ret cowl_string_api_init(void);
void cowl_string_api_deinit(void);

CowlString* cowl_string_alloc(CowlRawString raw_string);
CowlString cowl_string_init(CowlRawString raw_string);

CowlString* cowl_string_intern(CowlString *string);

CowlString* cowl_string_copy(CowlString *string);
cowl_ret cowl_string_split_two(CowlRawString string, cowl_uint lhs_length, CowlString **out);

COWL_END_DECLS

#endif // COWL_STRING_PRIVATE_H
