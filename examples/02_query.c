/*
 * In this example we will be logging the direct atomic subclasses of a class.
 *
 * @note Memory allocation failures are not handled for the sake of simplicity.
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
static bool for_each_cls(void *std_out, CowlAny *cls) {
    // We are only interested in atomic classes. Note that due to pseudo-inheritance
    // this check ensures that the concrete type of 'exp' is CowlClass.
    if (cowl_cls_exp_get_type(cls) != COWL_CET_CLASS) return true;

    // Log the IRI remainder.
    cowl_write_string(std_out, cowl_iri_get_rem(cowl_class_get_iri(cls)));
    cowl_write_static(std_out, "\n");

    return true;
}

int main(void) {
    cowl_init();

    CowlManager *manager = cowl_manager();
    CowlOntology *onto = cowl_manager_read_path(manager, ustring_literal(ONTO));
    cowl_release(manager);

    if (!onto) {
        fprintf(stderr, "Failed to load ontology " ONTO "\n");
        return EXIT_FAILURE;
    }

    // Query the ontology.
    UOStream *std_out = uostream_std();
    cowl_write_static(std_out, "Atomic subclasses of " CLASS_NAME ":\n");

    // Get the class whose atomic subclasses we are interested in.
    CowlClass *cls = cowl_class_from_static(NS CLASS_NAME);

    // Run the query.
    CowlIterator iter = { std_out, for_each_cls };
    cowl_ontology_iterate_sub_classes(onto, cls, &iter, false);

    // Cleanup.
    cowl_release_all(cls, onto);

    return EXIT_SUCCESS;
}
