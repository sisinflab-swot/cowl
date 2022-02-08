/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_api.h"

static bool count_axiom_iterator(void *ctx, cowl_unused void *obj) {
    (*((ulib_uint *)ctx))++;
    return true;
}

static bool count_primitive_iterator(void *ctx, cowl_unused void *obj) {
    (*((ulib_uint *)ctx))++;
    return true;
}

int main(int argc, char *argv[]) {
    cowl_api_init();

    char const *onto_path = argc > 1 ? argv[1] : "test_onto.owl";
    CowlManager *manager = cowl_manager_get();

    utime_ns t = utime_get_ns();
    CowlOntology *onto = cowl_manager_read_path(manager, onto_path);
    t = utime_get_ns() - t;

    cowl_manager_release(manager);

    if (!onto) {
        printf("Failed to read ontology at path: %s", onto_path);
        return EXIT_FAILURE;
    }

    printf("Ontology parsed in %.2f ms\n", utime_interval_convert(t, UTIME_MILLISECONDS));

    ulib_uint count = 0;

    t = utime_get_ns();
    CowlIterator iter = cowl_iterator_init(&count, count_axiom_iterator);
    cowl_ontology_iterate_axioms(onto, &iter);
    t = utime_get_ns() - t;

    printf("%" ULIB_UINT_FMT " axioms iterated in %.2f us\n",
           count, utime_interval_convert(t, UTIME_MICROSECONDS));

    count = 0;

    t = utime_get_ns();
    iter = cowl_iterator_init(&count, count_primitive_iterator);
    cowl_ontology_iterate_primitives(onto, COWL_PF_ALL, &iter);
    t = utime_get_ns() - t;

    printf("%" ULIB_UINT_FMT " primitives iterated in %.2f us\n",
           count, utime_interval_convert(t, UTIME_MICROSECONDS));

    cowl_ontology_release(onto);

    return EXIT_SUCCESS;
}
