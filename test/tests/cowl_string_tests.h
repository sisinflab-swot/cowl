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

#include "cowl_std.h"

COWL_BEGIN_DECLS

bool cowl_test_string_lifecycle(void);
bool cowl_test_string_get_empty(void);
bool cowl_test_string_get_length(void);
bool cowl_test_string_equals(void);
bool cowl_test_string_with_format(void);
bool cowl_test_string_concat(void);
bool cowl_test_string_intern(void);

#define COWL_STRING_TESTS                                                                          \
    cowl_test_string_lifecycle, cowl_test_string_get_empty, cowl_test_string_get_length,           \
        cowl_test_string_equals, cowl_test_string_with_format, cowl_test_string_concat,            \
        cowl_test_string_intern

COWL_END_DECLS

#endif // COWL_STRING_TESTS_H
