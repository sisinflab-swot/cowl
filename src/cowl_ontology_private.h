/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <https://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 */

#ifndef COWL_ONTOLOGY_PRIVATE_H
#define COWL_ONTOLOGY_PRIVATE_H

#include "cowl_attrs.h"
#include "cowl_axiom_type.h"
#include "cowl_object_private.h"
#include "cowl_ontology.h" // IWYU pragma: export
#include "cowl_primitive_type.h"
#include "cowl_ret.h"
#include "cowl_table.h" // IWYU pragma: keep, needed for UHash(CowlObjectPtr)
#include "cowl_vector.h"
#include "ulib.h"

COWL_BEGIN_DECLS

struct CowlOntology {
    CowlObject super;
    CowlIRI *iri;
    CowlIRI *version;
    CowlPrefixMap *pm;
    CowlVector *imports;
    CowlVector *annot;
    CowlVector *axioms_by_type[COWL_AT_COUNT];
    UHash(CowlObjectPtr) refs[COWL_PT_COUNT];
};

void cowl_ontology_free(CowlOntology *onto);
cowl_ret cowl_ontology_finalize(CowlOntology *onto);
void cowl_ontology_disable_indexing(CowlOntology *onto);

COWL_END_DECLS

#endif // COWL_ONTOLOGY_PRIVATE_H
