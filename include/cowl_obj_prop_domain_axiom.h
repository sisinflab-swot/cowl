/**
 * Declares CowlObjPropDomainAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_OBJ_PROP_DOMAIN_AXIOM_H
#define COWL_OBJ_PROP_DOMAIN_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlClsExp);
cowl_struct_decl(CowlObjPropExp);
cowl_vector_decl(CowlAnnotationPtr, CowlAnnotationVec);
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
 * @param annot The annotations.
 * @return Retained axiom.
 *
 * @public @memberof CowlObjPropDomainAxiom
 */
COWL_PUBLIC
CowlObjPropDomainAxiom* cowl_obj_prop_domain_axiom_get(CowlObjPropExp *prop, CowlClsExp *domain,
                                                       CowlAnnotationVec *annot);

/**
 * Retains the specified axiom.
 *
 * @param axiom The axiom.
 * @return Retained axiom.
 *
 * @public @memberof CowlObjPropDomainAxiom
 */
COWL_PUBLIC
CowlObjPropDomainAxiom* cowl_obj_prop_domain_axiom_retain(CowlObjPropDomainAxiom *axiom);

/**
 * Releases the specified axiom.
 *
 * @param axiom The axiom.
 *
 * @public @memberof CowlObjPropDomainAxiom
 */
COWL_PUBLIC
void cowl_obj_prop_domain_axiom_release(CowlObjPropDomainAxiom *axiom);

/**
 * Gets the object property.
 *
 * @param axiom The axiom.
 * @return The object property.
 *
 * @public @memberof CowlObjPropDomainAxiom
 */
COWL_PUBLIC
CowlObjPropExp* cowl_obj_prop_domain_axiom_get_prop(CowlObjPropDomainAxiom *axiom);

/**
 * Gets the domain of the object property.
 *
 * @param axiom The axiom.
 * @return Domain of the object property.
 *
 * @public @memberof CowlObjPropDomainAxiom
 */
COWL_PUBLIC
CowlClsExp* cowl_obj_prop_domain_axiom_get_domain(CowlObjPropDomainAxiom *axiom);

/**
 * Gets the annotations of the specified axiom.
 *
 * @param axiom The axiom.
 * @return The annotations.
 *
 * @public @memberof CowlObjPropDomainAxiom
 */
COWL_PUBLIC
CowlAnnotationVec* cowl_obj_prop_domain_axiom_get_annot(CowlObjPropDomainAxiom *axiom);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlObjPropDomainAxiom
 */
COWL_PUBLIC
bool cowl_obj_prop_domain_axiom_equals(CowlObjPropDomainAxiom *lhs, CowlObjPropDomainAxiom *rhs);

/**
 * Hash function.
 *
 * @param axiom The axiom.
 * @return The hash value.
 *
 * @public @memberof CowlObjPropDomainAxiom
 */
COWL_PUBLIC
cowl_uint_t cowl_obj_prop_domain_axiom_hash(CowlObjPropDomainAxiom *axiom);

/**
 * Iterates over the signature of the specified axiom.
 *
 * @param axiom The axiom.
 * @param iter The entity iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlObjPropDomainAxiom
 */
COWL_PUBLIC
bool cowl_obj_prop_domain_axiom_iterate_signature(CowlObjPropDomainAxiom *axiom,
                                                  CowlEntityIterator *iter);

COWL_END_DECLS

#endif // COWL_OBJ_PROP_DOMAIN_AXIOM_H
