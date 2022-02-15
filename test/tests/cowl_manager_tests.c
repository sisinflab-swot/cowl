/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_manager_tests.h"
#include "cowl_manager.h"
#include "cowl_ontology.h"
#include "cowl_string.h"
#include "cowl_test_utils.h"

// Utils

static void cowl_test_manager_write_error(void *ctx, CowlError const *error) {
    CowlString *string = cowl_error_to_string(error);
    uostream_write_string(ctx, cowl_string_get_raw(string), NULL);
    cowl_string_release(string);
}

// Tests

bool cowl_test_manager_lifecycle(void) {
    CowlManager *manager = cowl_manager_get();
    utest_assert_not_null(manager);
    cowl_manager_release(manager);
    return true;
}

bool cowl_test_manager_read_ontology(void) {
    CowlManager *manager = cowl_manager_get();

    CowlImportLoader loader = cowl_import_loader_init(NULL, cowl_test_load_import, NULL);
    cowl_manager_set_import_loader(manager, loader);

    UOStream stream;
    utest_assert_critical(uostream_to_path(&stream, COWL_TEST_ONTOLOGY ".log") == USTREAM_OK);

    CowlErrorHandler handler = cowl_error_handler_init(&stream, cowl_test_manager_write_error, NULL);
    cowl_manager_set_error_handler(manager, handler);

    CowlOntology *onto = cowl_manager_read_path(manager, ustring_literal(COWL_TEST_ONTOLOGY));
    utest_assert_not_null(onto);

    CowlString *string = cowl_ontology_to_string(onto);
    uostream_write_string(&stream, cowl_string_get_raw(string), NULL);
    cowl_string_release(string);

    cowl_ontology_release(onto);
    cowl_manager_release(manager);

    return true;
}
