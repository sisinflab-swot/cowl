/*
 * In this example we will be logging the atomic subclasses of a class recursively.
 *
 * @note Most errors are not handled for the sake of simplicity.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 */
#include "cowl.h"
#include "ulib.h"
#include <stdio.h>
#include <stdlib.h>

#define ONTO "example_pizza.owl"
#define NS "http://www.co-ode.org/ontologies/pizza/pizza.owl#"
#define CLASS_NAME "Food"

// Custom context struct for the query.
typedef struct CustomContext {
    CowlOntology *onto;
    UOStream *stream;
} CustomContext;

// Iterator body, invoked for each class expression matching the query.
static cowl_ret for_each_cls(void *ptr, CowlAny *cls) {
    if (cowl_cls_exp_get_type(cls) != COWL_CET_CLASS) return COWL_CONTINUE;

    // Log the IRI remainder.
    CustomContext *ctx = ptr;
    cowl_write_string(ctx->stream, cowl_get_rem(cls));
    cowl_write_static(ctx->stream, "\n");

    // Recurse.
    CowlIterator iter = { ctx, for_each_cls };
    return cowl_ontology_iterate_sub_classes(ctx->onto, cls, &iter);
}

int main(void) {
    cowl_init();

    CowlOntology *onto = cowl_ontology_at_path(ustring_literal(ONTO), NULL);

    if (!onto) {
        fprintf(stderr, "Failed to load ontology " ONTO "\n");
        return EXIT_FAILURE;
    }

    CowlClass *cls = cowl_class_from_static(NS CLASS_NAME);
    cowl_write_static(uostream_std(), "Recursive subclasses of " CLASS_NAME ":\n");

    // Since we are going to perform a recursive query,
    // we need the ontology to be part of the context.
    CustomContext ctx = { onto, uostream_std() };
    CowlIterator iter = { &ctx, for_each_cls };
    cowl_ontology_iterate_sub_classes(onto, cls, &iter);

    cowl_release_all(cls, onto);
    return EXIT_SUCCESS;
}
