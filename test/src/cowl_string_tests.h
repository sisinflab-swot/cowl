/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_STRING_TESTS_H
#define COWL_STRING_TESTS_H

#include "cowl_attrs.h"

COWL_BEGIN_DECLS

void cowl_test_string_lifecycle(void);
void cowl_test_string_get_empty(void);
void cowl_test_string_get_length(void);
void cowl_test_string_equals(void);
void cowl_test_string_with_format(void);
void cowl_test_string_concat(void);
void cowl_test_string_intern(void);

#define COWL_STRING_TESTS                                                                          \
    cowl_test_string_lifecycle, cowl_test_string_get_empty, cowl_test_string_get_length,           \
        cowl_test_string_equals, cowl_test_string_with_format, cowl_test_string_concat,            \
        cowl_test_string_intern

COWL_END_DECLS

#endif // COWL_STRING_TESTS_H
