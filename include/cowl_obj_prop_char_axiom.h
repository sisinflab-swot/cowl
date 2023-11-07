/**
 * Declares CowlObjPropCharAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_OBJ_PROP_CHAR_AXIOM_H
#define COWL_OBJ_PROP_CHAR_AXIOM_H

#include "cowl_char_axiom_type.h"
#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlObjPropExp);
cowl_struct_decl(CowlVector);
cowl_struct_decl(CowlObjPropCharAxiom);
/// @endcond

/**
 * Represents a [FunctionalObjectProperty], [InverseFunctionalObjectProperty],
 * [SymmetricObjectProperty], [AsymmetricObjectProperty], [TransitiveObjectProperty],
 * [ReflexiveObjectProperty] or [IrreflexiveObjectProperty] axiom in the OWL 2 specification.
 *
 * [FunctionalObjectProperty]:
 * https://www.w3.org/TR/owl2-syntax/#Functional_Object_Properties
 *
 * [InverseFunctionalObjectProperty]:
 * https://www.w3.org/TR/owl2-syntax/#Inverse-Functional_Object_Properties
 *
 * [SymmetricObjectProperty]:
 * https://www.w3.org/TR/owl2-syntax/#Symmetric_Object_Properties
 *
 * [AsymmetricObjectProperty]:
 * https://www.w3.org/TR/owl2-syntax/#Asymmetric_Object_Properties
 *
 * [TransitiveObjectProperty]:
 * https://www.w3.org/TR/owl2-syntax/#Transitive_Object_Properties
 *
 * [ReflexiveObjectProperty]:
 * https://www.w3.org/TR/owl2-syntax/#Reflexive_Object_Properties
 *
 * [IrreflexiveObjectProperty]:
 * https://www.w3.org/TR/owl2-syntax/#Irreflexive_Object_Properties
 *
 * @struct CowlObjPropCharAxiom
 * @extends CowlAxiom
 */

/**
 * Returns an object property characteristic axiom.
 *
 * @param type The type.
 * @param prop The object property expression.
 * @param annot [optional] The annotations.
 * @return Axiom, or NULL on error.
 *
 * @public @memberof CowlObjPropCharAxiom
 */
COWL_RETAINED
COWL_INLINE
CowlObjPropCharAxiom *
cowl_obj_prop_char_axiom(CowlCharAxiomType type, CowlAnyObjPropExp *prop, CowlVector *annot) {
    if (!cowl_enum_value_is_valid(CAT, type)) return NULL;
    CowlObjectType t = (CowlObjectType)(COWL_OT_A_FUNC_OBJ_PROP + (CowlObjectType)type);
    return (CowlObjPropCharAxiom *)cowl_get_impl_1_annot(t, prop, annot);
}

/**
 * Gets the type of the specified object property characteristic axiom.
 *
 * @param axiom The axiom.
 * @return The type.
 *
 * @public @memberof CowlObjPropCharAxiom
 */
COWL_PURE
COWL_INLINE
CowlCharAxiomType cowl_obj_prop_char_axiom_get_type(CowlObjPropCharAxiom *axiom) {
    return (CowlCharAxiomType)(cowl_get_type(axiom) - COWL_OT_A_FUNC_OBJ_PROP);
}

/**
 * Gets the object property expression of the specified characteristic axiom.
 *
 * @param axiom The axiom.
 * @return The object property expression.
 *
 * @public @memberof CowlObjPropCharAxiom
 */
COWL_PURE
COWL_INLINE
CowlObjPropExp *cowl_obj_prop_char_axiom_get_prop(CowlObjPropCharAxiom *axiom) {
    return (CowlObjPropExp *)cowl_get_field(axiom, 0);
}

/**
 * Gets the annotations of the specified axiom.
 *
 * @param axiom The axiom.
 * @return The annotations.
 *
 * @public @memberof CowlObjPropCharAxiom
 */
COWL_PURE
COWL_INLINE
CowlVector *cowl_obj_prop_char_axiom_get_annot(CowlObjPropCharAxiom *axiom) {
    return (CowlVector *)cowl_get_opt_field(axiom);
}

COWL_END_DECLS

#endif // COWL_OBJ_PROP_CHAR_AXIOM_H
