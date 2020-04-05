/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ONTOLOGY_ID_PRIVATE_H
#define COWL_ONTOLOGY_ID_PRIVATE_H

#include "cowl_ontology_id.h"

COWL_BEGIN_DECLS

#define COWL_ONTOLOGY_ID_ANONYMOUS ((CowlOntologyID){ .ontology_iri = NULL, .version_iri = NULL })

#define cowl_ontology_id_init(ONTO_IRI, VER_IRI) ((CowlOntologyID) {                                \
    .ontology_iri = (ONTO_IRI) ? cowl_iri_retain(ONTO_IRI) : NULL,                                  \
    .version_iri = (VER_IRI) ? cowl_iri_retain(VER_IRI) : NULL                                      \
})

#define cowl_ontology_id_deinit(ID) do {                                                            \
    cowl_iri_release((ID).ontology_iri);                                                            \
    cowl_iri_release((ID).version_iri);                                                             \
} while(0)

COWL_END_DECLS

#endif // COWL_ONTOLOGY_ID_PRIVATE_H
