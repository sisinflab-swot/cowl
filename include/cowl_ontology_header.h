/**
 * Defines CowlOntologyHeader.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2023 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ONTOLOGY_HEADER_H
#define COWL_ONTOLOGY_HEADER_H

#include "cowl_attrs.h"
#include "cowl_utils.h"
#include "ulib.h"
#include <stddef.h>

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlIRI);
uvec_decl(CowlObjectPtr);
/// @endcond

/// Models an ontology header.
typedef struct CowlOntologyHeader {

    /// Ontology IRI.
    CowlIRI *iri;

    /// Ontology version.
    CowlIRI *version;

    /// Import IRIs.
    UVec(CowlObjectPtr) const *imports;

    /// Annotations.
    UVec(CowlObjectPtr) const *annotations;

} CowlOntologyHeader;

/**
 * @defgroup CowlOntologyHeader CowlOntologyHeader API
 * @{
 */

/**
 * Returns an empty ontology header.
 *
 * @return Empty ontology header.
 */
COWL_CONST
COWL_INLINE
CowlOntologyHeader cowl_ontology_header_empty(void) {
    CowlOntologyHeader header = { NULL, NULL, NULL, NULL };
    return header;
}

/// @}

COWL_END_DECLS

#endif // COWL_ONTOLOGY_HEADER_H
