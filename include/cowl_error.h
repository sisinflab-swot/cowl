/// @author Ivano Bilenchi

#ifndef COWL_ERROR_H
#define COWL_ERROR_H

#include "cowl_std.h"
#include "vector.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlString);

typedef enum CowlErrorCode {
    COWL_ERR_ONTOLOGY_LOAD,
    COWL_ERR_SYNTAX
} CowlErrorCode;

typedef cowl_struct(CowlError) {
    cowl_uint_t line;
    CowlErrorCode code;
    CowlString *description;
} CowlError;

VECTOR_DECL(CowlError)

#define cowl_error_init(CODE, CSTR, LINE) ((CowlError) {                                            \
    .code = (CODE),                                                                                 \
    .description = cowl_string_get((CSTR), (cowl_uint_t)strlen(CSTR), false),                       \
    .line = (LINE)                                                                                  \
})

CowlError cowl_error_retain(CowlError error);
void cowl_error_release(CowlError error);

CowlString* cowl_error_to_string(CowlError error);

COWL_END_DECLS

#endif // COWL_ERROR_H
