/*
 * In this example we will be logging the direct atomic subclasses of a class.
 *
 * @note Most errors are not handled for the sake of simplicity.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <https://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 */
#include "cowl.h"
#include "ulib.h"
#include <stdio.h>
#include <stdlib.h>

#define ONTO "example_pizza.owl"
#define NS "http://www.co-ode.org/ontologies/pizza/pizza.owl#"
#define CLASS_NAME "Food"

// Iterator body, invoked for each class expression matching the query.
static cowl_ret for_each_cls(void *std_out, CowlAny *cls) {
    // We are only interested in atomic classes. Note that due to pseudo-inheritance
    // this check ensures that the concrete type of 'exp' is CowlClass.
    if (cowl_cls_exp_get_type(cls) == COWL_CET_CLASS) {
        cowl_write_string(std_out, cowl_get_rem(cls));
        cowl_write_literal(std_out, "\n");
    }
    return COWL_CONTINUE;
}

int main(void) {
    cowl_init();

    CowlOntology *onto = cowl_ontology_at_path(ustring_literal(ONTO), NULL);

    if (!onto) {
        fprintf(stderr, "Failed to load ontology " ONTO "\n");
        return EXIT_FAILURE;
    }

    // Get the class whose atomic subclasses we are interested in.
    CowlClass *cls = cowl_class_from_literal(NS CLASS_NAME);

    // Run the query.
    cowl_write_literal(uostream_std(), "Subclasses of " CLASS_NAME ":\n");

    CowlIterator iter = { uostream_std(), for_each_cls };
    cowl_ontology_iterate_sub_classes(onto, cls, &iter);

    // Cleanup.
    cowl_release_all(cls, onto);

    return EXIT_SUCCESS;
}
