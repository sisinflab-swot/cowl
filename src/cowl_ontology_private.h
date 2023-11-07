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

#include "cowl_axiom_type.h"
#include "cowl_object_private.h"
#include "cowl_ontology.h"
#include "cowl_ontology_id.h"
#include "cowl_table.h"
#include "cowl_vector.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlSymTable);

struct CowlOntology {
    CowlObject super;
    CowlOntologyId id;
    CowlManager *manager;
    CowlSymTable *st;
    CowlTable *imports;
    CowlVector *annot;
    CowlVector *axioms_by_type[COWL_AT_COUNT];
    UHash(CowlObjectTable) refs[COWL_PT_COUNT];
};

CowlOntology *cowl_ontology(CowlManager *manager);
void cowl_ontology_free(CowlOntology *ontology);
cowl_ret cowl_ontology_finalize(CowlOntology *onto);
COWL_PURE bool cowl_ontology_equals(CowlOntology *lhs, CowlOntology *rhs);
COWL_PURE ulib_uint cowl_ontology_hash(CowlOntology *onto);

COWL_END_DECLS

#endif // COWL_ONTOLOGY_PRIVATE_H
