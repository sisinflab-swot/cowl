/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ONTOLOGY_PRIVATE_H
#define COWL_ONTOLOGY_PRIVATE_H

#include "cowl_ontology.h"
#include "cowl_axiom_type.h"
#include "cowl_object_private.h"
#include "cowl_set.h"
#include "cowl_ontology_id.h"
#include "cowl_vector.h"

COWL_BEGIN_DECLS

struct CowlOntology {
    CowlObject super;
    CowlVector *annotations;
    CowlVector *imports;
    CowlVector *axioms_by_type[COWL_AT_COUNT];
    UHash(CowlObjectTable) annot_prop_refs;
    UHash(CowlObjectTable) class_refs;
    UHash(CowlObjectTable) data_prop_refs;
    UHash(CowlObjectTable) datatype_refs;
    UHash(CowlObjectTable) obj_prop_refs;
    UHash(CowlObjectTable) named_ind_refs;
    UHash(CowlObjectTable) anon_ind_refs;
    CowlOntologyId id;
};

CowlOntology* cowl_ontology_get(void);
void cowl_ontology_set_iri(CowlOntology *onto, CowlIRI *iri);
void cowl_ontology_set_version(CowlOntology *onto, CowlIRI *version);
cowl_ret cowl_ontology_add_annot(CowlOntology *onto, CowlAnnotation *annot);
cowl_ret cowl_ontology_add_import(CowlOntology *onto, CowlOntology *import);
cowl_ret cowl_ontology_add_axiom(CowlOntology *onto, CowlAxiom *axiom);
cowl_ret cowl_ontology_finalize(CowlOntology *onto);

COWL_END_DECLS

#endif // COWL_ONTOLOGY_PRIVATE_H
