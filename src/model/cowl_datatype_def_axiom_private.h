/// @author Ivano Bilenchi

#ifndef COWL_DATATYPE_DEF_AXIOM_PRIVATE_H
#define COWL_DATATYPE_DEF_AXIOM_PRIVATE_H

#include "cowl_datatype_def_axiom.h"
#include "cowl_axiom_private.h"

COWL_BEGIN_DECLS

cowl_struct(CowlDatatypeDefAxiom) {
    CowlAxiom super;
    CowlDatatype *datatype;
    CowlDataRange *range;
};

COWL_END_DECLS

#endif // COWL_DATATYPE_DEF_AXIOM_PRIVATE_H
