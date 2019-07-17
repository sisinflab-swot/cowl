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

#define COWL_ONTOLOGY_TESTS                                                                         \
    cowl_test_ontology_get_id,                                                                      \
    cowl_test_ontology_axiom_count,                                                                 \
    cowl_test_ontology_imports_count,                                                               \
    cowl_test_ontology_axiom_count_for_type

COWL_END_DECLS

#endif // COWL_ONTOLOGY_TESTS_H
