/*
 * In this example we will be creating a new ontology document by using an
 * ontology output stream.
 *
 * @note Most errors are not handled for the sake of simplicity.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2023 SisInf Lab, Polytechnic University of Bari
 * @copyright <https://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 */

#include "cowl.h"
#include "ulib.h"
#include <stdio.h>
#include <stdlib.h>

#define PATH "porcini_pizza.owl"

#define IMPORT_IRI "http://www.co-ode.org/ontologies/pizza"
#define IMPORT_NS IMPORT_IRI "/pizza.owl#"

#define IRI "http://example.com/ontologies/porcini_pizza"
#define NS IRI "/porcini_pizza.owl#"

int main(void) {
    cowl_init();

    printf("Generating ontology " PATH "... ");

    UOStream ostream;
    if (uostream_to_path(&ostream, PATH)) {
        // Initializing and writing to the stream may fail.
        // IO errors should be handled as fit for the application.
        goto err_io;
    }

    CowlWriter *writer = cowl_get_writer();

    // Optional: setup prefixes so that IRIs can be rendered in their prefixed form.
    CowlPrefixMap *map = cowl_prefix_map();
    cowl_prefix_map_add_raw(map, ustring_literal(""), ustring_literal(NS), false);
    cowl_prefix_map_add_raw(map, ustring_literal("pizza"),
                            ustring_literal(IMPORT_NS), false);

    // Write the ontology header.
    CowlIRI *iri = cowl_iri_from_literal(IRI);
    CowlIRI *import_iri = cowl_iri_from_literal(IMPORT_IRI);
    UVec(CowlObjectPtr) imports = uvec(CowlObjectPtr);
    uvec_push(CowlObjectPtr, &imports, import_iri);

    CowlOntologyHeader header = {
        .pm = map,
        .iri = iri,
        .imports = &imports,
    };

    if (cowl_writer_write_header(writer, &ostream, header)) goto err_io;

    cowl_release_all(iri, import_iri, map);
    uvec_deinit(CowlObjectPtr, &imports);

    // Write the axioms.
    // Declaration(Class(:PorciniTopping))
    CowlClass *porcini = cowl_class_from_literal(NS "PorciniTopping");
    CowlAnyAxiom *axiom = cowl_decl_axiom(porcini, NULL);
    if (cowl_writer_write_axiom(writer, &ostream, axiom)) goto err_io;
    cowl_release(axiom);

    // Declaration(Class(:Porcini))
    CowlClass *porcini_pizza = cowl_class_from_literal(NS "Porcini");
    axiom = cowl_decl_axiom(porcini_pizza, NULL);
    if (cowl_writer_write_axiom(writer, &ostream, axiom)) goto err_io;
    cowl_release(axiom);

    // SubClassOf(:PorciniTopping pizza:MushroomTopping)
    CowlClass *mushroom = cowl_class_from_literal(IMPORT_NS "MushroomTopping");
    axiom = cowl_sub_cls_axiom(porcini, mushroom, NULL);
    if (cowl_writer_write_axiom(writer, &ostream, axiom)) goto err_io;
    cowl_release_all(axiom, mushroom);

    // SubClassOf(:Porcini pizza:NamedPizza)
    CowlClass *named_pizza = cowl_class_from_literal(IMPORT_NS "NamedPizza");
    axiom = cowl_sub_cls_axiom(porcini_pizza, named_pizza, NULL);
    if (cowl_writer_write_axiom(writer, &ostream, axiom)) goto err_io;
    cowl_release_all(axiom, named_pizza);

    // SubClassOf(:Porcini
    // ObjectSomeValuesFrom(pizza:hasTopping pizza:MozzarellaTopping))
    CowlObjProp *has_topping = cowl_obj_prop_from_literal(IMPORT_NS "hasTopping");
    CowlClass *mozzarella = cowl_class_from_literal(IMPORT_NS "MozzarellaTopping");
    CowlObjQuant *obj_quant = cowl_obj_quant(COWL_QT_SOME, has_topping, mozzarella);
    axiom = cowl_sub_cls_axiom(porcini_pizza, obj_quant, NULL);
    if (cowl_writer_write_axiom(writer, &ostream, axiom)) goto err_io;
    cowl_release_all(axiom, obj_quant);

    // SubClassOf(:Porcini
    // ObjectSomeValuesFrom(pizza:hasTopping :PorciniTopping))
    obj_quant = cowl_obj_quant(COWL_QT_SOME, has_topping, porcini);
    axiom = cowl_sub_cls_axiom(porcini_pizza, obj_quant, NULL);
    if (cowl_writer_write_axiom(writer, &ostream, axiom)) goto err_io;
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
    if (cowl_writer_write_axiom(writer, &ostream, axiom)) goto err_io;
    cowl_release_all(axiom, obj_quant, closure, operands, porcini, porcini_pizza,
                     has_topping, mozzarella);

    // Finally, write the footer.
    if (cowl_writer_write_footer(writer, &ostream)) goto err_io;
    uostream_deinit(&ostream);

    puts("done!");
    return EXIT_SUCCESS;

err_io:
    puts("failed");
    return EXIT_FAILURE;
}
