/*
 * In this example we will be logging the atomic subclasses of a class recursively.
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

// Custom context struct for the query.
typedef struct CustomContext {
    CowlOntology *onto;
    UOStream *stream;
} CustomContext;

// Iterator body, invoked for each class expression matching the query.
static bool for_each_cls(void *ptr, CowlAny *cls) {
    if (cowl_cls_exp_get_type(cls) != COWL_CET_CLASS) return true;

    // Log the IRI remainder.
    CustomContext *ctx = ptr;
    cowl_write_string(ctx->stream, cowl_iri_get_rem(cowl_class_get_iri(cls)));
    cowl_write_static(ctx->stream, "\n");

    // Recurse.
    CowlIterator iter = { ctx, for_each_cls };
    return cowl_ontology_iterate_sub_classes(ctx->onto, cls, &iter, false);
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

    UOStream *std_out = uostream_std();
    cowl_write_static(std_out, "Recursive atomic subclasses of " CLASS_NAME ":");
    CowlClass *cls = cowl_class_from_static(NS CLASS_NAME);

    // Since we are going to perform a recursive query,
    // we need the ontology to be part of the context.
    CustomContext ctx = { onto, std_out };
    CowlIterator iter = { &ctx, for_each_cls };
    cowl_ontology_iterate_sub_classes(onto, cls, &iter, false);

    cowl_release_all(cls, onto);
    return EXIT_SUCCESS;
}
