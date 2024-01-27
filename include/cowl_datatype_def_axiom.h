/**
 * Declares CowlDatatypeDefAxiom and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_DATATYPE_DEF_AXIOM_H
#define COWL_DATATYPE_DEF_AXIOM_H

#include "cowl_object.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlDataRange);
cowl_struct_decl(CowlDatatype);
cowl_struct_decl(CowlVector);
/// @endcond

/**
 * Represents a [DatatypeDefinition] axiom in the OWL 2 specification.
 *
 * [DatatypeDefinition]: https://www.w3.org/TR/owl2-syntax/#Datatype_Definitions
 *
 * @superstruct{CowlAxiom}
 * @struct CowlDatatypeDefAxiom
 */
cowl_struct_decl(CowlDatatypeDefAxiom);

/**
 * @defgroup CowlDatatypeDefAxiom CowlDatatypeDefAxiom API
 * @{
 */

/**
 * Returns a datatype definition axiom.
 *
 * @param dt The defined datatype.
 * @param range Range of the defined datatype.
 * @param annot @type{optional} The annotations.
 * @return Axiom, or NULL on error.
 */
COWL_RETAINED
COWL_INLINE
CowlDatatypeDefAxiom *
cowl_datatype_def_axiom(CowlDatatype *dt, CowlAnyDataRange *range, CowlVector *annot) {
    return (CowlDatatypeDefAxiom *)cowl_get_impl_2_annot(COWL_OT_A_DATATYPE_DEF, dt, range, annot);
}

/**
 * Gets the defined datatype.
 *
 * @param axiom The axiom.
 * @return The datatype.
 */
COWL_PURE
COWL_INLINE
CowlDatatype *cowl_datatype_def_axiom_get_datatype(CowlDatatypeDefAxiom *axiom) {
    return (CowlDatatype *)cowl_get_field(axiom, 0);
}

/**
 * Gets the range of the defined datatype.
 * @param axiom The axiom.
 * @return The range.
 */
COWL_PURE
COWL_INLINE
CowlDataRange *cowl_datatype_def_axiom_get_range(CowlDatatypeDefAxiom *axiom) {
    return (CowlDataRange *)cowl_get_field(axiom, 1);
}

/// @}

COWL_END_DECLS

#endif // COWL_DATATYPE_DEF_AXIOM_H
