/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_api.h"

#include <stdio.h>
#include <time.h>

#ifdef CLOCK_MONOTONIC_RAW
    #define COWL_CLOCK CLOCK_MONOTONIC_RAW
#else
    #define COWL_CLOCK CLOCK_MONOTONIC
#endif

static inline uint64_t get_nanos(void) {
    struct timespec ts;
    clock_gettime(COWL_CLOCK, &ts);
    return (uint64_t)ts.tv_sec * 1000000000 + (uint64_t)ts.tv_nsec;
}

static inline double get_micros(void) {
    return ((double)get_nanos()) / 1000.0;
}

static inline double get_millis(void) {
    return ((double)get_nanos()) / 1000000.0;
}

static bool count_axiom_iterator(void *ctx, cowl_unused void *obj) {
    (*((cowl_uint *)ctx))++;
    return true;
}

static bool count_primitive_iterator(void *ctx, cowl_unused void *obj) {
    (*((cowl_uint *)ctx))++;
    return true;
}

int main(int argc, char *argv[]) {
    cowl_api_init();

    char const *onto_path = argc > 1 ? argv[1] : "test_onto.owl";
    CowlParser *parser = cowl_parser_get();

    double start = get_millis();
    CowlOntology *onto = cowl_parser_parse_ontology(parser, onto_path, NULL);
    double stop = get_millis();

    cowl_parser_release(parser);

    if (!onto) {
        printf("Failed to parse ontology at path: %s", onto_path);
        return EXIT_FAILURE;
    }

    printf("Ontology parsed in %.2f ms\n", stop - start);

    cowl_uint count = 0;

    start = get_micros();
    CowlIterator iter = cowl_iterator_init(&count, count_axiom_iterator);
    cowl_ontology_iterate_axioms(onto, &iter);
    stop = get_micros();

    printf("%" COWL_UINT_FMT " axioms iterated in %.2f us\n", count, stop - start);

    count = 0;

    start = get_micros();
    iter = cowl_iterator_init(&count, count_primitive_iterator);
    cowl_ontology_iterate_primitives(onto, &iter);
    stop = get_micros();

    printf("%" COWL_UINT_FMT " primitives iterated in %.2f us\n", count, stop - start);

    cowl_ontology_release(onto);

    return EXIT_SUCCESS;
}
