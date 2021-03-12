/*
 * In this example we will be logging the atomic subclasses
 * of a certain class recursively. Error and import handling are omitted.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 */
#include "cowl_api.h"

#define ONTO_PATH "example_pizza.owl"
#define ONTO_NS "http://www.co-ode.org/ontologies/pizza/pizza.owl#"
#define CLASS_NAME "Food"

static bool for_each_cls(void *ctx, void *cls);

int main(void) {
    cowl_api_init();

    CowlReader *reader = cowl_reader_get();
    CowlOntology *ontology = cowl_reader_read_path(reader, ONTO_PATH);
    cowl_reader_release(reader);

    if (ontology) {
        CowlLogger *logger = cowl_logger_console_get();
        CowlClass *cls = cowl_class_from_static(ONTO_NS CLASS_NAME);
        cowl_logger_logs(logger, "Recursive atomic subclasses of " CLASS_NAME ":\n");

        // Since we are going to perform a recursive query,
        // we need the ontology to be part of the context.
        void const *ctx[] = { ontology, logger };
        CowlIterator iter = cowl_iterator_init(ctx, for_each_cls);
        cowl_ontology_iterate_sub_classes(ontology, cls, &iter);

        cowl_class_release(cls);
        cowl_logger_release(logger);
        cowl_ontology_release(ontology);
    }

    return EXIT_SUCCESS;
}

static bool for_each_cls(void *ctx, void *cls) {
    if (cowl_cls_exp_get_type(cls) != COWL_CET_CLASS) return true;

    // Unpack the context.
    void **array = ctx;
    CowlOntology *ontology = array[0];
    CowlLogger *logger = array[1];

    // Log the IRI remainder.
    CowlIRI *iri = cowl_class_get_iri(cls);

    cowl_logger_log(logger, cowl_iri_get_rem(iri));
    cowl_logger_logs(logger, "\n");

    // Recurse.
    CowlIterator iter = cowl_iterator_init(ctx, for_each_cls);
    return cowl_ontology_iterate_sub_classes(ontology, cls, &iter);
}
