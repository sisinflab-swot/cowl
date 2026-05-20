/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2025 SisInf Lab, Polytechnic University of Bari
 * @copyright <https://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ONTOLOGY_HEADER_H
#define COWL_ONTOLOGY_HEADER_H

#include "cowl_attrs.h"
#include "cowl_utils.h"
#include "ulib.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlPrefixMap);
cowl_struct_decl(CowlIRI);
uvec_decl(CowlObjectPtr);
/// @endcond

/// Ontology header.
typedef struct CowlOntologyHeader {

    /// Prefix map.
    CowlPrefixMap *pm;

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
    CowlOntologyHeader header = ulib_zero_init;
    return header;
}

/// @}

COWL_END_DECLS

#endif // COWL_ONTOLOGY_HEADER_H
