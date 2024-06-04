/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_string_tests.h"
#include "cowl.h"
#include "cowl_test_utils.h"
#include "ulib.h"

#define COWL_TEST_STRING "test_string"

bool cowl_test_string_lifecycle(void) {
    CowlString *string = cowl_string_from_static(COWL_TEST_STRING);
    utest_assert_not_null(string);
    cowl_release(string);
    return true;
}

bool cowl_test_string_get_empty(void) {
    CowlString *string = cowl_string_empty();
    utest_assert_ustring(*cowl_string_get_raw(string), ==, ustring_empty);

    CowlString *other = cowl_string_empty();
    utest_assert_ptr(string, ==, other);

    cowl_release_all(string, other);
    return true;
}

bool cowl_test_string_get_length(void) {
    ulib_uint len = sizeof(COWL_TEST_STRING) - 1;
    CowlString *string = cowl_string_from_static(COWL_TEST_STRING);
    utest_assert_uint(cowl_string_get_length(string), ==, len);
    cowl_release(string);
    return true;
}

bool cowl_test_string_equals(void) {
    CowlString *a = cowl_string_from_static(COWL_TEST_STRING);
    CowlString *b = cowl_string_from_static(COWL_TEST_STRING);
    cowl_assert_equal(string, a, b);
    cowl_release(b);

    b = cowl_string_from_static(COWL_TEST_STRING "_2");
    cowl_assert_not_equal(string, a, b);

    cowl_release_all(a, b);
    return true;
}

bool cowl_test_string_with_format(void) {
    CowlString *string = cowl_string_with_format("Test %s %d", "string", 1);
    CowlString *other = cowl_string_from_static("Test string 1");
    cowl_assert_equal(string, string, other);

    cowl_release_all(string, other);
    return true;
}

bool cowl_test_string_concat(void) {
    CowlString *string = cowl_string_from_static(COWL_TEST_STRING);
    CowlString *other = cowl_string_from_static(COWL_TEST_STRING);

    CowlString *concat = cowl_string_concat(string, other);
    CowlString *oracle = cowl_string_from_static(COWL_TEST_STRING COWL_TEST_STRING);
    cowl_assert_equal(string, concat, oracle);

    cowl_release_all(string, other, concat, oracle);
    return true;
}

bool cowl_test_string_intern(void) {
    CowlString *a = cowl_string_opt(ustring_literal(COWL_TEST_STRING),
                                    COWL_SO_COPY | COWL_SO_INTERN);
    CowlString *ai = cowl_string_intern(a);
    utest_assert_ptr(a, ==, ai);

    CowlString *b = cowl_string_from_static(COWL_TEST_STRING);
    CowlString *bi = cowl_string_intern(b);
    utest_assert_ptr(ai, ==, bi);

    cowl_release_all(a, b);
    return true;
}
