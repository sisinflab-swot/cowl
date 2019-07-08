/// @author Ivano Bilenchi

#ifndef COWL_FACET_PRIVATE_H
#define COWL_FACET_PRIVATE_H

#include "cowl_facet.h"

COWL_BEGIN_DECLS

void cowl_facet_init(void);
void cowl_facet_deinit(void);

#define cowl_facet_foreach(var_name) \
    for (CowlFacet var_name = COWL_FACET_FIRST; (var_name) < COWL_FACET_COUNT; ++(var_name))

COWL_END_DECLS

#endif // COWL_FACET_PRIVATE_H
