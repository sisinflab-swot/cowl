/// @author Ivano Bilenchi

#ifndef COWL_NARY_DATA_PROP_AXIOM_PRIVATE_H
#define COWL_NARY_DATA_PROP_AXIOM_PRIVATE_H

#include "cowl_nary_data_prop_axiom.h"
#include "cowl_axiom_private.h"

COWL_BEGIN_DECLS

cowl_struct(CowlNAryDataPropAxiom) {
    CowlAxiom super;
    CowlDataPropExpSet *props;
};


COWL_END_DECLS

#endif // COWL_NARY_DATA_PROP_AXIOM_PRIVATE_H
