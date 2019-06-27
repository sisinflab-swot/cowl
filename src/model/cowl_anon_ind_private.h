/// @author Ivano Bilenchi

#ifndef COWL_ANON_IND_PRIVATE_H
#define COWL_ANON_IND_PRIVATE_H

#include "cowl_anon_ind.h"
#include "cowl_individual_private.h"

COWL_BEGIN_DECLS

cowl_struct(CowlAnonInd) {
    CowlIndividual super;
    CowlNodeID id;
};

COWL_END_DECLS

#endif //COWL_ANON_IND_PRIVATE_H
