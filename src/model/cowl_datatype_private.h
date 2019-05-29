/// @author Ivano Bilenchi

#ifndef COWL_DATATYPE_PRIVATE_H
#define COWL_DATATYPE_PRIVATE_H

#include "cowl_datatype.h"
#include "cowl_data_range_private.h"

COWL_BEGIN_DECLS

cowl_struct(CowlDatatype) {
    CowlDataRange super;
    CowlIRI *iri;
};

COWL_END_DECLS

#endif // COWL_DATATYPE_PRIVATE_H
