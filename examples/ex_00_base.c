/*
 * This introductory example shows how to parse and log an ontology.
 * Note that error and imports handling are omitted for the sake of simplicity.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 */
#include "cowl_api.h"

int main(void) {

    // You must always initialize the API before use.
    cowl_api_init();

    // Instantiate a parser and deserialize an ontology.
    CowlParser *parser = cowl_parser_get();
    CowlOntology *onto = cowl_parser_parse_ontology(parser, "pizza.owl", NULL);

    // You don't need the parser anymore.
    cowl_parser_release(parser);

    // Log the parsed ontology.
    if (onto) {
        CowlLogger *logger = cowl_logger_console_get();
        cowl_logger_log_ontology(logger, onto);
        cowl_logger_release(logger);
    }

    // Release the ontology.
    cowl_ontology_release(onto);

    return 0;
}
