/// @author Ivano Bilenchi

#ifndef COWL_NARY_BOOL_H
#define COWL_NARY_BOOL_H

#include "cowl_iterator.h"
#include "cowl_std.h"
#include "uhash.h"

COWL_BEGIN_DECLS

typedef struct UHash(CowlClsExpSet) const CowlClsExpSet;

typedef struct CowlNAryBool const CowlNAryBool;

typedef enum CowlNAryBoolType {
    CNBT_INTERSECTION,
    CNBT_UNION
} CowlNAryBoolType;

CowlNAryBool* cowl_nary_bool_get(CowlNAryBoolType type, CowlClsExpSet *operands);
CowlNAryBool* cowl_nary_bool_retain(CowlNAryBool *exp);
void cowl_nary_bool_release(CowlNAryBool *exp);

CowlNAryBoolType cowl_nary_bool_get_type(CowlNAryBool *exp);
CowlClsExpSet* cowl_nary_bool_get_operands(CowlNAryBool *exp);

bool cowl_nary_bool_equals(CowlNAryBool *lhs, CowlNAryBool *rhs);
uint32_t cowl_nary_bool_hash(CowlNAryBool *exp);

bool cowl_nary_bool_iterate_signature(CowlNAryBool *exp, void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_NARY_BOOL_H
