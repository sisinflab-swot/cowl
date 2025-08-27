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
#include <stdlib.h>

static bool count_constructs(void *ctx, cowl_unused CowlAny *obj) {
    (*((ulib_uint *)ctx))++;
    return true;
}

int main(int argc, char *argv[]) {
    ulog_main->level = ULOG_PERF;

    int exit_code = EXIT_FAILURE;
    CowlOntology *onto = NULL;

    if (cowl_init()) {
        ulog_error("Could not initialize Cowl");
        goto end;
    }

    char const *path = argc > 1 ? argv[1] : "test_onto.owl";
    char const *out_path = argc > 2 ? argv[2] : "test_out.owl";

    ulog_perf("Read ontology") {
        if (!(onto = cowl_ontology_at_path(ustring_wrap_buf(path)))) {
            ulog_error("Could not read ontology: %s", path);
            goto end;
        }
    }

    ulib_uint count = 0;
    CowlIterator iter = { &count, count_constructs };
    ulog_perf("Retrieve %" ULIB_UINT_FMT " axioms", count) {
        cowl_ontology_iterate_axioms(onto, &iter);
    }

    count = 0;
    ulog_perf("Retrieve %" ULIB_UINT_FMT " primitives", count) {
        cowl_ontology_iterate_primitives(onto, COWL_PF_ALL, &iter);
    }

    ulog_perf("Write ontology") {
        if (cowl_ontology_to_path(onto, ustring_wrap_buf(out_path))) {
            ulog_error("Could not write ontology: %s", out_path);
            goto end;
        }
    }

    exit_code = EXIT_SUCCESS;

end:
#if __SANITIZE_ADDRESS__
    cowl_release_all(onto);
    cowl_deinit();
#endif

    return exit_code;
}
