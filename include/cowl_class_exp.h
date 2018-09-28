/// @author Ivano Bilenchi

#ifndef COWL_CLASS_EXPRESSION_H
#define COWL_CLASS_EXPRESSION_H

#include "cowl_class_exp_type.h"
#include "cowl_std.h"
#include "khash_utils.h"

COWL_BEGIN_DECLS

typedef struct CowlEntity CowlEntity;
typedef struct CowlObjPropExp CowlObjPropExp;

typedef struct CowlClassExp CowlClassExp;
KHASH_SET_UTILS_DECL(CowlClassExpSet, CowlClassExp const*);

CowlClassExpType cowl_class_exp_type(CowlClassExp const *exp);

CowlEntity const* cowl_class_exp_as_class(CowlClassExp const *exp);

CowlClassExp const* cowl_class_exp_operand(CowlClassExp const *exp);
khash_t(CowlClassExpSet) const* cowl_class_exp_operands(CowlClassExp const *exp);

CowlObjPropExp const* cowl_class_exp_property(CowlClassExp const *exp);
CowlClassExp const* cowl_class_exp_filler(CowlClassExp const *exp);
uint32_t cowl_class_exp_cardinality(CowlClassExp const *exp);

bool cowl_class_exp_equals(CowlClassExp const *a, CowlClassExp const *b);
uint32_t cowl_class_exp_hash(CowlClassExp const *exp);

COWL_END_DECLS

#endif // COWL_CLASS_EXPRESSION_H
