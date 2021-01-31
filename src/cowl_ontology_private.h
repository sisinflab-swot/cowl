/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ONTOLOGY_PRIVATE_H
#define COWL_ONTOLOGY_PRIVATE_H

#include "cowl_ontology.h"
#include "cowl_axiom_type.h"
#include "cowl_object_private.h"
#include "cowl_ontology_id_private.h"

COWL_BEGIN_DECLS

typedef uvec_struct(CowlObjectPtr) UVec(CowlObjectPtr);
typedef uhash_struct(CowlObjectTable) UHash(CowlObjectTable);

cowl_struct(CowlOntology) {
    CowlObject super;
    UVec(CowlObjectPtr) *imports;
    UVec(CowlObjectPtr) *annotations;
    UHash(CowlObjectTable) *axioms_by_type[COWL_AT_COUNT];
    UHash(CowlObjectTable) *annot_prop_refs;
    UHash(CowlObjectTable) *class_refs;
    UHash(CowlObjectTable) *data_prop_refs;
    UHash(CowlObjectTable) *datatype_refs;
    UHash(CowlObjectTable) *obj_prop_refs;
    UHash(CowlObjectTable) *named_ind_refs;
    UHash(CowlObjectTable) *anon_ind_refs;
    CowlOntologyID id;
};

#define COWL_ONTOLOGY_INIT ((CowlOntology) {                                                        \
    .super = COWL_OBJECT_INIT(COWL_OT_ONTOLOGY),                                                    \
    .id = COWL_ONTOLOGY_ID_ANONYMOUS,                                                               \
    .imports = NULL,                                                                                \
    .annotations = NULL,                                                                            \
    .annot_prop_refs = cowl_annot_prop_map_alloc(),                                                 \
    .class_refs = cowl_class_map_alloc(),                                                           \
    .data_prop_refs = cowl_data_prop_map_alloc(),                                                   \
    .datatype_refs = cowl_datatype_map_alloc(),                                                     \
    .obj_prop_refs = cowl_obj_prop_map_alloc(),                                                     \
    .named_ind_refs = cowl_named_ind_map_alloc(),                                                   \
    .anon_ind_refs = cowl_anon_ind_map_alloc(),                                                     \
})

cowl_struct(CowlOntology)* cowl_ontology_get(void);

void cowl_ontology_set_id(CowlOntology *onto, CowlOntologyID id);
cowl_ret cowl_ontology_set_imports(CowlOntology *onto, UVec(CowlObjectPtr) *imports);
cowl_ret cowl_ontology_set_annot(CowlOntology *onto, UVec(CowlObjectPtr) *annot);
cowl_ret cowl_ontology_add_axiom(CowlOntology *onto, CowlAxiom *axiom);

COWL_END_DECLS

#endif // COWL_ONTOLOGY_PRIVATE_H
