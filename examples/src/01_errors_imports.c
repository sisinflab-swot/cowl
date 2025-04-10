/*
 * This example is the same as the previous one, except all errors are handled
 * and logged, and ontology imports are resolved.
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
#define IMPORT "import.owl"
#define LOG "errors.log"

/*
 * You should return the appropriate ontology given the specified IRI.
 * This may involve making network requests or simply retrieving
 * the imported ontology from the local filesystem. In this example
 * we just return a generic local "import.owl" ontology, disregarding its IRI.
 */
static CowlOntology *resolve_import(void *ctx, cowl_unused CowlIRI *iri) {
    // In this example, the manager is passed as the resolver's context.
    return cowl_manager_read_path(ctx, ustring_literal(IMPORT));
}

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

    // Setup a global error handler.
    UOStream stream;
    if (uostream_to_path(&stream, LOG)) {
        fprintf(stderr, "Failed to open " LOG "\n");
        return EXIT_FAILURE;
    }

    CowlErrorHandler handler = { &stream, handle_error, NULL };
    cowl_set_error_handler(handler);

    CowlManager *manager = cowl_manager();

    if (!manager) {
        return EXIT_FAILURE;
    }

    // Setup a custom import resolver.
    //
    // Note that the manager will already attempt to resolve imports based on the
    // IRIs of ontologies it is currently responsible for. A custom resolver is only
    // needed if you need to override this behavior.
    CowlImportResolver resolver = { manager, resolve_import, NULL };
    cowl_manager_set_import_resolver(manager, resolver);

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
