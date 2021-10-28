/*
 * This introductory example shows how to read an ontology
 * and log its axioms and annotations.
 * Note that error and import handling are omitted for the sake of simplicity.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 */
#include "cowl_api.h"

#define ONTO_PATH "example_pizza.owl"

int main(void) {

    // You must always initialize the API before use.
    cowl_api_init();

    // Instantiate a reader and deserialize an ontology from file.
    CowlReader *reader = cowl_reader_get();
    CowlOntology *ontology = cowl_reader_read_path(reader, ONTO_PATH);

    // You don't need the reader anymore.
    cowl_reader_release(reader);

    // Log the ontology.
    if (ontology) {
        CowlLogger *logger = cowl_logger_console_get();
        cowl_logger_log_ontology(logger, ontology);
        cowl_logger_release(logger);

        // Release the ontology.
        cowl_ontology_release(ontology);
    }

    return EXIT_SUCCESS;
}
