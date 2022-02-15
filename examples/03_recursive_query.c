/*
 * In this example we will be logging the atomic subclasses
 * of a certain class recursively. Error and import handling are omitted.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 */
#include "cowl_api.h"

#define ONTO_PATH "example_pizza.owl"
#define ONTO_NS "http://www.co-ode.org/ontologies/pizza/pizza.owl#"
#define CLASS_NAME "Food"

static bool for_each_cls(void *ctx, void *cls);

int main(void) {
    cowl_api_init();

    CowlManager *manager = cowl_manager_get();
    CowlOntology *ontology = cowl_manager_read_path(manager, ustring_literal(ONTO_PATH));
    cowl_manager_release(manager);

    if (ontology) {
        CowlClass *cls = cowl_class_from_static(ONTO_NS CLASS_NAME);
        puts("Recursive atomic subclasses of " CLASS_NAME ":\n");

        // Since we are going to perform a recursive query,
        // we need the ontology to be part of the context.
        CowlIterator iter = cowl_iterator_init(ontology, for_each_cls);
        cowl_ontology_iterate_sub_classes(ontology, cls, &iter);

        cowl_class_release(cls);
        cowl_ontology_release(ontology);
    }

    return EXIT_SUCCESS;
}

static bool for_each_cls(void *ctx, void *cls) {
    if (cowl_cls_exp_get_type(cls) != COWL_CET_CLASS) return true;

    // Log the IRI remainder.
    puts(cowl_string_get_cstring(cowl_iri_get_rem(cowl_class_get_iri(cls))));

    // Recurse.
    CowlIterator iter = cowl_iterator_init(ctx, for_each_cls);
    return cowl_ontology_iterate_sub_classes(ctx, cls, &iter);
}
