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
#define LOG "errors.log"

/*
 * In general, it is very reasonable to just check that the ontology returned
 * by the manager is not NULL. The error handler mechanism is only needed if you wish
 * to implement more fine-grained error handling. In this example, errors are logged.
 */
static void handle_error(void *ctx, CowlError const *error) {
    cowl_write_error(ctx, error);
    cowl_write_static(ctx, "\n");
}

int main(void) {
    // API initialization can fail due to low memory.
    if (cowl_init()) {
        return EXIT_FAILURE;
    }

    // Setup an error handler.
    CowlManager *manager = cowl_manager();

    UOStream stream;
    if (uostream_to_path(&stream, LOG)) {
        fprintf(stderr, "Failed to open " LOG "\n");
        return EXIT_FAILURE;
    }

    CowlErrorHandler handler = { &stream, handle_error, NULL };
    cowl_manager_set_error_handler(manager, handler);

    // Read the ontology from file.
    CowlOntology *onto = cowl_manager_read_path(manager, ustring_literal(ONTO));

    if (!onto) {
        fprintf(stderr, "Failed to load ontology " ONTO "\n");
        return EXIT_FAILURE;
    }

    // Do stuff with the ontology.
    cowl_manager_write_file(manager, onto, stdout);

    cowl_release_all(manager, onto);
    uostream_deinit(&stream);

    return EXIT_SUCCESS;
}
