/// @author Ivano Bilenchi

#ifndef COWL_ANON_INDIVIDUAL_H
#define COWL_ANON_INDIVIDUAL_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlString CowlString;

typedef struct CowlAnonIndividual CowlAnonIndividual;

CowlAnonIndividual const* cowl_anon_individual_get(CowlString const *id);
CowlAnonIndividual const* cowl_anon_individual_retain(CowlAnonIndividual const *ind);
void cowl_anon_individual_release(CowlAnonIndividual const *ind);

CowlString const* cowl_anon_individual_get_id(CowlAnonIndividual const *ind);

bool cowl_anon_individual_equals(CowlAnonIndividual const *lhs, CowlAnonIndividual const *rhs);
uint32_t cowl_anon_individual_hash(CowlAnonIndividual const *ind);

COWL_END_DECLS

#endif // COWL_ANON_INDIVIDUAL_H
