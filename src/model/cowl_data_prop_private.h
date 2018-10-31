/// @author Ivano Bilenchi

#ifndef COWL_DATA_PROP_PRIVATE_H
#define COWL_DATA_PROP_PRIVATE_H

#include "cowl_data_prop.h"
#include "cowl_data_prop_exp_private.h"

COWL_BEGIN_DECLS

struct CowlDataProp {
    CowlDataPropExp super;
    CowlIRI *iri;
};

COWL_END_DECLS

#endif // COWL_DATA_PROP_PRIVATE_H
