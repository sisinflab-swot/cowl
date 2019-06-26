/// @author Ivano Bilenchi

#include "cowl_error.h"
#include "cowl_string_private.h"

VECTOR_IMPL(CowlError)

CowlError cowl_error_retain(CowlError error) {
    cowl_string_retain(error.description);
    return error;
}

void cowl_error_release(CowlError error) {
    cowl_string_release(error.description);
}

CowlString* cowl_error_to_string(CowlError error) {
    static char const *const cowl_error_code_descriptions[] = {
        "Unable to load ontology",
        "Unsupported construct"
    };

    return cowl_string_with_format("Error %d (line %d) - %s: %s",
                                   error.code,
                                   error.line,
                                   cowl_error_code_descriptions[error.code],
                                   error.description->cstring);
}
