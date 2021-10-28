/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_READER_TESTS_H
#define COWL_READER_TESTS_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

bool cowl_test_reader_lifecycle(void);
bool cowl_test_reader_read_ontology(void);

#define COWL_READER_TESTS                                                                           \
    cowl_test_reader_lifecycle,                                                                     \
    cowl_test_reader_read_ontology

COWL_END_DECLS

#endif // COWL_READER_TESTS_H
