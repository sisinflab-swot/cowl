/// @author Ivano Bilenchi

#include <stdio.h>
#include <assert.h>

#include "cowl_anon_individual_private.h"
#include "cowl_individual_private.h"
#include "cowl_iri_private.h"
#include "cowl_string_private.h"
#include "cowl_parser.h"

#pragma mark - Tests

void test_iri(void) {
    const char ns_string[] = "http://test_namespace.owl#";
    const char rem_string[] = "remainder";

    CowlString *ns = cowl_string_get(ns_string, sizeof(ns_string), false);
    CowlString *rem = cowl_string_get(rem_string, sizeof(rem_string), false);

    CowlIRI *iri = cowl_iri_get(ns, rem);
    assert(cowl_iri_ref_get(iri) == 1);
    assert(cowl_string_ref_get(ns) == 2);
    assert(cowl_string_ref_get(rem) == 2);

    cowl_iri_retain(iri);
    assert(cowl_iri_ref_get(iri) == 2);

    cowl_iri_release(iri);
    assert(cowl_iri_ref_get(iri) == 1);

    cowl_iri_release(iri);
    assert(cowl_string_ref_get(ns) == 1);
    assert(cowl_string_ref_get(rem) == 1);

    cowl_string_release(ns);
    cowl_string_release(rem);
}

void test_anon_individual(void) {
    char const id_str[] = "_:12345";
    CowlString *id = cowl_string_get(id_str, sizeof(id_str) - 1, false);
    assert(cowl_string_ref_get(id) == 1);

    CowlAnonIndividual *anon_ind = cowl_anon_individual_get(id);
    assert(cowl_individual_ref_get(anon_ind) == 1);
    assert(cowl_string_ref_get(id) == 2);

    CowlAnonIndividual *other_ind = cowl_anon_individual_get(id);
    assert(other_ind == anon_ind);
    assert(cowl_anon_individual_equals(other_ind, anon_ind));
    assert(cowl_individual_ref_get(other_ind) == 2);

    cowl_anon_individual_retain(anon_ind);
    assert(cowl_individual_ref_get(anon_ind) == 3);

    cowl_anon_individual_release(other_ind);
    assert(cowl_individual_ref_get(anon_ind) == 2);

    cowl_anon_individual_release(anon_ind);
    assert(cowl_individual_ref_get(anon_ind) == 1);

    cowl_anon_individual_release(anon_ind);
    assert(cowl_string_ref_get(id) == 1);

    cowl_string_release(id);
}

void test_parser(void) {
    cowl_parse_ontology("test_ontology.owl");
}

#pragma mark - Main

int main(void) {
    test_iri();
    test_anon_individual();
    test_parser();
    return 0;
}
