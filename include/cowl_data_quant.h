/**
 * Declares CowlDataQuant and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_DATA_QUANT_H
#define COWL_DATA_QUANT_H

#include "cowl_object.h"
#include "cowl_quant_type.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlDataRange);
cowl_struct_decl(CowlDataPropExp);
cowl_struct_decl(CowlDataQuant);
/// @endcond

/**
 * Represents [DataSomeValuesFrom] and [DataAllValuesFrom] in the OWL 2 specification.
 *
 * [DataSomeValuesFrom]: https://www.w3.org/TR/owl2-syntax/#Existential_Quantification_2
 * [DataAllValuesFrom]: https://www.w3.org/TR/owl2-syntax/#Universal_Quantification_2
 *
 * @struct CowlDataQuant
 * @extends CowlClsExp
 */

/**
 * Returns a retained data quantifier.
 *
 * @param type Data quantifier type.
 * @param prop The data property.
 * @param range Range of the quantifier.
 * @return Retained data quantifier, or NULL on error.
 *
 * @public @memberof CowlDataQuant
 */
COWL_PUBLIC
CowlDataQuant *
cowl_data_quant(CowlQuantType type, CowlAnyDataPropExp *prop, CowlAnyDataRange *range);

/**
 * Retains the specified data quantifier.
 *
 * @param restr The data quantifier.
 * @return Retained data quantifier.
 *
 * @public @memberof CowlDataQuant
 */
COWL_INLINE
CowlDataQuant *cowl_data_quant_retain(CowlDataQuant *restr) {
    return (CowlDataQuant *)cowl_retain(restr);
}

/**
 * Releases the specified data quantifier.
 *
 * @param restr The data quantifier.
 *
 * @public @memberof CowlDataQuant
 */
COWL_INLINE
void cowl_data_quant_release(CowlDataQuant *restr) {
    cowl_release_impl(restr);
}

/**
 * Gets the type of the specified data quantifier.
 *
 * @param restr The data quantifier.
 * @return The type of the data quantifier.
 *
 * @public @memberof CowlDataQuant
 */
COWL_INLINE
CowlQuantType cowl_data_quant_get_type(CowlDataQuant *restr) {
    return (CowlQuantType)(cowl_get_type(restr) - COWL_OT_CE_DATA_SOME);
}

/**
 * Gets the data property.
 *
 * @param restr The data quantifier.
 * @return The data property.
 *
 * @public @memberof CowlDataQuant
 */
COWL_INLINE
CowlDataPropExp *cowl_data_quant_get_prop(CowlDataQuant *restr) {
    return (CowlDataPropExp *)cowl_get_field(restr, 0);
}

/**
 * Gets the range of the specified data quantifier.
 *
 * @param restr The data quantifier.
 * @return Range of the data quantifier.
 *
 * @public @memberof CowlDataQuant
 */
COWL_PUBLIC
CowlDataRange *cowl_data_quant_get_range(CowlDataQuant *restr);

/**
 * Returns the string representation of the specified data quantifier.
 *
 * @param restr The data quantifier.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlDataQuant
 */
COWL_INLINE
CowlString *cowl_data_quant_to_string(CowlDataQuant *restr) {
    return cowl_to_string(restr);
}

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlDataQuant
 */
COWL_INLINE
bool cowl_data_quant_equals(CowlDataQuant *lhs, CowlDataQuant *rhs) {
    return cowl_equals_impl(lhs, rhs);
}

/**
 * Hash function.
 *
 * @param restr The data quantifier.
 * @return The hash value.
 *
 * @public @memberof CowlDataQuant
 */
COWL_INLINE
ulib_uint cowl_data_quant_hash(CowlDataQuant *restr) {
    return cowl_hash_impl(restr);
}

/**
 * Iterates over the primitives referenced by the specified data quantifier.
 *
 * @param restr The data quantifier.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlDataQuant
 */
COWL_INLINE
bool cowl_data_quant_iterate_primitives(CowlDataQuant *restr, CowlPrimitiveFlags flags,
                                        CowlIterator *iter) {
    return cowl_iterate_primitives_impl(restr, flags, iter);
}

COWL_END_DECLS

#endif // COWL_DATA_QUANT_H
