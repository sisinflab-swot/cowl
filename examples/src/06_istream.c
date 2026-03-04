/*
 * In this example we will be logging the direct atomic subclasses
 * of a certain class, but we will do so without instantiating a
 * CowlOntology object.
 *
 * @note Most errors are not handled for the sake of simplicity.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2023 SisInf Lab, Polytechnic University of Bari
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

// Change handler, invoked for each construct read from the ontology document.
static cowl_ret handle_axiom(void *target_class, CowlChange change) {
    // We are only interested in subclass axioms.
    if (change.part != COWL_PART_AXIOM) return COWL_OK;

    CowlAnyAxiom *axiom = change.value;
    if (cowl_axiom_get_type(axiom) != COWL_AT_SUB_CLASS) return COWL_OK;

    // We are only interested in axioms where the superclass is the target class.
    CowlAnyClsExp *cls = cowl_sub_cls_axiom_get_super(axiom);
    if (!cowl_equals(target_class, cls)) return COWL_OK;

    // We are only interested in axioms where the subclass is atomic.
    cls = cowl_sub_cls_axiom_get_sub(axiom);
    if (cowl_cls_exp_get_type(cls) != COWL_CET_CLASS) return COWL_OK;

    // Log the IRI remainder.
    puts(cowl_string_get_cstring(cowl_get_rem(cls)));
    return COWL_OK;
}

int main(void) {
    cowl_init();

    CowlClass *target_class = cowl_class_from_static(NS CLASS_NAME);

    // Configure the change handler for the incoming stream.
    CowlChangeHandler handler = {
        .ctx = target_class,
        .handle = handle_axiom,
    };

    // Process the ontology document as a stream of changes.
    puts("Atomic subclasses of " CLASS_NAME ":");
    CowlReader *reader = cowl_get_reader();
    if (cowl_reader_read_path(reader, ustring_literal(ONTO), handler)) {
        return EXIT_FAILURE;
    }

    cowl_release(target_class);
    return EXIT_SUCCESS;
}
