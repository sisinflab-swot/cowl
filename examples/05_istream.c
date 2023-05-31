/*
 * In this example we will be logging the direct atomic subclasses
 * of a certain class, but we will do so without instantiating a
 * CowlOntology object.
 *
 * @note Memory allocation failures are not handled for the sake of simplicity.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2023 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 */
#include "cowl.h"

#define ONTO "example_pizza.owl"
#define NS "http://www.co-ode.org/ontologies/pizza/pizza.owl#"
#define CLASS_NAME "Food"

// Axiom handler, invoked for each axiom in the ontology document.
static cowl_ret handle_axiom(void *target_class, CowlAnyAxiom *axiom) {
    // We are only interested in subclass axioms.
    if (cowl_axiom_get_type(axiom) != COWL_AT_SUB_CLASS) return COWL_OK;

    // We are only interested in axioms where the superclass is the target class.
    CowlAnyClsExp *cls = cowl_sub_cls_axiom_get_super(axiom);
    if (!cowl_equals(target_class, cls)) return COWL_OK;

    // We are only interested in axioms where the subclass is atomic.
    cls = cowl_sub_cls_axiom_get_sub(axiom);
    if (cowl_cls_exp_get_type(cls) != COWL_CET_CLASS) return COWL_OK;

    // Log the IRI remainder.
    puts(cowl_string_get_cstring(cowl_iri_get_rem(cowl_class_get_iri(cls))));
    return COWL_OK;
}

int main(void) {
    cowl_init();

    CowlManager *manager = cowl_manager();
    CowlClass *target_class = cowl_class_from_static(NS CLASS_NAME);

    // Configure the ontology input stream.
    CowlIStreamHandlers handlers = { .ctx = target_class, .axiom = handle_axiom };
    CowlIStream *stream = cowl_manager_get_istream(manager, handlers);

    // Process the ontology as a stream.
    puts("Atomic subclasses of " CLASS_NAME ":");
    if (cowl_istream_process_path(stream, ustring_literal(ONTO))) {
        return EXIT_FAILURE;
    }

    cowl_release_all(manager, target_class, stream);
    return EXIT_SUCCESS;
}
