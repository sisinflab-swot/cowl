/*
 * This example demonstrates ontology editing and serialization to file.
 * Error and import handling are deliberately omitted.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 */
#include "cowl.h"

#define IN_PATH "example_pizza.owl"
#define OUT_PATH "example_pizza_new.owl"
#define NS "http://www.co-ode.org/ontologies/pizza/pizza.owl#"

int main(void) {
    cowl_init();

    // We will be editing the pizza ontology by adding a new type of pizza.
    printf("Reading ontology " IN_PATH "...");
    CowlManager *manager = cowl_manager();
    CowlOntology *ontology = cowl_manager_read_path(manager, ustring_literal(IN_PATH));

    if (ontology) {
        printf(" done!\n");
    } else {
        printf(" failed\n");
        return EXIT_FAILURE;
    }

    // Note that most of the following function calls can fail due to
    // memory exhaustion, so you should always check their return values.
    CowlClass *my_pizza = cowl_class_from_static(NS "MyPizza");
    CowlClass *pizza = cowl_class_from_static(NS "Pizza");

    // We first declare the new class.
    CowlAnyAxiom *axiom = cowl_decl_axiom(my_pizza, NULL);
    cowl_ontology_add_axiom(ontology, axiom);
    cowl_decl_axiom_release(axiom);

    // Then we state that it is a subclass of 'Pizza'.
    axiom = cowl_sub_cls_axiom(my_pizza, pizza, NULL);
    cowl_ontology_add_axiom(ontology, axiom);
    cowl_sub_cls_axiom_release(axiom);

    // Finally we serialize the edited ontology to a new file.
    printf("Writing ontology " OUT_PATH "...");

    if (cowl_manager_write_path(manager, ontology, ustring_literal(OUT_PATH))) {
        printf(" failed\n");
    } else {
        printf(" done!\n");
    }

    cowl_release(my_pizza);
    cowl_release(pizza);
    cowl_release(ontology);
    cowl_release(manager);

    return EXIT_SUCCESS;
}
