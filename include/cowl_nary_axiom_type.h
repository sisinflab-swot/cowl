/**
 * Defines the #CowlNAryAxiomType enumeration.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_NARY_AXIOM_TYPE_H
#define COWL_NARY_AXIOM_TYPE_H

#include "cowl_compat.h"

COWL_BEGIN_DECLS

/**
 * Represents the type of CowlNAryClsAxiom, CowlNAryObjPropAxiom,
 * CowlNAryDataPropAxiom and CowlNAryIndAxiom.
 */
typedef enum CowlNAryAxiomType {

/// @name Classes and Properties

    /// Equivalence.
    COWL_NAT_EQUIV,

    /// Disjointness.
    COWL_NAT_DISJ,

/// @name Markers

    /// Number of enum values.
    COWL_NAT_COUNT,

    /// First enum value.
    COWL_NAT_FIRST = 0,

/// @name Individuals

    /// Same individuals.
    COWL_NAT_SAME = COWL_NAT_EQUIV,

    /// Different individuals.
    COWL_NAT_DIFF = COWL_NAT_DISJ

} CowlNAryAxiomType;

COWL_END_DECLS

#endif // COWL_NARY_AXIOM_TYPE_H
