/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_parser_tests.h"
#include "cowl_iri.h"
#include "cowl_logger.h"
#include "cowl_parser.h"
#include "cowl_ontology.h"
#include "cowl_test_utils.h"

// Utils

static void cowl_test_parser_handle_error(void *ctx, CowlError const *error) {
    cowl_logger_log_error(ctx, error);
}

// Tests

bool cowl_test_parser_lifecycle(void) {
    CowlParser *parser = cowl_parser_get();
    cowl_assert_not_null(parser, "Parser");
    cowl_parser_release(parser);
    return true;
}

bool cowl_test_parser_parse_ontology(void) {
    CowlParser *parser = cowl_parser_get();

    CowlImportLoader loader = cowl_import_loader_init(NULL, cowl_test_load_import, NULL);
    cowl_parser_set_import_loader(parser, loader);

    CowlLogger *logger = cowl_logger_file_get(COWL_TEST_ONTOLOGY ".log");
    cowl_assert_not_null(logger, "File logger");
    cowl_logger_clear(logger);

    CowlErrorHandler handler = cowl_error_handler_init(logger, cowl_test_parser_handle_error, NULL);
    cowl_parser_set_error_handler(parser, handler);

    CowlOntology *onto = cowl_parser_parse_ontology(parser, COWL_TEST_ONTOLOGY);
    cowl_assert_not_null(onto, "Parsed ontology");

    cowl_logger_log_ontology(logger, onto);

    cowl_logger_release(logger);
    cowl_ontology_release(onto);
    cowl_parser_release(parser);

    return true;
}
