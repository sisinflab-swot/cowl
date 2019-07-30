/*
 * In this example we will be logging the atomic subclasses
 * of a certain class recursively. Error and imports handling are omitted.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 */
#include "cowl_api.h"

#define ONTO_PATH "example_pizza.owl"
#define ONTO_NS "http://www.co-ode.org/ontologies/pizza/pizza.owl#"
#define CLASS_NAME "Food"

static bool for_each_cls(void *ctx, CowlClsExp *exp);

int main(void) {

    cowl_api_init();
    CowlParser *parser = cowl_parser_get();
    CowlOntology *onto = cowl_parser_parse_ontology(parser, ONTO_PATH, NULL);
    cowl_parser_release(parser);

    if (onto) {
        CowlLogger *logger = cowl_logger_console_get();

        CowlIRI *iri = cowl_iri_from_static(ONTO_NS CLASS_NAME);
        CowlClass *cls = cowl_class_get(iri);

        cowl_logger_logf(logger, "Recursive atomic subclasses of " CLASS_NAME ":\n");

        // Since we are going to perform a recursive query,
        // we need the ontology to be part of the context.
        void const *ctx[] = { onto, logger };
        CowlClsExpIterator iter = cowl_iterator_init(ctx, for_each_cls);
        cowl_ontology_iterate_sub_classes(onto, cls, &iter);

        cowl_class_release(cls);
        cowl_iri_release(iri);
        cowl_logger_release(logger);
    }

    cowl_ontology_release(onto);

    return 0;
}

static bool for_each_cls(void *ctx, CowlClsExp *exp) {
    if (cowl_cls_exp_get_type(exp) != COWL_CET_CLASS) return true;

    // Unpack the context.
    void **array = ctx;
    CowlOntology *onto = array[0];
    CowlLogger *logger = array[1];

    // Log the IRI remainder.
    CowlClass *cls = (CowlClass *)exp;
    CowlIRI *iri = cowl_class_get_iri(cls);

    cowl_logger_log(logger, cowl_iri_get_rem(iri));
    cowl_logger_logf(logger, "\n");

    // Recurse.
    CowlClsExpIterator iter = cowl_iterator_init(ctx, for_each_cls);
    return cowl_ontology_iterate_sub_classes(onto, cls, &iter);
}
