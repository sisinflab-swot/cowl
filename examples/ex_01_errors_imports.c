/*
 * This example is the same as the previous one,
 * except error and import handling are included.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 */
#include "cowl_api.h"

#define ONTO_PATH "example_pizza.owl"
#define IMPORT_PATH "import.owl"

static CowlOntology* load_import(void *ctx, CowlIRI *iri);
static void handle_error(void *ctx, CowlError const *error);

int main(void) {

    // API initialization can fail due to low memory.
    if (cowl_api_init()) {
        return EXIT_FAILURE;
    }

    CowlParser *parser = cowl_parser_get();
    CowlLogger *logger = cowl_logger_console_get();

    if (!(parser && logger)) {
        return EXIT_FAILURE;
    }

    // Setup an import loader.
    CowlImportLoader loader = cowl_import_loader_init(NULL, load_import, NULL);
    cowl_parser_set_import_loader(parser, loader);

    // Setup an error handler.
    CowlErrorHandler handler = cowl_error_handler_init(logger, handle_error, NULL);
    cowl_parser_set_error_handler(parser, handler);

    // Deserialize an ontology.
    CowlOntology *ontology = cowl_parser_parse_ontology(parser, ONTO_PATH);
    cowl_parser_release(parser);

    // Log the parsed ontology.
    if (ontology) {
        cowl_logger_log_ontology(logger, ontology);
    }

    cowl_ontology_release(ontology);
    cowl_logger_release(logger);

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
    CowlParser *parser = cowl_parser_get();

    if (parser) {
        import = cowl_parser_parse_ontology(parser, IMPORT_PATH);
        cowl_parser_release(parser);
    }

    return import;
}

/*
 * In general it is very reasonable to just check that the ontology returned by the parser
 * is not NULL. The error handler mechanism is only needed if you wish to implement
 * more fine-grained error handling. In this example, errors are logged to file.
 */
static void handle_error(void *ctx, CowlError const *error) {
    cowl_logger_log_error(ctx, error);
}
