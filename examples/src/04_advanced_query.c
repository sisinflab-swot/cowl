/*
 * In this example we will be logging axioms of different types referencing
 * multiple entities.
 *
 * @note Most errors are not handled for the sake of simplicity.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2024 SisInf Lab, Polytechnic University of Bari
 * @copyright <https://swot.sisinflab.poliba.it>
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

int main(void) {
    cowl_init();

    CowlOntology *onto = cowl_ontology_at_path(ustring_literal(ONTO), NULL);

    if (!onto) {
        fprintf(stderr, "Failed to load ontology " ONTO "\n");
        return EXIT_FAILURE;
    }

    cowl_write_literal(uostream_std(), "Matching axioms:\n");
    CowlClass *cls = cowl_class_from_literal(NS CLASS_NAME);
    CowlObjProp *prop = cowl_obj_prop_from_literal(NS PROPERTY_NAME);

    // We want to log all SubClassOf and EquivalentClasses axioms that
    // reference both the class and the property.

    // Note that this query can be done via other functions as well,
    // though using a CowlAxiomFilter is usually more efficient, as it
    // is used to determine the best indexing strategy for the query.
    CowlAxiomFlags types = COWL_AF_SUB_CLASS | COWL_AF_EQUIV_CLASSES;
    CowlAxiomFilter filter = cowl_axiom_filter(types);
    cowl_axiom_filter_add_primitive(&filter, cls);
    cowl_axiom_filter_add_primitive(&filter, prop);

    // Other than using custom iterators, Cowl provides some built-in ones
    // for common tasks. Here we use a set iterator: all axioms matching
    // the filter will be collected in a set, removing any duplicates.
    UHash(CowlObjectPtr) set = uhset(CowlObjectPtr);
    CowlIterator iter = cowl_iterator_set(&set, false);
    cowl_ontology_iterate_axioms_matching(onto, &filter, &iter);

    // [Optional] Adding the pizza prefix to the default prefix map
    // allows for more concise IRIs when logging the axioms.
    CowlPrefixMap *pm = cowl_get_prefix_map();
    UString const prefix = ustring_literal("pizza");
    UString const ns = ustring_literal(NS);
    cowl_prefix_map_add_raw(pm, prefix, ns, false);

    // We can now log the axioms by iterating over the set.
    UOStream *stream = uostream_std();
    uhash_foreach (CowlObjectPtr, &set, item) {
        cowl_write(stream, *item.key);
        cowl_write_literal(stream, "\n");
    }

    uhash_deinit(CowlObjectPtr, &set);
    cowl_release_all(cls, prop, onto);
    return EXIT_SUCCESS;
}
