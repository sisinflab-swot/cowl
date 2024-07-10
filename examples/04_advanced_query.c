/*
 * In this example we will be logging axioms of different types referencing
 * multiple entities.
 *
 * @note Memory allocation failures are not handled for the sake of simplicity.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2024 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 */
#include "cowl.h"
#include "cowl_axiom_filter.h"
#include "cowl_axiom_flags.h"
#include "cowl_obj_prop.h"
#include "cowl_writer.h"
#include "ulib.h"
#include <stdio.h>
#include <stdlib.h>

#define ONTO "example_pizza.owl"
#define NS "http://www.co-ode.org/ontologies/pizza/pizza.owl#"
#define CLASS_NAME "ThinAndCrispyBase"
#define PROPERTY_NAME "hasBase"

// Iterator body, invoked for each axiom matching the query.
static bool for_each_axiom(void *stream, CowlAny *axiom) {
    cowl_write(stream, axiom);
    cowl_write_static(stream, "\n");
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

    UOStream *std_out = uostream_std();
    cowl_write_static(std_out, "Matching axioms:\n");
    CowlClass *cls = cowl_class_from_static(NS CLASS_NAME);
    CowlObjProp *prop = cowl_obj_prop_from_static(NS PROPERTY_NAME);

    // We want to log all SubClassOf and EquivalentClasses axioms that reference
    // both the class and the property.

    // Note that this can be done via other query functions as well, though
    // using a CowlAxiomFilter is usually more efficient, as it is used
    // internally to determine the best indexing strategy for the query.
    CowlAxiomFlags types = COWL_AF_SUB_CLASS | COWL_AF_EQUIV_CLASSES;
    CowlAxiomFilter filter = cowl_axiom_filter(types);
    cowl_axiom_filter_add_primitive(&filter, cls);
    cowl_axiom_filter_add_primitive(&filter, prop);

    CowlIterator iter = { std_out, for_each_axiom };
    cowl_ontology_iterate_axioms_matching(onto, &filter, &iter, false);

    cowl_axiom_filter_deinit(&filter);
    cowl_release_all(cls, prop, onto);
    return EXIT_SUCCESS;
}
