/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <https://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_NARY_DATA_PROP_AXIOM_H
#define COWL_NARY_DATA_PROP_AXIOM_H

#include "cowl_attrs.h"
#include "cowl_impl.h"
#include "cowl_nary_axiom_type.h"
#include "cowl_object.h"
#include "cowl_object_type.h"
#include "cowl_utils.h"
#include <stddef.h>

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlVector);
/// @endcond

/**
 * Represents an [EquivalentDataProperties] or [DisjointDataProperties] axiom
 * in the OWL 2 specification.
 *
 * [EquivalentDataProperties]: https://www.w3.org/TR/owl2-syntax/#Equivalent_Data_Properties
 * [DisjointDataProperties]: https://www.w3.org/TR/owl2-syntax/#Disjoint_Data_Properties
 *
 * @superstruct{CowlAxiom}
 * @struct CowlNAryDataPropAxiom
 */
cowl_struct_decl(CowlNAryDataPropAxiom);

/**
 * @defgroup CowlNAryDataPropAxiom CowlNAryDataPropAxiom API
 * @{
 */

/**
 * Returns a N-ary data property axiom.
 *
 * @param type The type.
 * @param props The data properties.
 * @param annot @ctype{optional} The annotations.
 * @return Axiom, or NULL on error.
 */
COWL_RETAINED
COWL_INLINE
CowlNAryDataPropAxiom *
cowl_nary_data_prop_axiom(CowlNAryAxiomType type, CowlVector *props, CowlVector *annot) {
    if (!cowl_enum_value_is_valid(NAT, type)) return NULL;
    CowlObjectType t = (CowlObjectType)(COWL_OT_A_EQUIV_DATA_PROP + (CowlObjectType)type);
    return (CowlNAryDataPropAxiom *)cowl_get_impl_1_annot(t, props, annot);
}

/**
 * Returns an EquivalentDataProperties axiom.
 *
 * @param props The data properties.
 * @param annot @ctype{optional} The annotations.
 * @return Axiom, or NULL on error.
 */
COWL_RETAINED
COWL_INLINE
CowlNAryDataPropAxiom *cowl_equiv_data_prop_axiom(CowlVector *props, CowlVector *annot) {
    return cowl_nary_data_prop_axiom(COWL_NAT_EQUIV, props, annot);
}

/**
 * Returns an EquivalentDataProperties axiom.
 *
 * @param ... The data properties.
 * @return Axiom, or NULL on error.
 *
 * @alias CowlNAryDataPropAxiom *cowl_equiv_data_prop_axiom_with(...);
 */
COWL_RETAINED
#define cowl_equiv_data_prop_axiom_with(...)                                                       \
    cowl_nary_get_impl(COWL_OT_A_EQUIV_DATA_PROP, __VA_ARGS__, NULL)

/**
 * Returns a DisjointDataProperties axiom.
 *
 * @param props The data properties.
 * @param annot @ctype{optional} The annotations.
 * @return Axiom, or NULL on error.
 */
COWL_RETAINED
COWL_INLINE
CowlNAryDataPropAxiom *cowl_disj_data_prop_axiom(CowlVector *props, CowlVector *annot) {
    return cowl_nary_data_prop_axiom(COWL_NAT_DISJ, props, annot);
}

/**
 * Returns a DisjointDataProperties axiom.
 *
 * @param ... The data properties.
 * @return Axiom, or NULL on error.
 *
 * @alias CowlNAryDataPropAxiom *cowl_disj_data_prop_axiom_with(...);
 */
COWL_RETAINED
#define cowl_disj_data_prop_axiom_with(...)                                                        \
    cowl_nary_get_impl(COWL_OT_A_DISJ_DATA_PROP, __VA_ARGS__, NULL)

/**
 * Gets the type of the specified N-ary data property axiom.
 *
 * @param axiom The axiom.
 * @return The type.
 */
COWL_PURE
COWL_INLINE
CowlNAryAxiomType cowl_nary_data_prop_axiom_get_type(CowlNAryDataPropAxiom *axiom) {
    return (CowlNAryAxiomType)(cowl_get_type(axiom) - COWL_OT_A_EQUIV_DATA_PROP);
}

/**
 * Gets the data properties of the specified N-ary data property axiom.
 *
 * @param axiom The axiom.
 * @return The data properties.
 */
COWL_PURE
COWL_INLINE
CowlVector *cowl_nary_data_prop_axiom_get_props(CowlNAryDataPropAxiom *axiom) {
    return (CowlVector *)cowl_get_field(axiom, 0);
}

/// @}

COWL_END_DECLS

#endif // COWL_NARY_DATA_PROP_AXIOM_H
