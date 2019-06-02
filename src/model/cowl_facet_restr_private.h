/// @author Ivano Bilenchi

#ifndef COWL_FACET_RESTR_PRIVATE_H
#define COWL_FACET_RESTR_PRIVATE_H

#include "cowl_facet_restr.h"
#include "cowl_object.h"

COWL_BEGIN_DECLS

cowl_struct(CowlFacetRestr) {
    CowlObject super;
    CowlFacet facet;
    CowlLiteral *value;
};

COWL_END_DECLS

#endif // COWL_FACET_RESTR_PRIVATE_H
