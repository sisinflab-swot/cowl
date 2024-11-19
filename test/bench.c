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
    char const *out_path = argc > 2 ? argv[2] : "test_out.owl";

    CowlManager *manager = cowl_manager();

    utime_ns t = utime_get_ns();
    CowlOntology *onto = cowl_manager_read_path(manager, ustring_wrap_buf(path));
    t = utime_get_ns() - t;

    if (!onto) {
        printf("Failed to read ontology at path: %s\n", path);
        return EXIT_FAILURE;
    }

    printf("Ontology read in %.2f ms\n", utime_interval_convert(t, UTIME_MILLISECONDS));

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

    t = utime_get_ns();
    cowl_ret ret = cowl_manager_write_path(manager, onto, ustring_wrap_buf(out_path));
    t = utime_get_ns() - t;

    if (ret) {
        printf("Failed to write ontology at path: %s\n", out_path);
    } else {
        printf("Ontology written in %.2f ms\n", utime_interval_convert(t, UTIME_MILLISECONDS));
    }

    cowl_release_all(manager, onto);

    return EXIT_SUCCESS;
}
