/// @author Ivano Bilenchi

#include <stdio.h>
#include <assert.h>

#include "cowl.h"

#pragma mark - Tests

#pragma mark - Main

int main(void) {
    const char ns_string[] = "http://test_namespace.owl#";
    const char rem_string[] = "remainder";

    CowlString *ns = cowl_string_get(ns_string, sizeof(ns_string), false);
    CowlString *ns2 = cowl_string_get(ns_string, sizeof(ns_string), false);
    
    assert(cowl_string_equals(ns, ns2));
    cowl_string_release(ns);

    CowlString *rem = cowl_string_get(rem_string, sizeof(rem_string), false);
    assert(!cowl_string_equals(ns, rem));
    
    CowlIRI *iri = cowl_iri_alloc(ns, rem);
    printf("IRI: %s%s\n", cowl_string_cstring(iri->ns), cowl_string_cstring(iri->rem));
    cowl_iri_free(iri);
    
    return 0;
}
