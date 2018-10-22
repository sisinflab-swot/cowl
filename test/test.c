/// @author Ivano Bilenchi

#include <stdio.h>
#include <assert.h>

#include "cowl.h"
#include "cowl_individual_private.h"
#include "cowl_string_private.h"

#pragma mark - Tests

void test_iri(void) {
    const char ns_string[] = "http://test_namespace.owl#";
    const char rem_string[] = "remainder";

    CowlString const *ns = cowl_string_get(ns_string, sizeof(ns_string), false);
    CowlString const *ns2 = cowl_string_get(ns_string, sizeof(ns_string), false);

    assert(cowl_string_equals(ns, ns2));
    cowl_string_release(ns2);

    CowlString const *rem = cowl_string_get(rem_string, sizeof(rem_string), false);
    assert(!cowl_string_equals(ns, rem));

    CowlIRI const *iri = cowl_iri_get(ns, rem);
    printf("IRI: %s%s\n",
           cowl_string_cstring(cowl_iri_get_ns(iri)),
           cowl_string_cstring(cowl_iri_get_rem(iri)));

    cowl_string_release(ns);
    cowl_string_release(rem);
    cowl_iri_release(iri);
}

void test_anon_individual(void) {
    char const id_str[] = ":12345";
    CowlString const *id = cowl_string_get(id_str, sizeof(id_str) - 1, false);
    assert(cowl_string_ref_get(id) == 1);

    CowlAnonIndividual const *anon_ind = cowl_anon_individual_get(id);
    assert(cowl_individual_ref_get(anon_ind) == 1);
    assert(cowl_string_ref_get(id) == 2);

    CowlAnonIndividual const *other_ind = cowl_anon_individual_get(id);
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

#pragma mark - Main

int main(void) {
    test_iri();
    test_anon_individual();
    return 0;
}
