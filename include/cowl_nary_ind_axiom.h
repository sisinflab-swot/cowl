/// @author Ivano Bilenchi

#ifndef COWL_NARY_IND_AXIOM_H
#define COWL_NARY_IND_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_nary_axiom_type.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_hash_decl(CowlIndividualSet);
cowl_struct_decl(CowlIndividual);
cowl_vector_decl(CowlAnnotationPtr, CowlAnnotationVec);

cowl_struct_decl(CowlNAryIndAxiom);

CowlNAryIndAxiom *cowl_nary_ind_axiom_get(CowlNAryAxiomType type, CowlIndividualSet *operands,
                                          CowlAnnotationVec *annot);
CowlNAryIndAxiom *cowl_nary_ind_axiom_retain(CowlNAryIndAxiom *axiom);
void cowl_nary_ind_axiom_release(CowlNAryIndAxiom *axiom);

CowlNAryAxiomType cowl_nary_ind_axiom_get_type(CowlNAryIndAxiom *axiom);
CowlIndividualSet *cowl_nary_ind_axiom_get_operands(CowlNAryIndAxiom *axiom);
CowlAnnotationVec *cowl_nary_ind_axiom_get_annot(CowlNAryIndAxiom *axiom);

bool cowl_nary_ind_axiom_equals(CowlNAryIndAxiom *lhs, CowlNAryIndAxiom *rhs);
cowl_uint_t cowl_nary_ind_axiom_hash(CowlNAryIndAxiom *axiom);

bool cowl_nary_ind_axiom_iterate_signature(CowlNAryIndAxiom *axiom, CowlEntityIterator *iter);

COWL_END_DECLS

#endif // COWL_NARY_IND_AXIOM_H
