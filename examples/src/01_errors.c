/*
 * This example is the same as the previous one,
 * except all errors are handled and logged.
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

static void log_error(char const *msg) {
    fprintf(stderr, "Error: %s\n", msg);
}

int main(void) {
    // API initialization can fail due to low memory.
    if (cowl_is_err(cowl_init())) {
        log_error("API initialization failure");
        return EXIT_FAILURE;
    }

    // Cowl objects are allocated on the heap, so we need to check for NULL.
    CowlReader *reader = cowl_reader_functional();

    if (!reader) {
        log_error("allocation failure");
        return EXIT_FAILURE;
    }

    UString const path = ustring_literal(ONTO);
    CowlOntology *onto = cowl_reader_read_ontology_at_path(reader, path);

    if (!onto) {
        // If reading fails, we can log the last reader error.
        cowl_reader_write_error(reader, uostream_stderr());
        return EXIT_FAILURE;
    }

    // I/O operations can fail, so we need to check for errors.
    cowl_ret ret = cowl_ontology_to_stream(onto, uostream_std());

    if (cowl_is_err(ret)) {
        log_error("ontology write failure");
        return EXIT_FAILURE;
    }

    cowl_release_all(onto, reader);
    return EXIT_SUCCESS;
}
