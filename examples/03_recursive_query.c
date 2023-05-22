/*
 * In this example we will be logging the atomic subclasses
 * of a certain class recursively. Error and import handling are omitted.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 */
#include "cowl.h"

#define ONTO "example_pizza.owl"
#define NS "http://www.co-ode.org/ontologies/pizza/pizza.owl#"
#define CLASS_NAME "Food"

// Iterator body, invoked for each class expression matching the query.
static bool for_each_cls(void *ctx, CowlAny *cls) {
    if (cowl_cls_exp_get_type(cls) != COWL_CET_CLASS) return true;

    // Log the IRI remainder.
    UOStream *std_out = uostream_std();
    cowl_write_string(std_out, cowl_iri_get_rem(cowl_class_get_iri(cls)));
    cowl_write_static(std_out, "\n");

    // Recurse.
    CowlIterator iter = { ctx, for_each_cls };
    return cowl_ontology_iterate_sub_classes(ctx, cls, &iter, false);
}

int main(void) {
    cowl_init();

    CowlManager *manager = cowl_manager();
    CowlOntology *ontology = cowl_manager_read_path(manager, ustring_literal(ONTO));
    cowl_release(manager);

    if (ontology) {
        puts("Recursive atomic subclasses of " CLASS_NAME ":");
        CowlClass *cls = cowl_class_from_static(NS CLASS_NAME);

        // Since we are going to perform a recursive query,
        // we need the ontology to be part of the context.
        CowlIterator iter = { ontology, for_each_cls };
        cowl_ontology_iterate_sub_classes(ontology, cls, &iter, false);

        cowl_release(cls);
        cowl_release(ontology);
    }

    return EXIT_SUCCESS;
}
