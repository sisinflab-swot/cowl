/*
 * This example is the same as the previous one, except all errors are handled and
 * logged.
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
    // API initialization can fail due to low memory.
    if (cowl_init()) {
        return EXIT_FAILURE;
    }

    CowlManager *manager = cowl_manager();

    // Cowl objects are allocated on the heap, so we need to check for NULL.
    if (!manager) {
        return EXIT_FAILURE;
    }

    CowlOntology *onto = cowl_manager_read_path(manager, ustring_literal(ONTO));

    if (!onto) {
        fprintf(stderr, "Failed to load ontology " ONTO "\n");
        return EXIT_FAILURE;
    }

    // I/O operations can fail, so we need to check for errors.
    cowl_ret ret = cowl_manager_write_file(manager, onto, stdout);

    if (cowl_is_err(ret)) {
        return EXIT_FAILURE;
    }

    cowl_release_all(manager, onto);

    return EXIT_SUCCESS;
}
