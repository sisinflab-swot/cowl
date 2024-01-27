/**
 * Declares CowlDataPropDomainAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_DATA_PROP_DOMAIN_AXIOM_H
#define COWL_DATA_PROP_DOMAIN_AXIOM_H

#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlClsExp);
cowl_struct_decl(CowlDataPropExp);
cowl_struct_decl(CowlVector);
/// @endcond

/**
 * Represents a [DataPropertyDomain] axiom in the OWL 2 specification.
 *
 * [DataPropertyDomain]: https://www.w3.org/TR/owl2-syntax/#Data_Property_Domain
 *
 * @superstruct{CowlAxiom}
 * @struct CowlDataPropDomainAxiom
 */
cowl_struct_decl(CowlDataPropDomainAxiom);

/**
 * @defgroup CowlDataPropDomainAxiom CowlDataPropDomainAxiom API
 * @{
 */

/**
 * Returns a data property domain axiom.
 *
 * @param prop The data property.
 * @param domain Domain of the data property.
 * @param annot @type{optional} The annotations.
 * @return Axiom, or NULL on error.
 */
COWL_RETAINED
COWL_INLINE
CowlDataPropDomainAxiom *
cowl_data_prop_domain_axiom(CowlAnyDataPropExp *prop, CowlAnyClsExp *domain, CowlVector *annot) {
    return (CowlDataPropDomainAxiom *)cowl_get_impl_2_annot(COWL_OT_A_DATA_PROP_DOMAIN, prop,
                                                            domain, annot);
}

/**
 * Gets the data property.
 *
 * @param axiom The axiom.
 * @return The data property.
 */
COWL_PURE
COWL_INLINE
CowlDataPropExp *cowl_data_prop_domain_axiom_get_prop(CowlDataPropDomainAxiom *axiom) {
    return (CowlDataPropExp *)cowl_get_field(axiom, 0);
}

/**
 * Gets the domain of the data property.
 *
 * @param axiom The axiom.
 * @return Domain of the data property.
 */
COWL_PURE
COWL_INLINE
CowlClsExp *cowl_data_prop_domain_axiom_get_domain(CowlDataPropDomainAxiom *axiom) {
    return (CowlClsExp *)cowl_get_field(axiom, 1);
}

/// @}

COWL_END_DECLS

#endif // COWL_DATA_PROP_DOMAIN_AXIOM_H
