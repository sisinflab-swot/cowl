/**
 * Declares CowlObjPropDomainAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
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
/// @endcond

/**
 * Represents an [ObjectPropertyDomain] axiom in the OWL 2 specification.
 *
 * [ObjectPropertyDomain]: https://www.w3.org/TR/owl2-syntax/#Object_Property_Domain
 *
 * @superstruct{CowlAxiom}
 * @struct CowlObjPropDomainAxiom
 */
cowl_struct_decl(CowlObjPropDomainAxiom);

/**
 * @defgroup CowlObjPropDomainAxiom CowlObjPropDomainAxiom API
 * @{
 */

/**
 * Returns an object property domain axiom.
 *
 * @param prop The object property.
 * @param domain Domain of the object property.
 * @param annot @type{optional} The annotations.
 * @return Axiom, or NULL on error.
 */
COWL_RETAINED
COWL_INLINE
CowlObjPropDomainAxiom *
cowl_obj_prop_domain_axiom(CowlAnyObjPropExp *prop, CowlAnyClsExp *domain, CowlVector *annot) {
    return (CowlObjPropDomainAxiom *)cowl_get_impl_2_annot(COWL_OT_A_OBJ_PROP_DOMAIN, prop, domain,
                                                           annot);
}

/**
 * Gets the object property.
 *
 * @param axiom The axiom.
 * @return The object property.
 */
COWL_PURE
COWL_INLINE
CowlObjPropExp *cowl_obj_prop_domain_axiom_get_prop(CowlObjPropDomainAxiom *axiom) {
    return (CowlObjPropExp *)cowl_get_field(axiom, 0);
}

/**
 * Gets the domain of the object property.
 *
 * @param axiom The axiom.
 * @return Domain of the object property.
 */
COWL_PURE
COWL_INLINE
CowlClsExp *cowl_obj_prop_domain_axiom_get_domain(CowlObjPropDomainAxiom *axiom) {
    return (CowlClsExp *)cowl_get_field(axiom, 1);
}

/// @}

COWL_END_DECLS

#endif // COWL_OBJ_PROP_DOMAIN_AXIOM_H
