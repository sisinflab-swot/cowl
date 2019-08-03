/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_string_tests.h"
#include "cowl_string_private.h"
#include "cowl_test_utils.h"

#define COWL_TEST_STRING "test_string"

bool cowl_test_string_lifecycle(void) {
    CowlString *string = cowl_string_from_static(COWL_TEST_STRING);
    cowl_assert_not_null(string, "Created string");
    cowl_string_release(string);
    return true;
}

bool cowl_test_string_get_empty(void) {
    CowlString *string = cowl_string_get_empty();
    cowl_assert_equal_str(cowl_string_get_cstring(string), "", "Value of the empty string");
    cowl_assert_equal_int(cowl_string_get_length(string), 0, "Length of the empty string");

    CowlString *other = cowl_string_get_empty();
    cowl_assert(string == other, "Empty strings must be pointers to the same instance.");

    cowl_string_release(string);
    cowl_string_release(other);

    return true;
}

bool cowl_test_string_get_length(void) {
    cowl_uint_t len = sizeof(COWL_TEST_STRING) - 1;
    CowlString *string = cowl_string_from_static(COWL_TEST_STRING);
    cowl_assert_equal_int(cowl_string_get_length(string), len, "String length");
    cowl_string_release(string);
    return true;
}

bool cowl_test_string_equals(void) {
    CowlString *a = cowl_string_from_static(COWL_TEST_STRING);
    CowlString *b = cowl_string_from_static(COWL_TEST_STRING);
    cowl_assert_equal(string, a, b, "String");
    cowl_string_release(b);

    b = cowl_string_from_static(COWL_TEST_STRING "_2");
    cowl_assert_not_equal(string, a, b, "String");
    cowl_string_release(b);

    return true;
}

bool cowl_test_string_with_format(void) {
    CowlString *string = cowl_string_with_format("Test %s %d", "string", 1);
    CowlString *other = cowl_string_from_static("Test string 1");
    cowl_assert_equal(string, string, other, "String");

    cowl_string_release(string);
    cowl_string_release(other);

    return true;
}

bool cowl_test_string_concat(void) {
    CowlString *string = cowl_string_from_static(COWL_TEST_STRING);
    CowlString *other = cowl_string_from_static(COWL_TEST_STRING);

    CowlString *concat = cowl_string_concat(string, other);
    CowlString *oracle = cowl_string_from_static(COWL_TEST_STRING COWL_TEST_STRING);

    cowl_assert_equal(string, concat, oracle, "Concatenated string");

    cowl_string_release(string);
    cowl_string_release(other);
    cowl_string_release(concat);
    cowl_string_release(oracle);

    return true;
}

bool cowl_test_string_get_intern(void) {
    CowlString *a = cowl_string_from_static(COWL_TEST_STRING);
    a = cowl_string_get_intern(a, false);

    CowlString *b = cowl_string_from_static(COWL_TEST_STRING);
    b = cowl_string_get_intern(b, false);

    cowl_assert(a == b, "Equal interned strings must be pointers to the same instance.");

    cowl_string_release_intern(a);
    cowl_string_release_intern(b);

    return true;
}
