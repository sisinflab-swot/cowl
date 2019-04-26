/// @author Ivano Bilenchi

#ifndef COWL_OBJ_PROP_CHAR_AXIOM_H
#define COWL_OBJ_PROP_CHAR_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlObjPropExp const CowlObjPropExp;

typedef struct CowlObjPropCharAxiom const CowlObjPropCharAxiom;

typedef enum CowlObjPropCharAxiomType {
    COPCAT_FUNCTIONAL,
    COPCAT_INVERSE_FUNCTIONAL,
    COPCAT_SYMMETRIC,
    COPCAT_ASYMMETRIC,
    COPCAT_TRANSITIVE,
    COPCAT_REFLEXIVE,
    COPCAT_IRREFLEXIVE
} CowlObjPropCharAxiomType;

CowlObjPropCharAxiom* cowl_obj_prop_char_axiom_get(CowlObjPropCharAxiomType type,
                                                   CowlObjPropExp *prop);
CowlObjPropCharAxiom* cowl_obj_prop_char_axiom_retain(CowlObjPropCharAxiom *axiom);
void cowl_obj_prop_char_axiom_release(CowlObjPropCharAxiom *axiom);

CowlObjPropCharAxiomType cowl_obj_prop_char_axiom_get_type(CowlObjPropCharAxiom *axiom);
CowlObjPropExp* cowl_obj_prop_char_axiom_get_prop(CowlObjPropCharAxiom *axiom);

bool cowl_obj_prop_char_axiom_equals(CowlObjPropCharAxiom *lhs, CowlObjPropCharAxiom *rhs);
cowl_uint_t cowl_obj_prop_char_axiom_hash(CowlObjPropCharAxiom *axiom);

bool cowl_obj_prop_char_axiom_iterate_signature(CowlObjPropCharAxiom *axiom,
                                                void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_OBJ_PROP_CHAR_AXIOM_H
