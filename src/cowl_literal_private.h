/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_LITERAL_PRIVATE_H
#define COWL_LITERAL_PRIVATE_H

#include "cowl_literal.h"
#include "cowl_object_private.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlDatatype);
cowl_struct_decl(CowlString);

struct CowlLiteral {
    CowlHashObject super;
    CowlDatatype *dt;
    CowlString *value;
    CowlString *lang;
};

CowlLiteral* cowl_literal_get_raw(CowlDatatype *dt, UString value, UString lang);

COWL_END_DECLS

#endif // COWL_LITERAL_PRIVATE_H
