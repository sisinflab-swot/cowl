/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ONTOLOGY_TESTS_H
#define COWL_ONTOLOGY_TESTS_H

#include "cowl_attrs.h"

COWL_BEGIN_DECLS

void cowl_test_ontology_init(void);
void cowl_test_ontology_deinit(void);

void cowl_test_ontology_get_iri_version(void);
void cowl_test_ontology_axiom_count(void);
void cowl_test_ontology_imports_count(void);
void cowl_test_ontology_axiom_count_for_type(void);
void cowl_test_ontology_axiom_count_for_types(void);
void cowl_test_ontology_primitives_count(void);
void cowl_test_ontology_axiom_count_for_primitive(void);
void cowl_test_ontology_has_primitive(void);
void cowl_test_ontology_has_axiom(void);

#define COWL_ONTOLOGY_TESTS                                                                        \
    cowl_test_ontology_init, cowl_test_ontology_get_iri_version, cowl_test_ontology_axiom_count,   \
        cowl_test_ontology_imports_count, cowl_test_ontology_axiom_count_for_type,                 \
        cowl_test_ontology_axiom_count_for_types, cowl_test_ontology_primitives_count,             \
        cowl_test_ontology_axiom_count_for_primitive, cowl_test_ontology_has_primitive,            \
        cowl_test_ontology_has_axiom, cowl_test_ontology_deinit

COWL_END_DECLS

#endif // COWL_ONTOLOGY_TESTS_H
