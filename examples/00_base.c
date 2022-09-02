/*
 * This introductory example shows how to read an ontology
 * and log its axioms and annotations.
 * Note that error and import handling are omitted for the sake of simplicity.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 */
#include "cowl_api.h"

#define ONTO "example_pizza.owl"

int main(void) {

    // You must always initialize the API before use.
    cowl_api_init();

    // Instantiate a manager and deserialize an ontology from file.
    CowlManager *manager = cowl_manager_get();
    CowlOntology *ontology = cowl_manager_read_path(manager, ustring_literal(ONTO));

    if (ontology) {
        // Do stuff with the ontology. In this case we are just logging it
        // to the standard output using the default writer.
        cowl_manager_write_file(manager, ontology, stdout);

        // Release the ontology.
        cowl_ontology_release(ontology);
    }

    // Release the manager.
    cowl_manager_release(manager);

    return EXIT_SUCCESS;
}
