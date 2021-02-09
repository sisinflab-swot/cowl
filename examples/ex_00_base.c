/*
 * This introductory example shows how to parse an ontology
 * and log its axioms and annotations.
 * Note that error and import handling are omitted for the sake of simplicity.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 */
#include "cowl_api.h"

#define ONTO_PATH "example_pizza.owl"

int main(void) {

    // You must always initialize the API before use.
    cowl_api_init();

    // Instantiate a parser and deserialize an ontology.
    CowlParser *parser = cowl_parser_get();
    CowlOntology *ontology = cowl_parser_parse_path(parser, ONTO_PATH);

    // You don't need the parser anymore.
    cowl_parser_release(parser);

    // Log the parsed ontology.
    if (ontology) {
        CowlLogger *logger = cowl_logger_console_get();
        cowl_logger_log_ontology(logger, ontology);
        cowl_logger_release(logger);

        // Release the ontology.
        cowl_ontology_release(ontology);
    }

    return EXIT_SUCCESS;
}
