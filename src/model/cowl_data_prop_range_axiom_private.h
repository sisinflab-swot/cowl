/// @author Ivano Bilenchi

#ifndef COWL_DATA_PROP_RANGE_AXIOM_PRIVATE_H
#define COWL_DATA_PROP_RANGE_AXIOM_PRIVATE_H

#include "cowl_data_prop_range_axiom.h"
#include "cowl_axiom_private.h"

COWL_BEGIN_DECLS

cowl_axiom_struct(CowlDataPropRangeAxiom,
    CowlDataPropExp *prop_exp;
    CowlDataRange *range;
);

COWL_END_DECLS

#endif // COWL_DATA_PROP_RANGE_AXIOM_PRIVATE_H
