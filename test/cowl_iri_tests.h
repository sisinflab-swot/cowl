/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_IRI_TESTS_H
#define COWL_IRI_TESTS_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

bool cowl_test_iri_lifecycle(void);
bool cowl_test_iri_get_ns(void);
bool cowl_test_iri_get_rem(void);
bool cowl_test_iri_to_string_no_brackets(void);
bool cowl_test_iri_equals(void);

#define COWL_IRI_TESTS                                                                              \
    cowl_test_iri_lifecycle,                                                                        \
    cowl_test_iri_get_ns,                                                                           \
    cowl_test_iri_get_rem,                                                                          \
    cowl_test_iri_to_string_no_brackets,                                                            \
    cowl_test_iri_equals

COWL_END_DECLS

#endif // COWL_IRI_TESTS_H
