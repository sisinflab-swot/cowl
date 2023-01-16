/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_MANAGER_TESTS_H
#define COWL_MANAGER_TESTS_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

bool cowl_test_manager_lifecycle(void);
bool cowl_test_manager_read_ontology(void);
bool cowl_test_manager_write_ontology(void);
bool cowl_test_manager_edit_ontology(void);

#define COWL_MANAGER_TESTS                                                                         \
    cowl_test_manager_lifecycle, cowl_test_manager_read_ontology,                                  \
        cowl_test_manager_write_ontology, cowl_test_manager_edit_ontology

COWL_END_DECLS

#endif // COWL_MANAGER_TESTS_H
