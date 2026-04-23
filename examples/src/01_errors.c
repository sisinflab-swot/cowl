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
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ONTO "example_pizza.owl"

static void log_error(char const *msg) {
    fprintf(stderr, "Error: %s\n", msg);
}

static void log_cowl_error(CowlError const *error) {
    // Cowl integrates with the uLib I/O API. This is usually preferable as it allows
    // writing most objects, including errors, to output streams without needing to
    // convert them to strings first (i.e. without additional allocations).
    UOStream *stream = uostream_stderr();
    cowl_write_static(stream, "Error: ");
    cowl_write_error(stream, error);
    cowl_write_static(stream, "\n");
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

    // The returned ontology is NULL if an error occurs during reading,
    // e.g. due to I/O or syntax errors. More details about the error can be obtained
    // by inspecting the return code.
    cowl_ret ret;
    CowlOntology *onto = cowl_reader_read_ontology_at_path(reader, path, &ret);

    if (!onto) {
        if (ret == COWL_ERR_IO) {
            // An I/O error occurred, e.g. the file does not exist or is not
            // readable. Further details can be obtained by inspecting `errno`.
            log_error(errno ? strerror(errno) : "unknown I/O error");
        } else if (ret == COWL_ERR_SYNTAX) {
            // In case of syntax errors, we can log the last one.
            log_cowl_error(cowl_reader_last_error(reader));
        } else {
            // Some other error occurred.
            log_error("ontology read failure");
        }
        return EXIT_FAILURE;
    }

    // Stream operations can fail, so we need to check for errors.
    ret = cowl_ontology_to_stream(onto, uostream_std());

    if (cowl_is_err(ret)) {
        log_error("ontology write failure");
        return EXIT_FAILURE;
    }

    cowl_release_all(onto, reader);
    return EXIT_SUCCESS;
}
