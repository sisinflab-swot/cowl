/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2024 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_DATA_QUANT_PRIVATE_H
#define COWL_DATA_QUANT_PRIVATE_H

#include "cowl_data_quant.h" // IWYU pragma: export
#include "cowl_iterator.h"
#include "cowl_primitive_flags.h"

bool cowl_data_quant_iterate_primitives(CowlDataQuant *restr, CowlPrimitiveFlags flags,
                                        CowlIterator *iter);

#endif // COWL_DATA_QUANT_PRIVATE_H
