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

    // We will be editing the pizza ontology by adding the Porcini pizza.
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
    // memory exhaustion, so you should check their return values.

    // Declaration(Class(pizza:PorciniTopping))
    CowlClass *porcini_topping = cowl_class_from_static(NS "PorciniTopping");
    CowlAnyAxiom *axiom = cowl_decl_axiom(porcini_topping, NULL);
    cowl_ontology_add_axiom(ontology, axiom);
    cowl_release(axiom);

    // Declaration(Class(pizza:Porcini))
    CowlClass *porcini = cowl_class_from_static(NS "Porcini");
    axiom = cowl_decl_axiom(porcini, NULL);
    cowl_ontology_add_axiom(ontology, axiom);
    cowl_release(axiom);

    // SubClassOf(pizza:PorciniTopping pizza:MushroomTopping)
    CowlClass *mushroom_topping = cowl_class_from_static(NS "MushroomTopping");
    axiom = cowl_sub_cls_axiom(porcini_topping, mushroom_topping, NULL);
    cowl_ontology_add_axiom(ontology, axiom);
    cowl_release_all(axiom, mushroom_topping);

    // SubClassOf(pizza:Porcini pizza:NamedPizza)
    CowlClass *named_pizza = cowl_class_from_static(NS "NamedPizza");
    axiom = cowl_sub_cls_axiom(porcini, named_pizza, NULL);
    cowl_ontology_add_axiom(ontology, axiom);
    cowl_release_all(axiom, named_pizza);

    // SubClassOf(pizza:Porcini ObjectSomeValuesFrom(pizza:hasTopping pizza:MozzarellaTopping))
    CowlObjProp *has_topping = cowl_obj_prop_from_static(NS "hasTopping");
    CowlClass *mozzarella_topping = cowl_class_from_static(NS "MozzarellaTopping");
    CowlObjQuant *obj_quant = cowl_obj_quant(COWL_QT_SOME, has_topping, mozzarella_topping);
    axiom = cowl_sub_cls_axiom(porcini, obj_quant, NULL);
    cowl_ontology_add_axiom(ontology, axiom);
    cowl_release_all(axiom, obj_quant, mozzarella_topping);

    // SubClassOf(pizza:Porcini ObjectSomeValuesFrom(pizza:hasTopping pizza:PorciniTopping))
    obj_quant = cowl_obj_quant(COWL_QT_SOME, has_topping, porcini_topping);
    axiom = cowl_sub_cls_axiom(porcini, obj_quant, NULL);
    cowl_ontology_add_axiom(ontology, axiom);
    cowl_release_all(axiom, obj_quant);

    // SubClassOf(pizza:Porcini ObjectAllValuesFrom(pizza:hasTopping
    // ObjectUnionOf(pizza:MozzarellaTopping pizza:PorciniTopping)))
    UVec(CowlObjectPtr) vec = uvec(CowlObjectPtr);
    uvec_push(CowlObjectPtr, &vec, mozzarella_topping);
    uvec_push(CowlObjectPtr, &vec, porcini_topping);
    CowlVector *operands = cowl_vector(&vec);
    CowlNAryBool *closure = cowl_nary_bool(COWL_NT_UNION, operands);
    obj_quant = cowl_obj_quant(COWL_QT_ALL, has_topping, closure);
    axiom = cowl_sub_cls_axiom(porcini, obj_quant, NULL);
    cowl_ontology_add_axiom(ontology, axiom);
    cowl_release_all(axiom, obj_quant, closure, operands, porcini_topping, porcini, has_topping);

    // Serialize the edited ontology to a new file.
    printf("Writing ontology " OUT_PATH "...");

    if (cowl_manager_write_path(manager, ontology, ustring_literal(OUT_PATH))) {
        printf(" failed\n");
    } else {
        printf(" done!\n");
    }

    cowl_release_all(ontology, manager);

    return EXIT_SUCCESS;
}
