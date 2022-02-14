/**
 * Defines the #CowlCharAxiomType enumeration.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_CHAR_AXIOM_TYPE_H
#define COWL_CHAR_AXIOM_TYPE_H

#include "cowl_compat.h"

COWL_BEGIN_DECLS

/// Represents the type of CowlObjPropCharAxiom.
typedef enum CowlCharAxiomType {

/// @name Types

    /// Functional object property.
    COWL_CAT_FUNC,

    /// Inverse functional object property.
    COWL_CAT_INV_FUNC,

    /// Symmetric object property.
    COWL_CAT_SYMM,

    /// Asymmetric object property.
    COWL_CAT_ASYMM,

    /// Transitive object property.
    COWL_CAT_TRANS,

    /// Reflexive object property.
    COWL_CAT_REFL,

    /// Irreflexive object property.
    COWL_CAT_IRREFL,

/// @name Markers

    /// Number of enum values.
    COWL_CAT_COUNT,

    /// First enum value.
    COWL_CAT_FIRST = 0

} CowlCharAxiomType;

COWL_END_DECLS

#endif // COWL_CHAR_AXIOM_TYPE_H
