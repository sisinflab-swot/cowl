/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2024 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_OBJ_QUANT_PRIVATE_H
#define COWL_OBJ_QUANT_PRIVATE_H

#include "cowl_iterator.h"
#include "cowl_obj_quant.h" // IWYU pragma: export
#include "cowl_primitive_flags.h"
#include "cowl_ret.h"

cowl_ret cowl_obj_quant_iterate_primitives(CowlObjQuant *restr, CowlPrimitiveFlags flags,
                                           CowlIterator *iter);

#endif // COWL_OBJ_QUANT_PRIVATE_H
