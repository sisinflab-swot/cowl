/// @author Ivano Bilenchi

#ifndef COWL_ERROR_H
#define COWL_ERROR_H

#include "cowl_std.h"
#include "vector.h"

COWL_BEGIN_DECLS

typedef struct CowlString const CowlString;

typedef enum CowlErrorCode {
    CEC_ONTOLOGY_LOAD,
    CEC_UNSUPPORTED
} CowlErrorCode;

typedef struct CowlError {
    CowlErrorCode code;
    CowlString *description;
    uint32_t line;
} CowlError;

VECTOR_DECL(CowlError);

CowlString* cowl_error_to_string(CowlError error);

COWL_END_DECLS

#endif // COWL_ERROR_H
