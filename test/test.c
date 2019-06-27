/// @author Ivano Bilenchi

#include <stdio.h>
#include <assert.h>
#include <time.h>

#include "cowl_private.h"

static inline double get_millis(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    return (double)ts.tv_sec * 1000.0 + (double)ts.tv_nsec / 1000000.0;
}

static void test_iri(void) {
    const char ns_string[] = "http://test_namespace.owl#";
    const char rem_string[] = "remainder";

    CowlString *ns = cowl_string_get(ns_string, sizeof(ns_string), false);
    CowlString *rem = cowl_string_get(rem_string, sizeof(rem_string), false);

    CowlIRI *iri = cowl_iri_get(ns, rem);
    assert(cowl_object_ref_get(iri) == 1);
    assert(cowl_object_ref_get(ns) == 3);
    assert(cowl_object_ref_get(rem) == 2);

    cowl_iri_retain(iri);
    assert(cowl_object_ref_get(iri) == 2);

    cowl_iri_release(iri);
    assert(cowl_object_ref_get(iri) == 1);

    cowl_iri_release(iri);
    assert(cowl_object_ref_get(ns) == 2);
    assert(cowl_object_ref_get(rem) == 1);

    cowl_string_release(ns);
    cowl_string_release(rem);
}

static void test_anon_individual(void) {
    CowlNodeID id = cowl_node_id_get_next();
    CowlAnonInd *anon_ind = cowl_anon_ind_get(id);
    assert(cowl_object_ref_get(anon_ind) == 1);

    CowlAnonInd *other_ind = cowl_anon_ind_get(id);
    assert(other_ind == anon_ind);
    assert(cowl_anon_ind_equals(other_ind, anon_ind));
    assert(cowl_object_ref_get(other_ind) == 2);

    cowl_anon_ind_retain(anon_ind);
    assert(cowl_object_ref_get(anon_ind) == 3);

    cowl_anon_ind_release(other_ind);
    assert(cowl_object_ref_get(anon_ind) == 2);

    cowl_anon_ind_release(anon_ind);
    assert(cowl_object_ref_get(anon_ind) == 1);

    cowl_anon_ind_release(anon_ind);
}

static CowlOntology* test_imports_loader(cowl_unused void *ctx, cowl_unused CowlIRI *iri,
                                         Vector(CowlError) *errors) {
    CowlParser *parser = cowl_parser_alloc();
    CowlOntology *onto = cowl_parser_parse_ontology(parser, "test_import.owl");
    vector_deep_append(CowlError, errors, parser->errors, cowl_error_retain);
    cowl_parser_free(parser);
    return onto;
}

static void test_parser(void) {
    CowlLogger *logger = cowl_logger_alloc_console();
    CowlParser *parser = cowl_parser_alloc();

    CowlImportsLoader loader = cowl_imports_loader_init(NULL, test_imports_loader, NULL);
    cowl_parser_set_ontology_loader(parser, loader);

    double start = get_millis();
    CowlOntology *ontology = cowl_parser_parse_ontology(parser, "test_ontology.owl");
    double stop = get_millis();

    if (ontology) cowl_logger_log_ontology(logger, ontology);

    Vector(CowlError) const *errors = cowl_parser_get_errors(parser);
    cowl_logger_logf(logger, "Ontology parsed in %.2f ms with %d errors.\n",
                     stop - start, vector_count(errors));

    vector_foreach(CowlError, errors, error, {
        cowl_logger_log_error(logger, error);
        cowl_logger_logf(logger, "\n");
    });

    cowl_ontology_release(ontology);
    cowl_parser_free(parser);
    cowl_logger_free(logger);
}

int main(void) {
    cowl_api_init();

    test_iri();
    test_anon_individual();
    test_parser();

    return 0;
}
