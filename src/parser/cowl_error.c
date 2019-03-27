/// @author Ivano Bilenchi

#include "cowl_error_private.h"
#include "cowl_string_private.h"

static char const *const cowl_error_code_descriptions[] = {
    "Unable to load ontology",
    "Unsupported construct"
};

VECTOR_IMPL(CowlError);

CowlString* cowl_error_to_string(CowlError error) {
    return cowl_string_with_format("Error %d (line %d) - %s: %s",
                                   error.code,
                                   error.line,
                                   cowl_error_code_descriptions[error.code],
                                   error.description->cstring);
}
