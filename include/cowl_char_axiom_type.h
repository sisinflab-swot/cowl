/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <https://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_CHAR_AXIOM_TYPE_H
#define COWL_CHAR_AXIOM_TYPE_H

#include "cowl_attrs.h"

COWL_BEGIN_DECLS

/// Represents the type of @type{CowlObjPropCharAxiom}.
typedef enum CowlCharAxiomType {

    /// @name Types

    /// Functional object property.
    COWL_CAT_FUNC,

    /// Inverse functional object property.
    COWL_CAT_INV_FUNC,

    /// Reflexive object property.
    COWL_CAT_REFL,

    /// Irreflexive object property.
    COWL_CAT_IRREFL,

    /// Symmetric object property.
    COWL_CAT_SYMM,

    /// Asymmetric object property.
    COWL_CAT_ASYMM,

    /// Transitive object property.
    COWL_CAT_TRANS,

    /// @name Markers

    /// Number of enum values.
    COWL_CAT_COUNT,

    /// First enum value.
    COWL_CAT_FIRST = 0

} CowlCharAxiomType;

COWL_END_DECLS

#endif // COWL_CHAR_AXIOM_TYPE_H
