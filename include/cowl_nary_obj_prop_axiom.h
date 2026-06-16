/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <https://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_NARY_OBJ_PROP_AXIOM_H
#define COWL_NARY_OBJ_PROP_AXIOM_H

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
 * Represents an [EquivalentObjectProperties] or [DisjointObjectProperties] axiom
 * in the OWL 2 specification.
 *
 * [EquivalentObjectProperties]: https://www.w3.org/TR/owl2-syntax/#Equivalent_Object_Properties
 * [DisjointObjectProperties]: https://www.w3.org/TR/owl2-syntax/#Disjoint_Object_Properties
 *
 * @superstruct{CowlAxiom}
 * @struct CowlNAryObjPropAxiom
 */
cowl_struct_decl(CowlNAryObjPropAxiom);

/**
 * @defgroup CowlNAryObjPropAxiom CowlNAryObjPropAxiom API
 * @{
 */

/**
 * Returns a N-ary object property axiom.
 *
 * @param type The type.
 * @param props The object properties.
 * @param annot @ctype{optional} The annotations.
 * @return Axiom, or NULL on error.
 */
COWL_RETAINED
COWL_INLINE
CowlNAryObjPropAxiom *
cowl_nary_obj_prop_axiom(CowlNAryAxiomType type, CowlVector *props, CowlVector *annot) {
    if (!cowl_enum_value_is_valid(NAT, type)) return NULL;
    CowlObjectType t = (CowlObjectType)(COWL_OT_A_EQUIV_OBJ_PROP + (CowlObjectType)type);
    return (CowlNAryObjPropAxiom *)cowl_get_impl_1_annot(t, props, annot);
}

/**
 * Returns an EquivalentObjectProperties axiom.
 *
 * @param props The object properties.
 * @param annot @ctype{optional} The annotations.
 * @return Axiom, or NULL on error.
 */
COWL_RETAINED
COWL_INLINE
CowlNAryObjPropAxiom *cowl_equiv_obj_prop_axiom(CowlVector *props, CowlVector *annot) {
    return cowl_nary_obj_prop_axiom(COWL_NAT_EQUIV, props, annot);
}

/**
 * Returns an EquivalentObjectProperties axiom.
 *
 * @param ... The object properties.
 * @return Axiom, or NULL on error.
 *
 * @alias CowlNAryObjPropAxiom *cowl_equiv_obj_prop_axiom_with(...);
 */
COWL_RETAINED
#define cowl_equiv_obj_prop_axiom_with(...)                                                        \
    cowl_nary_get_impl(COWL_OT_A_EQUIV_OBJ_PROP, __VA_ARGS__, NULL)

/**
 * Returns a DisjointObjectProperties axiom.
 *
 * @param props The object properties.
 * @param annot @ctype{optional} The annotations.
 * @return Axiom, or NULL on error.
 */
COWL_RETAINED
COWL_INLINE
CowlNAryObjPropAxiom *cowl_disj_obj_prop_axiom(CowlVector *props, CowlVector *annot) {
    return cowl_nary_obj_prop_axiom(COWL_NAT_DISJ, props, annot);
}

/**
 * Returns a DisjointObjectProperties axiom.
 *
 * @param ... The object properties.
 * @return Axiom, or NULL on error.
 *
 * @alias CowlNAryObjPropAxiom *cowl_disj_obj_prop_axiom_with(...);
 */
COWL_RETAINED
#define cowl_disj_obj_prop_axiom_with(...)                                                         \
    cowl_nary_get_impl(COWL_OT_A_DISJ_OBJ_PROP, __VA_ARGS__, NULL)

/**
 * Gets the type of the specified N-ary object property axiom.
 *
 * @param axiom The axiom.
 * @return The type.
 */
COWL_PURE
COWL_INLINE
CowlNAryAxiomType cowl_nary_obj_prop_axiom_get_type(CowlNAryObjPropAxiom *axiom) {
    return (CowlNAryAxiomType)(cowl_get_type(axiom) - COWL_OT_A_EQUIV_OBJ_PROP);
}

/**
 * Gets the object properties of the specified N-ary object property axiom.
 *
 * @param axiom The axiom.
 * @return The object properties.
 */
COWL_PURE
COWL_INLINE
CowlVector *cowl_nary_obj_prop_axiom_get_props(CowlNAryObjPropAxiom *axiom) {
    return (CowlVector *)cowl_get_field(axiom, 0);
}

/// @}

COWL_END_DECLS

#endif // COWL_NARY_OBJ_PROP_AXIOM_H
