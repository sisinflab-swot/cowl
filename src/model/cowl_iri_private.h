/// @author Ivano Bilenchi

#ifndef COWL_IRI_PRIVATE_H
#define COWL_IRI_PRIVATE_H

#include "cowl_iri.h"
#include "cowl_object.h"

COWL_BEGIN_DECLS

cowl_struct(CowlIRI) {
    CowlObject super;
    CowlString *ns;
    CowlString *rem;
};

#define COWL_IRI_INIT(NS, REM) { .super = COWL_OBJECT_INIT, .ns = (NS), .rem = (REM) }

COWL_END_DECLS

#endif // COWL_IRI_PRIVATE_H
