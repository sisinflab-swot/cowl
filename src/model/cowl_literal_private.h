/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_LITERAL_PRIVATE_H
#define COWL_LITERAL_PRIVATE_H

#include "cowl_literal.h"
#include "cowl_object.h"
#include "cowl_raw_string.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlDatatype);
cowl_struct_decl(CowlString);

cowl_struct(CowlLiteral) {
    CowlHashObject super;
    CowlDatatype *dt;
    CowlString *value;
    CowlString *lang;
};

#define COWL_LITERAL_INIT(D, V, L, H) \
    { .super = COWL_HASH_OBJECT_INIT(H), .dt = (D), .value = (V), .lang = (L) }

CowlLiteral* cowl_literal_get_raw(CowlDatatype *dt, CowlRawString value, CowlRawString lang);

COWL_END_DECLS

#endif // COWL_LITERAL_PRIVATE_H
