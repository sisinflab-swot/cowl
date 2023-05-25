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

#include "cowl_ontology_id.h"
#include "cowl_vector.h"

COWL_BEGIN_DECLS

/// Models an ontology header.
typedef struct CowlOntologyHeader {

    /// Ontology identifier.
    CowlOntologyId id;

    /// Import IRIs.
    UVec(CowlObjectPtr) const *imports;

    /// Annotations.
    UVec(CowlObjectPtr) const *annotations;

} CowlOntologyHeader;

COWL_END_DECLS

#endif // COWL_ONTOLOGY_HEADER_H
