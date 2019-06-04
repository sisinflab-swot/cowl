/// @author Ivano Bilenchi

#ifndef COWL_NARY_INDIVIDUAL_AXIOM_H
#define COWL_NARY_INDIVIDUAL_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_nary_axiom_type.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_hash_decl(CowlIndividualSet);
cowl_struct_decl(CowlIndividual);

cowl_struct_decl(CowlNAryIndividualAxiom);

CowlNAryIndividualAxiom* cowl_nary_individual_axiom_get(CowlNAryAxiomType type,
                                                        CowlIndividualSet *operands);
CowlNAryIndividualAxiom* cowl_nary_individual_axiom_retain(CowlNAryIndividualAxiom *axiom);
void cowl_nary_individual_axiom_release(CowlNAryIndividualAxiom *axiom);

CowlNAryAxiomType cowl_nary_individual_axiom_get_type(CowlNAryIndividualAxiom *axiom);
CowlIndividualSet* cowl_nary_individual_axiom_get_operands(CowlNAryIndividualAxiom *axiom);

bool cowl_nary_individual_axiom_equals(CowlNAryIndividualAxiom *lhs, CowlNAryIndividualAxiom *rhs);
cowl_uint_t cowl_nary_individual_axiom_hash(CowlNAryIndividualAxiom *axiom);

bool cowl_nary_individual_axiom_iterate_signature(CowlNAryIndividualAxiom *axiom, void *ctx,
                                                  CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_NARY_INDIVIDUAL_AXIOM_H
