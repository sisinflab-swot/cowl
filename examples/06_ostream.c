/*
 * In this example we will be creating a new ontology document by using an
 * ontology output stream.
 *
 * @note Memory allocation failures are not handled for the sake of simplicity.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2023 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl.h"

#define PATH "porcini_pizza.owl"

#define IMPORT_IRI "http://www.co-ode.org/ontologies/pizza"
#define IMPORT_NS IMPORT_IRI "/pizza.owl#"

#define IRI "http://foo.com/ontologies/porcini_pizza"
#define NS IRI "/porcini_pizza.owl#"

int main(void) {
    cowl_init();

    printf("Generating ontology " PATH "... ");

    UOStream ostream;
    if (uostream_to_path(&ostream, PATH)) {
        // Initializing and writing to the stream may fail.
        // You should handle IO errors as fit for your application.
        goto err_io;
    }

    CowlManager *manager = cowl_manager();
    CowlOStream *stream = cowl_manager_get_ostream(manager, &ostream);
    cowl_release(manager);

    // Optional: setup prefixes so that IRIs can be rendered in their prefixed form.
    CowlSymTable *st = cowl_ostream_get_sym_table(stream);
    cowl_sym_table_register_prefix_raw(st, ustring_literal(""), ustring_literal(NS),
                                       false);
    cowl_sym_table_register_prefix_raw(st, ustring_literal("pizza"),
                                       ustring_literal(IMPORT_NS), false);

    // Write the ontology header.
    CowlIRI *iri = cowl_iri_from_static(IRI);
    CowlIRI *import_iri = cowl_iri_from_static(IMPORT_IRI);
    UVec(CowlObjectPtr) imports = uvec(CowlObjectPtr);
    uvec_push(CowlObjectPtr, &imports, import_iri);

    CowlOntologyHeader header = {
        .id = { iri },
        .imports = &imports,
    };

    if (cowl_ostream_write_header(stream, header)) goto err_io;

    cowl_release_all(iri, import_iri);
    uvec_deinit(CowlObjectPtr, &imports);

    // Write the axioms.
    // Declaration(Class(:PorciniTopping))
    CowlClass *porcini = cowl_class_from_static(NS "PorciniTopping");
    CowlAnyAxiom *axiom = cowl_decl_axiom(porcini, NULL);
    if (cowl_ostream_write_axiom(stream, axiom)) goto err_io;
    cowl_release(axiom);

    // Declaration(Class(:Porcini))
    CowlClass *porcini_pizza = cowl_class_from_static(NS "Porcini");
    axiom = cowl_decl_axiom(porcini_pizza, NULL);
    if (cowl_ostream_write_axiom(stream, axiom)) goto err_io;
    cowl_release(axiom);

    // SubClassOf(:PorciniTopping pizza:MushroomTopping)
    CowlClass *mushroom = cowl_class_from_static(IMPORT_NS "MushroomTopping");
    axiom = cowl_sub_cls_axiom(porcini, mushroom, NULL);
    if (cowl_ostream_write_axiom(stream, axiom)) goto err_io;
    cowl_release_all(axiom, mushroom);

    // SubClassOf(:Porcini pizza:NamedPizza)
    CowlClass *named_pizza = cowl_class_from_static(IMPORT_NS "NamedPizza");
    axiom = cowl_sub_cls_axiom(porcini_pizza, named_pizza, NULL);
    if (cowl_ostream_write_axiom(stream, axiom)) goto err_io;
    cowl_release_all(axiom, named_pizza);

    // SubClassOf(:Porcini
    // ObjectSomeValuesFrom(pizza:hasTopping pizza:MozzarellaTopping))
    CowlObjProp *has_topping = cowl_obj_prop_from_static(IMPORT_NS "hasTopping");
    CowlClass *mozzarella = cowl_class_from_static(IMPORT_NS "MozzarellaTopping");
    CowlObjQuant *obj_quant = cowl_obj_quant(COWL_QT_SOME, has_topping, mozzarella);
    axiom = cowl_sub_cls_axiom(porcini_pizza, obj_quant, NULL);
    if (cowl_ostream_write_axiom(stream, axiom)) goto err_io;
    cowl_release_all(axiom, obj_quant, mozzarella);

    // SubClassOf(:Porcini
    // ObjectSomeValuesFrom(pizza:hasTopping :PorciniTopping))
    obj_quant = cowl_obj_quant(COWL_QT_SOME, has_topping, porcini);
    axiom = cowl_sub_cls_axiom(porcini_pizza, obj_quant, NULL);
    if (cowl_ostream_write_axiom(stream, axiom)) goto err_io;
    cowl_release_all(axiom, obj_quant);

    // SubClassOf(:Porcini ObjectAllValuesFrom(pizza:hasTopping
    // ObjectUnionOf(pizza:MozzarellaTopping :PorciniTopping)))
    UVec(CowlObjectPtr) vec = uvec(CowlObjectPtr);
    uvec_push(CowlObjectPtr, &vec, mozzarella);
    uvec_push(CowlObjectPtr, &vec, porcini);
    CowlVector *operands = cowl_vector(&vec);
    CowlNAryBool *closure = cowl_nary_bool(COWL_NT_UNION, operands);
    obj_quant = cowl_obj_quant(COWL_QT_ALL, has_topping, closure);
    axiom = cowl_sub_cls_axiom(porcini_pizza, obj_quant, NULL);
    if (cowl_ostream_write_axiom(stream, axiom)) goto err_io;
    cowl_release_all(axiom, obj_quant, closure, operands, porcini, porcini_pizza,
                     has_topping);

    // Finally, write the footer.
    if (cowl_ostream_write_footer(stream)) goto err_io;

    puts("done!");
    cowl_release(stream);
    return EXIT_SUCCESS;

err_io:
    puts("failed");
    return EXIT_FAILURE;
}
