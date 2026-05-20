/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2024 SisInf Lab, Polytechnic University of Bari
 * @copyright <https://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 */

#ifndef COWL_DATA_QUANT_PRIVATE_H
#define COWL_DATA_QUANT_PRIVATE_H

#include "cowl_data_quant.h" // IWYU pragma: export
#include "cowl_iterator.h"
#include "cowl_primitive_flags.h"
#include "cowl_ret.h"

cowl_ret cowl_data_quant_iterate_primitives(CowlDataQuant *restr, CowlPrimitiveFlags flags,
                                            CowlIterator *iter);

#endif // COWL_DATA_QUANT_PRIVATE_H
