/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ONTOLOGY_TESTS_H
#define COWL_ONTOLOGY_TESTS_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

bool cowl_test_ontology_get_id(void);
bool cowl_test_ontology_axiom_count(void);
bool cowl_test_ontology_imports_count(void);
bool cowl_test_ontology_axiom_count_for_type(void);
bool cowl_test_ontology_class_count(void);
bool cowl_test_ontology_datatypes_count(void);
bool cowl_test_ontology_obj_props_count(void);
bool cowl_test_ontology_data_props_count(void);
bool cowl_test_ontology_annot_props_count(void);
bool cowl_test_ontology_named_inds_count(void);
bool cowl_test_ontology_anon_inds_count(void);

#define COWL_ONTOLOGY_TESTS                                                                         \
    cowl_test_ontology_get_id,                                                                      \
    cowl_test_ontology_axiom_count,                                                                 \
    cowl_test_ontology_imports_count,                                                               \
    cowl_test_ontology_axiom_count_for_type,                                                        \
    cowl_test_ontology_class_count,                                                                 \
    cowl_test_ontology_datatypes_count,                                                             \
    cowl_test_ontology_obj_props_count,                                                             \
    cowl_test_ontology_data_props_count,                                                            \
    cowl_test_ontology_annot_props_count,                                                           \
    cowl_test_ontology_named_inds_count,                                                            \
    cowl_test_ontology_anon_inds_count

COWL_END_DECLS

#endif // COWL_ONTOLOGY_TESTS_H
