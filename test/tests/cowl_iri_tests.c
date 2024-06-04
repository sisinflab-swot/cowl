/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_iri_tests.h"
#include "cowl.h"
#include "cowl_test_utils.h"
#include "ulib.h"

#define COWL_TEST_IRI_NS "http://site.com/ontology.owl#"
#define COWL_TEST_IRI_REM "remainder"
#define COWL_TEST_IRI COWL_TEST_IRI_NS COWL_TEST_IRI_REM

bool cowl_test_iri_lifecycle(void) {
    CowlIRI *iri = cowl_iri_from_static(COWL_TEST_IRI);
    utest_assert_not_null(iri);
    cowl_release(iri);
    return true;
}

bool cowl_test_iri_get_ns(void) {
    char const *tests[][2] = {
        { COWL_TEST_IRI, COWL_TEST_IRI_NS },
        { COWL_TEST_IRI_REM, "" },
        { COWL_TEST_IRI_NS, COWL_TEST_IRI_NS },
    };

    for (unsigned i = 0; i < ulib_array_count(tests); ++i) {
        char const *iri_str = tests[i][0];
        char const *ns_str = tests[i][1];
        CowlIRI *iri = cowl_iri_from_string(ustring_wrap_buf(iri_str));
        CowlString *ns = cowl_iri_get_ns(iri);
        utest_assert_string(cowl_string_get_cstring(ns), ==, ns_str);
        cowl_release(iri);
    }

    return true;
}

bool cowl_test_iri_get_rem(void) {
    char const *tests[][2] = {
        { COWL_TEST_IRI, COWL_TEST_IRI_REM },
        { COWL_TEST_IRI_REM, COWL_TEST_IRI_REM },
        { COWL_TEST_IRI_NS, "" },
    };

    for (unsigned i = 0; i < ulib_array_count(tests); ++i) {
        char const *iri_str = tests[i][0];
        char const *rem_str = tests[i][1];
        CowlIRI *iri = cowl_iri_from_string(ustring_wrap_buf(iri_str));
        CowlString *rem = cowl_iri_get_rem(iri);
        utest_assert_string(cowl_string_get_cstring(rem), ==, rem_str);
        cowl_release(iri);
    }

    return true;
}

bool cowl_test_iri_equals(void) {
    CowlIRI *expected = cowl_iri_from_static(COWL_TEST_IRI);
    cowl_assert_equal(iri, expected, cowl_get_iri(expected));

    char const *tests[][2] = {
        { COWL_TEST_IRI_NS, COWL_TEST_IRI_REM },
        { "", COWL_TEST_IRI },
        { COWL_TEST_IRI, "" },
        { "http://site.com/onto", "logy.owl#remainder" },
        { "http://site.com/ontology.owl#rem", "ainder" },
    };

    for (unsigned i = 0; i < ulib_array_count(tests); ++i) {
        char const *prefix_str = tests[i][0];
        char const *suffix_str = tests[i][1];

        CowlString *prefix = cowl_string_opt(ustring_wrap_buf(prefix_str), COWL_SO_COPY);
        CowlString *suffix = cowl_string_opt(ustring_wrap_buf(suffix_str), COWL_SO_COPY);

        CowlIRI *iri = cowl_iri(prefix, suffix);
        cowl_assert_equal(iri, iri, expected);
        cowl_release_all(prefix, suffix, iri);
    }

    CowlIRI *iri = cowl_iri_from_static(COWL_TEST_IRI "_2");
    cowl_assert_not_equal(iri, iri, expected);

    cowl_release_all(iri, expected);
    return true;
}
