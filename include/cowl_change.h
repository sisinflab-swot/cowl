/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2025 SisInf Lab, Polytechnic University of Bari
 * @copyright <https://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_CHANGE_H
#define COWL_CHANGE_H

#include "cowl_attrs.h"
#include "cowl_ret.h"
#include "cowl_utils.h"
#include "ulib.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlOntology);
cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlString);
/// @endcond

/**
 * @defgroup CowlChange_types CowlChange types
 * @{
 */

/// Prefix to namespace mapping.
typedef struct CowlPrefixDecl {

    /// Prefix.
    CowlString *prefix;

    /// Namespace.
    CowlString *ns;

} CowlPrefixDecl;

/// Ontology part.
typedef enum cowl_part {

    /// @type{CowlPrefixDecl} - prefix declaration.
    COWL_PART_PREFIX_DECL,

    /// @type{CowlIRI} - ontology IRI.
    COWL_PART_IRI,

    /// @type{CowlIRI} - version IRI.
    COWL_PART_VERSION,

    /// @type{CowlIRI} - import IRI.
    COWL_PART_IMPORT,

    /// @type{CowlAnnotation} - Annotation.
    COWL_PART_ANNOTATION,

    /// @type{CowlAxiom} - Axiom.
    COWL_PART_AXIOM,

} cowl_part;

/// Change type.
typedef enum cowl_change_type {

    /// Change is an addition.
    COWL_CHANGE_ADD,

    /// Change is a removal.
    COWL_CHANGE_REMOVE,

} cowl_change_type;

/// A change in the ontology.
typedef struct CowlChange {

    /// Change type.
    cowl_change_type type;

    /// Part of the ontology that changed.
    cowl_part part;

    /// Change value.
    void *value;

} CowlChange;

/// @}

/**
 * @defgroup CowlChange_api CowlChange API
 * @{
 */

/**
 * Initializes a change object.
 *
 * @param type Change type.
 * @param part Part of the ontology that changed.
 * @param value Change value.
 * @return Change object.
 */
COWL_INLINE
CowlChange cowl_change(cowl_change_type type, cowl_part part, void *value) {
    CowlChange change = ulib_zero_init;
    change.type = type;
    change.part = part;
    change.value = value;
    return change;
}

/**
 * Initializes a change object for an addition.
 *
 * @param part Part of the ontology that changed.
 * @param value Change value.
 * @return Change object.
 */
COWL_INLINE
CowlChange cowl_change_add(cowl_part part, void *value) {
    return cowl_change(COWL_CHANGE_ADD, part, value);
}

/**
 * Initializes a change object for a removal.
 *
 * @param part Part of the ontology that changed.
 * @param value Change value.
 * @return Change object.
 */
COWL_INLINE
CowlChange cowl_change_remove(cowl_part part, void *value) {
    return cowl_change(COWL_CHANGE_REMOVE, part, value);
}

/// @}

COWL_END_DECLS

#endif // COWL_CHANGE_H
