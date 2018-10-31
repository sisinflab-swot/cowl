/// @author Ivano Bilenchi

#ifndef COWL_DATATYPE_PRIVATE_H
#define COWL_DATATYPE_PRIVATE_H

#include "cowl_datatype.h"

COWL_BEGIN_DECLS

struct CowlDatatype {
    uint32_t ref_count;
    CowlIRI *iri;
};

#define COWL_DATATYPE_INIT(IRI) { .ref_count = 1, .iri = (IRI) }

#define cowl_datatype_ref_get(i) (((struct CowlDatatype *)(i))->ref_count)
#define cowl_datatype_ref_incr(i) (++cowl_datatype_ref_get(i), (i))
#define cowl_datatype_ref_decr(i) (--cowl_datatype_ref_get(i))

COWL_END_DECLS

#endif // COWL_DATATYPE_PRIVATE_H
