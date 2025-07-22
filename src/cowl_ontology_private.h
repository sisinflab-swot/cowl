/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ONTOLOGY_PRIVATE_H
#define COWL_ONTOLOGY_PRIVATE_H

#include "cowl_attrs.h"
#include "cowl_axiom_type.h"
#include "cowl_object_private.h"
#include "cowl_ontology.h" // IWYU pragma: export
#include "cowl_primitive_type.h"
#include "cowl_ret.h"
#include "cowl_table.h" // IWYU pragma: keep, needed for UHash(CowlObjectTable)
#include "cowl_vector.h"
#include "ulib.h"

COWL_BEGIN_DECLS

struct CowlOntology {
    CowlObject super;
    CowlIRI *iri;
    CowlIRI *version;
    CowlManager *manager;
    CowlPrefixMap *pm;
    CowlVector *imports;
    CowlVector *annot;
    CowlVector *axioms_by_type[COWL_AT_COUNT];
    UHash(CowlObjectTable) refs[COWL_PT_COUNT];
};

CowlOntology *cowl_ontology(CowlManager *manager);
void cowl_ontology_free(CowlOntology *onto);
cowl_ret cowl_ontology_finalize(CowlOntology *onto);

COWL_END_DECLS

#endif // COWL_ONTOLOGY_PRIVATE_H
