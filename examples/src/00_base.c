/*
 * This introductory example shows how to read an ontology
 * and log its axioms and annotations.
 *
 * @note Most errors are not handled for the sake of simplicity.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 */
#include "cowl.h"
#include "ulib.h"
#include <stdio.h>
#include <stdlib.h>

#define ONTO "example_pizza.owl"

int main(void) {
    // You must always initialize the library before use.
    cowl_init();

    // Read an ontology from file.
    CowlOntology *onto = cowl_ontology_at_path(ustring_literal(ONTO));

    if (!onto) {
        // The ontology could not be read.
        fprintf(stderr, "Failed to load ontology " ONTO "\n");
        return EXIT_FAILURE;
    }

    // Do stuff with the ontology. In this case we are just logging it
    // to the standard output using the default writer.
    cowl_ontology_to_stream(onto, uostream_std());

    // Release the ontology.
    cowl_release(onto);

    return EXIT_SUCCESS;
}
