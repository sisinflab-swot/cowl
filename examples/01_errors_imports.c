/*
 * This example is the same as the previous one,
 * except error and import handling are included.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 */
#include "cowl.h"

#define ONTO "example_pizza.owl"
#define IMPORT "import.owl"
#define LOG "errors.log"

static CowlOntology* load_import(void *ctx, CowlIRI *iri);
static void handle_error(void *ctx, CowlError const *error);

int main(void) {

    // API initialization can fail due to low memory.
    if (cowl_init()) {
        return EXIT_FAILURE;
    }

    // Setup a global error handler and import loader.
    cowl_set_import_loader(cowl_import_loader(NULL, load_import, NULL));

    UOStream stream;
    if (uostream_to_path(&stream, LOG)) {
        return EXIT_FAILURE;
    }

    cowl_set_error_handler(cowl_error_handler(&stream, handle_error, NULL));

    // Read the ontology from file.
    CowlManager *manager = cowl_manager_get();

    if (manager) {
        CowlOntology *onto = cowl_manager_read_path(manager, ustring_literal(ONTO));

        // Do stuff with the ontology.
        if (onto) {
            cowl_manager_write_file(manager, onto, stdout);
            cowl_ontology_release(onto);
        }

        cowl_manager_release(manager);
    }

    uostream_deinit(&stream);

    return EXIT_SUCCESS;
}

/*
 * You should return the appropriate ontology given the specified IRI.
 * This may involve making network requests or simply retrieving
 * the imported ontology from the local filesystem. In this example
 * we just return a generic local "import.owl" ontology, disregarding its IRI.
 */
static CowlOntology* load_import(cowl_unused void *ctx, cowl_unused CowlIRI *iri) {
    CowlOntology *import = NULL;
    CowlManager *manager = cowl_manager_get();

    if (manager) {
        import = cowl_manager_read_path(manager, ustring_literal(IMPORT));
        cowl_manager_release(manager);
    }

    return import;
}

/*
 * In general, it is very reasonable to just check that the ontology returned
 * by the manager is not NULL. The error handler mechanism is only needed if you wish
 * to implement more fine-grained error handling. In this example, errors are logged.
 */
static void handle_error(void *ctx, CowlError const *error) {
    cowl_write_error(ctx, error);
}
