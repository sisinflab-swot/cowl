/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2023 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_LITERAL_PRIVATE_H
#define COWL_LITERAL_PRIVATE_H

#include "cowl_literal.h"

COWL_BEGIN_DECLS

void cowl_literal_free(CowlLiteral *literal);
bool cowl_literal_equals(CowlLiteral *lhs, CowlLiteral *rhs);
ulib_uint cowl_literal_hash(CowlLiteral *literal);
bool cowl_literal_iterate_primitives(CowlLiteral *literal, CowlPrimitiveFlags flags,
                                     CowlIterator *iter);

COWL_END_DECLS

#endif // COWL_LITERAL_PRIVATE_H
