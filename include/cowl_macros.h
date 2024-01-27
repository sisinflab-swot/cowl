/**
 * Utility macros.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2024 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_MACROS_H
#define COWL_MACROS_H

#include "cowl_attrs.h"

COWL_BEGIN_DECLS

/**
 * Struct type forward declaration.
 *
 * @param NAME Name of the struct type.
 */
#define cowl_struct_decl(NAME) typedef struct NAME NAME

/**
 * Checks whether the specified enum value is valid.
 *
 * @param T Enumeration name.
 * @param val Enumeration value.
 * @return True if the value is valid, false otherwise.
 */
#define cowl_enum_value_is_valid(T, val) ((unsigned)(val) < COWL_##T##_COUNT)

COWL_END_DECLS

#endif // COWL_MACROS_H
