/// @author Ivano Bilenchi

#ifndef COWL_DISJ_UNION_AXIOM_H
#define COWL_DISJ_UNION_AXIOM_H

#include "cowl_std.h"
#include "cowl_iterator.h"

COWL_BEGIN_DECLS

cowl_hash_decl(CowlClsExpSet);
cowl_vector_decl(CowlAnnotationPtr, CowlAnnotationVec);

cowl_struct_decl(CowlDisjUnionAxiom);

CowlDisjUnionAxiom* cowl_disj_union_axiom_get(CowlClass *cls, CowlClsExpSet *disjoints,
                                              CowlAnnotationVec *annot);
CowlDisjUnionAxiom* cowl_disj_union_axiom_retain(CowlDisjUnionAxiom *axiom);
void cowl_disj_union_axiom_release(CowlDisjUnionAxiom *axiom);

CowlClass* cowl_disj_union_axiom_get_class(CowlDisjUnionAxiom *axiom);
CowlClsExpSet* cowl_disj_union_axiom_get_disjoints(CowlDisjUnionAxiom *axiom);
CowlAnnotationVec* cowl_disj_union_axiom_get_annot(CowlDisjUnionAxiom *axiom);

bool cowl_disj_union_axiom_equals(CowlDisjUnionAxiom *lhs, CowlDisjUnionAxiom *rhs);
cowl_uint_t cowl_disj_union_axiom_hash(CowlDisjUnionAxiom *axiom);

bool cowl_disj_union_axiom_iterate_signature(CowlDisjUnionAxiom *axiom,
                                             void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_DISJ_UNION_AXIOM_H
