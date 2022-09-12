/**
 * Declares CowlObjPropDomainAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_OBJ_PROP_DOMAIN_AXIOM_H
#define COWL_OBJ_PROP_DOMAIN_AXIOM_H

#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlClsExp);
cowl_struct_decl(CowlObjPropExp);
cowl_struct_decl(CowlVector);
cowl_struct_decl(CowlObjPropDomainAxiom);
/// @endcond

/**
 * Represents an [ObjectPropertyDomain] axiom in the OWL 2 specification.
 *
 * [ObjectPropertyDomain]: https://www.w3.org/TR/owl2-syntax/#Object_Property_Domain
 *
 * @struct CowlObjPropDomainAxiom
 * @extends CowlAxiom
 */

/**
 * Returns a retained object property domain axiom.
 *
 * @param prop The object property.
 * @param domain Domain of the object property.
 * @param annot [optional] The annotations.
 * @return Retained axiom, or NULL on error.
 *
 * @public @memberof CowlObjPropDomainAxiom
 */
COWL_INLINE
CowlObjPropDomainAxiom* cowl_obj_prop_domain_axiom(CowlObjPropExp *prop, CowlClsExp *domain,
                                                   CowlVector *annot) {
    return (CowlObjPropDomainAxiom *)cowl_get_impl_2_opt(COWL_OT_A_OBJ_PROP_DOMAIN,
                                                         prop, domain, annot);
}

/**
 * Retains the specified axiom.
 *
 * @param axiom The axiom.
 * @return Retained axiom.
 *
 * @public @memberof CowlObjPropDomainAxiom
 */
COWL_INLINE
CowlObjPropDomainAxiom* cowl_obj_prop_domain_axiom_retain(CowlObjPropDomainAxiom *axiom) {
    return (CowlObjPropDomainAxiom *)cowl_retain(axiom);
}

/**
 * Releases the specified axiom.
 *
 * @param axiom The axiom.
 *
 * @public @memberof CowlObjPropDomainAxiom
 */
COWL_INLINE
void cowl_obj_prop_domain_axiom_release(CowlObjPropDomainAxiom *axiom) {
    cowl_release_impl(axiom);
}

/**
 * Gets the object property.
 *
 * @param axiom The axiom.
 * @return The object property.
 *
 * @public @memberof CowlObjPropDomainAxiom
 */
COWL_INLINE
CowlObjPropExp* cowl_obj_prop_domain_axiom_get_prop(CowlObjPropDomainAxiom *axiom) {
    return (CowlObjPropExp *)cowl_get_field(axiom, 0);
}

/**
 * Gets the domain of the object property.
 *
 * @param axiom The axiom.
 * @return Domain of the object property.
 *
 * @public @memberof CowlObjPropDomainAxiom
 */
COWL_INLINE
CowlClsExp* cowl_obj_prop_domain_axiom_get_domain(CowlObjPropDomainAxiom *axiom) {
    return (CowlClsExp *)cowl_get_field(axiom, 1);
}

/**
 * Gets the annotations of the specified axiom.
 *
 * @param axiom The axiom.
 * @return The annotations.
 *
 * @public @memberof CowlObjPropDomainAxiom
 */
COWL_INLINE
CowlVector* cowl_obj_prop_domain_axiom_get_annot(CowlObjPropDomainAxiom *axiom) {
    return (CowlVector *)cowl_get_opt_field(axiom);
}

/**
 * Returns the string representation of the specified axiom.
 *
 * @param axiom The axiom.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlObjPropDomainAxiom
 */
COWL_INLINE
CowlString* cowl_obj_prop_domain_axiom_to_string(CowlObjPropDomainAxiom *axiom) {
    return cowl_to_string(axiom);
}

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlObjPropDomainAxiom
 */
COWL_INLINE
bool cowl_obj_prop_domain_axiom_equals(CowlObjPropDomainAxiom *lhs, CowlObjPropDomainAxiom *rhs) {
    return cowl_equals_impl(lhs, rhs);
}

/**
 * Hash function.
 *
 * @param axiom The axiom.
 * @return The hash value.
 *
 * @public @memberof CowlObjPropDomainAxiom
 */
COWL_INLINE
ulib_uint cowl_obj_prop_domain_axiom_hash(CowlObjPropDomainAxiom *axiom) {
    return cowl_hash_impl(axiom);
}

/**
 * Iterates over the primitives referenced by the specified axiom.
 *
 * @param axiom The axiom.
 * @param flags Iteration flags.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlObjPropDomainAxiom
 */
COWL_INLINE
bool cowl_obj_prop_domain_axiom_iterate_primitives(CowlObjPropDomainAxiom *axiom,
                                                   CowlPrimitiveFlags flags, CowlIterator *iter) {
    return cowl_iterate_primitives_impl(axiom, flags, iter);
}

COWL_END_DECLS

#endif // COWL_OBJ_PROP_DOMAIN_AXIOM_H
