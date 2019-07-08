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

cowl_struct(CowlOntologyID) {
    CowlIRI *onto_iri;
    CowlIRI *version_iri;
};

CowlOntologyID* cowl_ontology_id_alloc(CowlIRI *onto_iri, CowlIRI *version_iri);
CowlOntologyID* cowl_ontology_id_alloc_anonymous(void);
void cowl_ontology_id_free(CowlOntologyID *id);

COWL_END_DECLS

#endif // COWL_ONTOLOGY_ID_PRIVATE_H
