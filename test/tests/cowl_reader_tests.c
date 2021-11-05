/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_reader_tests.h"
#include "cowl_ontology.h"
#include "cowl_reader.h"
#include "cowl_string.h"
#include "cowl_test_utils.h"

// Utils

static void cowl_test_reader_write_error(void *ctx, CowlError const *error) {
    CowlString *string = cowl_error_to_string(error);
    uostream_write(ctx, cowl_string_get_cstring(string), cowl_string_get_length(string), NULL);
    cowl_string_release(string);
}

// Tests

bool cowl_test_reader_lifecycle(void) {
    CowlReader *reader = cowl_reader_get();
    utest_assert_not_null(reader);
    cowl_reader_release(reader);
    return true;
}

bool cowl_test_reader_read_ontology(void) {
    CowlReader *reader = cowl_reader_get();

    CowlImportLoader loader = cowl_import_loader_init(NULL, cowl_test_load_import, NULL);
    cowl_reader_set_import_loader(reader, loader);

    UOStream stream;
    utest_assert_critical(uostream_to_path(&stream, COWL_TEST_ONTOLOGY ".log") == USTREAM_OK);

    CowlErrorHandler handler = cowl_error_handler_init(&stream, cowl_test_reader_write_error, NULL);
    cowl_reader_set_error_handler(reader, handler);

    CowlOntology *onto = cowl_reader_read_path(reader, COWL_TEST_ONTOLOGY);
    utest_assert_not_null(onto);

    CowlString *string = cowl_ontology_to_string(onto);
    uostream_write(&stream, cowl_string_get_cstring(string), cowl_string_get_length(string), NULL);
    cowl_string_release(string);

    cowl_ontology_release(onto);
    cowl_reader_release(reader);

    return true;
}
