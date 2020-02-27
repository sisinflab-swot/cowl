/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_iri_tests.h"
#include "cowl_iri.h"
#include "cowl_string.h"
#include "cowl_test_utils.h"

#define COWL_TEST_IRI_NS "http://site.com/ontology.owl#"
#define COWL_TEST_IRI_REM "remainder"
#define COWL_TEST_IRI COWL_TEST_IRI_NS COWL_TEST_IRI_REM

bool cowl_test_iri_lifecycle(void) {
    CowlIRI *iri = cowl_iri_from_static(COWL_TEST_IRI);
    cowl_assert_not_null(iri, "Created IRI");
    cowl_iri_release(iri);
    return true;
}

bool cowl_test_iri_get_ns(void) {
    char const *tests[][2] = {
        {COWL_TEST_IRI, COWL_TEST_IRI_NS},
        {COWL_TEST_IRI_REM, ""},
        {COWL_TEST_IRI_NS, COWL_TEST_IRI_NS}
    };

    for (unsigned i = 0; i < cowl_array_size(tests); ++i) {
        char const *iri_str = tests[i][0];
        char const *ns_str = tests[i][1];
        CowlIRI *iri = cowl_iri_from_cstring(iri_str, strlen(iri_str));
        CowlString *ns = cowl_iri_get_ns(iri);
        cowl_assert_equal_str(cowl_string_get_cstring(ns), ns_str, "Namespace #%u", i);
        cowl_iri_release(iri);
    }

    return true;
}

bool cowl_test_iri_get_rem(void) {
    char const *tests[][2] = {
        {COWL_TEST_IRI, COWL_TEST_IRI_REM},
        {COWL_TEST_IRI_REM, COWL_TEST_IRI_REM},
        {COWL_TEST_IRI_NS, ""}
    };

    for (unsigned i = 0; i < cowl_array_size(tests); ++i) {
        char const *iri_str = tests[i][0];
        char const *rem_str = tests[i][1];
        CowlIRI *iri = cowl_iri_from_cstring(iri_str, strlen(iri_str));
        CowlString *rem = cowl_iri_get_rem(iri);
        cowl_assert_equal_str(cowl_string_get_cstring(rem), rem_str, "Remainder #%u", i);
        cowl_iri_release(iri);
    }

    return true;
}

bool cowl_test_iri_to_string_no_brackets(void) {
    CowlIRI *iri = cowl_iri_from_static(COWL_TEST_IRI);
    CowlString *str = cowl_iri_to_string_no_brackets(iri);

    cowl_assert_equal_str(cowl_string_get_cstring(str), COWL_TEST_IRI,
                          "String representation without brackets");
    cowl_string_release(str);

    return true;
}

bool cowl_test_iri_equals(void) {
    CowlIRI *expected = cowl_iri_from_static(COWL_TEST_IRI);

    char const *tests[][2] = {
        {COWL_TEST_IRI_NS, COWL_TEST_IRI_REM},
        {"", COWL_TEST_IRI},
        {COWL_TEST_IRI, ""},
        {"http://site.com/onto", "logy.owl#remainder"},
        {"http://site.com/ontology.owl#rem", "ainder"}
    };

    for (unsigned i = 0; i < cowl_array_size(tests); ++i) {
        char const *prefix_str = tests[i][0];
        char const *suffix_str = tests[i][1];

        CowlString *prefix = cowl_string_get(prefix_str, strlen(prefix_str), true);
        CowlString *suffix = cowl_string_get(suffix_str, strlen(suffix_str), true);

        CowlIRI *iri = cowl_iri_get(prefix, suffix);
        cowl_assert_equal(iri, iri, expected, "IRI #%u", i);

        cowl_string_release(prefix);
        cowl_string_release(suffix);
        cowl_iri_release(iri);
    }

    CowlIRI *iri = cowl_iri_from_static(COWL_TEST_IRI "_2");
    cowl_assert_not_equal(iri, iri, expected, "IRI");

    cowl_iri_release(iri);
    cowl_iri_release(expected);

    return true;
}
