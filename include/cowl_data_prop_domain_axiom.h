/**
 * Declares CowlDataPropDomainAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_DATA_PROP_DOMAIN_AXIOM_H
#define COWL_DATA_PROP_DOMAIN_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlClsExp);
cowl_struct_decl(CowlDataPropExp);
cowl_vector_decl(CowlObjectPtr, CowlObjectVec);
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
COWL_PUBLIC
CowlDataPropDomainAxiom* cowl_data_prop_domain_axiom_get(CowlDataPropExp *prop, CowlClsExp *domain,
                                                         CowlObjectVec *annot);

/**
 * Retains the specified axiom.
 *
 * @param axiom The axiom.
 * @return Retained axiom.
 *
 * @public @memberof CowlDataPropDomainAxiom
 */
COWL_PUBLIC
CowlDataPropDomainAxiom* cowl_data_prop_domain_axiom_retain(CowlDataPropDomainAxiom *axiom);

/**
 * Releases the specified axiom.
 *
 * @param axiom The axiom.
 *
 * @public @memberof CowlDataPropDomainAxiom
 */
COWL_PUBLIC
void cowl_data_prop_domain_axiom_release(CowlDataPropDomainAxiom *axiom);

/**
 * Gets the data property.
 *
 * @param axiom The axiom.
 * @return The data property.
 *
 * @public @memberof CowlDataPropDomainAxiom
 */
COWL_PUBLIC
CowlDataPropExp* cowl_data_prop_domain_axiom_get_prop(CowlDataPropDomainAxiom *axiom);

/**
 * Gets the domain of the data property.
 *
 * @param axiom The axiom.
 * @return Domain of the data property.
 *
 * @public @memberof CowlDataPropDomainAxiom
 */
COWL_PUBLIC
CowlClsExp* cowl_data_prop_domain_axiom_get_domain(CowlDataPropDomainAxiom *axiom);

/**
 * Gets the annotations of the specified axiom.
 *
 * @param axiom The axiom.
 * @return The annotations.
 *
 * @public @memberof CowlDataPropDomainAxiom
 */
COWL_PUBLIC
CowlObjectVec* cowl_data_prop_domain_axiom_get_annot(CowlDataPropDomainAxiom *axiom);

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
COWL_PUBLIC
CowlString* cowl_data_prop_domain_axiom_to_string(CowlDataPropDomainAxiom *axiom);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlDataPropDomainAxiom
 */
COWL_PUBLIC
bool cowl_data_prop_domain_axiom_equals(CowlDataPropDomainAxiom *lhs, CowlDataPropDomainAxiom *rhs);

/**
 * Hash function.
 *
 * @param axiom The axiom.
 * @return The hash value.
 *
 * @public @memberof CowlDataPropDomainAxiom
 */
COWL_PUBLIC
ulib_uint cowl_data_prop_domain_axiom_hash(CowlDataPropDomainAxiom *axiom);

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
COWL_PUBLIC
bool cowl_data_prop_domain_axiom_iterate_primitives(CowlDataPropDomainAxiom *axiom,
                                                    CowlPrimitiveFlags flags, CowlIterator *iter);

COWL_END_DECLS

#endif // COWL_DATA_PROP_DOMAIN_AXIOM_H
