/*
 * In this example we will be logging the direct atomic subclasses of a certain class.
 * Note that error and imports handling are omitted for the sake of simplicity.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 */
#include "cowl_api.h"

#define ONTO_NS "http://www.co-ode.org/ontologies/pizza/pizza.owl#"
#define CLASS_NAME "Food"

static bool for_each_cls(void *ctx, CowlClsExp *exp);

int main(void) {

    cowl_api_init();
    CowlParser *parser = cowl_parser_get();
    CowlOntology *onto = cowl_parser_parse_ontology(parser, "pizza.owl", NULL);
    cowl_parser_release(parser);

    // Query the parsed ontology
    if (onto) {
        CowlLogger *logger = cowl_logger_console_get();

        // Get the class whose atomic subclasses we're interested in.
        CowlIRI *iri = cowl_iri_from_static(ONTO_NS CLASS_NAME);
        CowlClass *cls = cowl_class_get(iri);

        cowl_logger_logf(logger, "Atomic subclasses of " CLASS_NAME ":\n");

        // Run the query.
        CowlClsExpIterator iter = cowl_iterator_init(logger, for_each_cls);
        cowl_ontology_iterate_sub_classes(onto, cls, &iter);

        // Cleanup.
        cowl_class_release(cls);
        cowl_iri_release(iri);
        cowl_logger_release(logger);
    }

    cowl_ontology_release(onto);

    return 0;
}

// Iterator body, invoked for each class expression matching the query.
static bool for_each_cls(void *ctx, CowlClsExp *exp) {

    // We are only interested in atomic classes.
    if (cowl_cls_exp_get_type(exp) != COWL_CET_CLASS) return true;

    // Pseudo-inheritance allows us to simply cast a class expression to the desired type.
    CowlClass *cls = (CowlClass *)exp;

    // Log the IRI remainder.
    CowlIRI *iri = cowl_class_get_iri(cls);
    cowl_logger_log_string(ctx, cowl_iri_get_rem(iri));
    cowl_logger_logf(ctx, "\n");

    return true;
}
