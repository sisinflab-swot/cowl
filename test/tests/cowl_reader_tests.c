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
#include "cowl_iri.h"
#include "cowl_logger.h"
#include "cowl_ontology.h"
#include "cowl_reader.h"
#include "cowl_test_utils.h"

// Utils

static void cowl_test_reader_handle_error(void *ctx, CowlError const *error) {
    cowl_logger_log_error(ctx, error);
}

// Tests

bool cowl_test_reader_lifecycle(void) {
    CowlReader *reader = cowl_reader_get();
    cowl_assert_not_null(reader, "Reader");
    cowl_reader_release(reader);
    return true;
}

bool cowl_test_reader_read_ontology(void) {
    CowlReader *reader = cowl_reader_get();

    CowlImportLoader loader = cowl_import_loader_init(NULL, cowl_test_load_import, NULL);
    cowl_reader_set_import_loader(reader, loader);

    CowlLogger *logger = cowl_logger_file_get(COWL_TEST_ONTOLOGY ".log");
    cowl_assert_not_null(logger, "File logger");
    cowl_logger_clear(logger);

    CowlErrorHandler handler = cowl_error_handler_init(logger, cowl_test_reader_handle_error, NULL);
    cowl_reader_set_error_handler(reader, handler);

    CowlOntology *onto = cowl_reader_read_path(reader, COWL_TEST_ONTOLOGY);
    cowl_assert_not_null(onto, "Parsed ontology");

    cowl_logger_log_ontology(logger, onto);

    cowl_logger_release(logger);
    cowl_ontology_release(onto);
    cowl_reader_release(reader);

    return true;
}
