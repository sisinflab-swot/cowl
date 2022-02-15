/*
 * In this example we will be logging the direct atomic subclasses
 * of a certain class. Note that error and import handling are omitted
 * for the sake of simplicity.
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

    // Query the ontology
    if (ontology) {
        // Get the class whose atomic subclasses we are interested in.
        CowlClass *cls = cowl_class_from_static(ONTO_NS CLASS_NAME);
        printf("Atomic subclasses of " CLASS_NAME ":\n");

        // Run the query.
        CowlIterator iter = cowl_iterator_init(NULL, for_each_cls);
        cowl_ontology_iterate_sub_classes(ontology, cls, &iter);

        // Cleanup.
        cowl_class_release(cls);
        cowl_ontology_release(ontology);
    }

    return EXIT_SUCCESS;
}

// Iterator body, invoked for each class expression matching the query.
static bool for_each_cls(cowl_unused void *ctx, void *cls) {
    // We are only interested in atomic classes. Note that, due to pseudo-inheritance,
    // this check ensures that the concrete type of 'exp' is CowlClass.
    if (cowl_cls_exp_get_type(cls) != COWL_CET_CLASS) return true;

    // Log the IRI remainder.
    puts(cowl_string_get_cstring(cowl_iri_get_rem(cowl_class_get_iri(cls))));

    return true;
}
