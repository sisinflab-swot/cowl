/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_api.h"
#include "cowl_iri_tests.h"
#include "cowl_ontology_tests.h"
#include "cowl_parser_tests.h"
#include "cowl_string_tests.h"
#include "cowl_test_utils.h"
#include "cowl_version_tests.h"

#define cowl_run_tests(EXIT_CODE, ...) do {                                                         \
    bool (*tests_to_run[])(void) = { __VA_ARGS__ };                                                 \
    for (size_t test_i = 0; test_i < cowl_array_size(tests_to_run); ++test_i) {                     \
        if (!tests_to_run[test_i]()) EXIT_CODE = EXIT_FAILURE;                                      \
    }                                                                                               \
} while(0)

int main(void) {

#ifdef COWL_DEBUG_LEAKS
    cowl_leak_debug_init();
#endif

    cowl_api_init();

    int exit_code = EXIT_SUCCESS;
    printf("Starting tests...\n");

    cowl_run_tests(exit_code,
        COWL_STRING_TESTS,
        COWL_IRI_TESTS,
        COWL_PARSER_TESTS,
        COWL_ONTOLOGY_TESTS,
        COWL_VERSION_TESTS
    );

    cowl_api_deinit();

    if (exit_code == EXIT_SUCCESS) {
        printf("All tests passed.\n");
    } else {
        printf("Some tests failed.\n");
    }

#ifdef COWL_DEBUG_LEAKS
    cowl_uint_t leaks = cowl_leak_debug_count();

    if (leaks) {
        printf("Detected %" COWL_UINT_FMT " leaked objects.\n", leaks);
        cowl_leak_debug_print();
        exit_code = EXIT_FAILURE;
    } else {
        printf("No leaks detected.\n");
    }

    cowl_leak_debug_deinit();
#endif

    return exit_code;
}
