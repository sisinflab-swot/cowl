/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_MACROS_H
#define COWL_MACROS_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

#define cowl_enum_value_is_valid(T, VAL) ((VAL) >= COWL_##T##_FIRST && (VAL) < COWL_##T##_COUNT)

COWL_END_DECLS

#endif // COWL_MACROS_H
