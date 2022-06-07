/**
 * Declares CowlDataPropDomainAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_DATA_PROP_DOMAIN_AXIOM_H
#define COWL_DATA_PROP_DOMAIN_AXIOM_H

#include "cowl_object_impl.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlClsExp);
cowl_struct_decl(CowlDataPropExp);
cowl_struct_decl(CowlVector);
cowl_struct_decl(CowlDataPropDomainAxiom);
/// @endcond

/**
 * Represents a [DataPropertyDomain] axiom in the OWL 2 specification.
 *
 * [DataPropertyDomain]: https://www.w3.org/TR/owl2-syntax/#Data_Property_Domain
 *
 * @struct CowlDataPropDomainAxiom
 * @extends CowlAxiom
 */

/**
 * Returns a retained data property domain axiom.
 *
 * @param prop The data property.
 * @param domain Domain of the data property.
 * @param annot [optional] The annotations.
 * @return Retained axiom, or NULL on error.
 *
 * @public @memberof CowlDataPropDomainAxiom
 */
COWL_INLINE
CowlDataPropDomainAxiom* cowl_data_prop_domain_axiom_get(CowlDataPropExp *prop, CowlClsExp *domain,
                                                         CowlVector *annot) {
    return cowl_get_impl_2(COWL_OT_A_DATA_PROP_DOMAIN, prop, domain, annot);
}

/**
 * Retains the specified axiom.
 *
 * @param axiom The axiom.
 * @return Retained axiom.
 *
 * @public @memberof CowlDataPropDomainAxiom
 */
COWL_INLINE
CowlDataPropDomainAxiom* cowl_data_prop_domain_axiom_retain(CowlDataPropDomainAxiom *axiom) {
    return cowl_retain(axiom);
}

/**
 * Releases the specified axiom.
 *
 * @param axiom The axiom.
 *
 * @public @memberof CowlDataPropDomainAxiom
 */
COWL_INLINE
void cowl_data_prop_domain_axiom_release(CowlDataPropDomainAxiom *axiom) {
    cowl_release_impl(axiom);
}

/**
 * Gets the data property.
 *
 * @param axiom The axiom.
 * @return The data property.
 *
 * @public @memberof CowlDataPropDomainAxiom
 */
COWL_INLINE
CowlDataPropExp* cowl_data_prop_domain_axiom_get_prop(CowlDataPropDomainAxiom *axiom) {
    return cowl_get_field(axiom, 0);
}

/**
 * Gets the domain of the data property.
 *
 * @param axiom The axiom.
 * @return Domain of the data property.
 *
 * @public @memberof CowlDataPropDomainAxiom
 */
COWL_INLINE
CowlClsExp* cowl_data_prop_domain_axiom_get_domain(CowlDataPropDomainAxiom *axiom) {
    return cowl_get_field(axiom, 1);
}

/**
 * Gets the annotations of the specified axiom.
 *
 * @param axiom The axiom.
 * @return The annotations.
 *
 * @public @memberof CowlDataPropDomainAxiom
 */
COWL_INLINE
CowlVector* cowl_data_prop_domain_axiom_get_annot(CowlDataPropDomainAxiom *axiom) {
    return cowl_get_opt_field(axiom);
}

/**
 * Returns the string representation of the specified axiom.
 *
 * @param axiom The axiom.
 * @return String representation, or NULL on error.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlDataPropDomainAxiom
 */
COWL_INLINE
CowlString* cowl_data_prop_domain_axiom_to_string(CowlDataPropDomainAxiom *axiom) {
    return cowl_to_string_impl(axiom);
}

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlDataPropDomainAxiom
 */
COWL_INLINE
bool cowl_data_prop_domain_axiom_equals(CowlDataPropDomainAxiom *lhs, CowlDataPropDomainAxiom *rhs) {
    return cowl_equals_impl(lhs, rhs);
}

/**
 * Hash function.
 *
 * @param axiom The axiom.
 * @return The hash value.
 *
 * @public @memberof CowlDataPropDomainAxiom
 */
COWL_INLINE
ulib_uint cowl_data_prop_domain_axiom_hash(CowlDataPropDomainAxiom *axiom) {
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
 * @public @memberof CowlDataPropDomainAxiom
 */
COWL_INLINE
bool cowl_data_prop_domain_axiom_iterate_primitives(CowlDataPropDomainAxiom *axiom,
                                                    CowlPrimitiveFlags flags, CowlIterator *iter) {
    return cowl_iterate_primitives_impl(axiom, flags, iter);
}

COWL_END_DECLS

#endif // COWL_DATA_PROP_DOMAIN_AXIOM_H
