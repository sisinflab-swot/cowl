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

// Tests

bool cowl_test_parser_lifecycle(void) {
    CowlParser *parser = cowl_parser_get();
    cowl_assert_not_null(parser, "Parser");
    cowl_parser_release(parser);
    return true;
}

bool cowl_test_parser_parse_ontology(void) {
    CowlParser *parser = cowl_parser_get();

    CowlImportsLoader loader = cowl_imports_loader_init(NULL, cowl_test_load_import, NULL);
    cowl_parser_set_imports_loader(parser, loader);
    Vector(CowlError) *errors = vector_alloc(CowlError);

    CowlOntology *onto = cowl_parser_parse_ontology(parser, COWL_TEST_ONTOLOGY, errors);
    cowl_assert_not_null(onto, "Parsed ontology");

    CowlLogger *logger = cowl_logger_file_get(COWL_TEST_ONTOLOGY ".log");
    cowl_assert_not_null(logger, "File logger");

    cowl_logger_clear(logger);
    cowl_logger_log_errors(logger, errors);
    cowl_logger_log_ontology(logger, onto);

    cowl_assert_equal_int(vector_count(errors), 0, "Parsing errors");

    cowl_logger_release(logger);
    vector_free(CowlError, errors);
    cowl_ontology_release(onto);
    cowl_parser_release(parser);

    return true;
}
