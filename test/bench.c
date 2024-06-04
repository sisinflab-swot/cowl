/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl.h"
#include "ulib.h"
#include <stdio.h>
#include <stdlib.h>

static bool count_constructs(void *ctx, cowl_unused CowlAny *obj) {
    (*((ulib_uint *)ctx))++;
    return true;
}

int main(int argc, char *argv[]) {
    cowl_init();

    char const *path = argc > 1 ? argv[1] : "test_onto.owl";
    CowlManager *manager = cowl_manager();

    utime_ns t = utime_get_ns();
    CowlOntology *onto = cowl_manager_read_path(manager, ustring_wrap_buf(path));
    t = utime_get_ns() - t;

    cowl_release(manager);

    if (!onto) {
        printf("Failed to read ontology at path: %s", path);
        return EXIT_FAILURE;
    }

    printf("Ontology parsed in %.2f ms\n", utime_interval_convert(t, UTIME_MILLISECONDS));

    ulib_uint count = 0;
    CowlIterator iter = { &count, count_constructs };

    t = utime_get_ns();
    cowl_ontology_iterate_axioms(onto, &iter, false);
    t = utime_get_ns() - t;

    printf("%" ULIB_UINT_FMT " axioms iterated in %.2f us\n", count,
           utime_interval_convert(t, UTIME_MICROSECONDS));

    count = 0;

    t = utime_get_ns();
    cowl_ontology_iterate_primitives(onto, COWL_PF_ALL, &iter, false);
    t = utime_get_ns() - t;

    printf("%" ULIB_UINT_FMT " primitives iterated in %.2f us\n", count,
           utime_interval_convert(t, UTIME_MICROSECONDS));

    cowl_release(onto);

    return EXIT_SUCCESS;
}
