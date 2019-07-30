/*
 * This example is the same as the previous one,
 * except error and imports handling are included.
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

static CowlOntology* load_imports(void *ctx, CowlIRI *iri, Vector(CowlError) *errors);

int main(void) {

    cowl_api_init();
    CowlParser *parser = cowl_parser_get();
    CowlLogger *logger = cowl_logger_console_get();

    // Setup an imports loader.
    CowlImportsLoader loader = cowl_imports_loader_init(NULL, load_imports, NULL);
    cowl_parser_set_imports_loader(parser, loader);

    // Deserialize an ontology. Errors will be appended to the 'errors' vector.
    Vector(CowlError) *errors = vector_alloc(CowlError);
    CowlOntology *onto = cowl_parser_parse_ontology(parser, ONTO_PATH, errors);
    cowl_parser_release(parser);

    // Log the errors, if any.
    cowl_uint_t error_count = vector_count(errors);
    cowl_logger_logf(logger, "Ontology parsed with %d error(s).\n", error_count);
    cowl_logger_log_errors(logger, errors);

    if (onto) {
        cowl_logger_log_ontology(logger, onto);
    }

    cowl_ontology_release(onto);
    cowl_logger_release(logger);

    return 0;
}

/*
 * You should return the appropriate ontology given the specified IRI.
 * This may involve making network requests or simply retrieving
 * the imported ontology from the local filesystem. In this example
 * we just return a generic local "import.owl" ontology, disregarding its IRI.
 */
static CowlOntology* load_imports(cowl_unused void *ctx, cowl_unused CowlIRI *iri,
                                  Vector(CowlError) *errors) {
    CowlParser *parser = cowl_parser_get();
    CowlOntology *onto = cowl_parser_parse_ontology(parser, IMPORT_PATH, errors);
    cowl_parser_release(parser);
    return onto;
}
