/// @author Ivano Bilenchi

#ifndef COWL_ANNOT_VALUE_H
#define COWL_ANNOT_VALUE_H

#include "cowl_annot_value_type.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlAnonIndividual);
cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlLiteral);
cowl_struct_decl(CowlString);

typedef cowl_struct(CowlAnnotValue) {
    CowlAnnotValueType type;

    union {
        CowlIRI *iri;
        CowlAnonIndividual *anon_ind;
        CowlLiteral *literal;
    };
} CowlAnnotValue;

#define cowl_annot_value_wrap_iri(IRI) \
    ((CowlAnnotValue const){ .type = CAVT_IRI, .iri = (IRI)})

#define cowl_annot_value_wrap_anon_ind(IND) \
    ((CowlAnnotValue const){ .type = CAVT_ANON_IND, .anon_ind = (CowlAnonIndividual *)(IND) })

#define cowl_annot_value_wrap_literal(LITERAL) \
    ((CowlAnnotValue const){ .type = CAVT_LITERAL, .literal = (LITERAL) })

#define cowl_annot_value_init_iri(IRI) \
    cowl_annot_value_wrap_iri(cowl_iri_retain(IRI))

#define cowl_annot_value_init_anon_ind(IND) \
    cowl_annot_value_wrap_anon_ind(cowl_anon_individual_retain(IND))

#define cowl_annot_value_init_literal(LITERAL) \
    cowl_annot_value_wrap_literal(cowl_literal_retain(LITERAL))

CowlAnnotValue cowl_annot_value_retain(CowlAnnotValue value);
void cowl_annot_value_release(CowlAnnotValue value);

CowlString* cowl_annot_value_to_string(CowlAnnotValue value);

bool cowl_annot_value_equals(CowlAnnotValue lhs, CowlAnnotValue rhs);
cowl_uint_t cowl_annot_value_hash(CowlAnnotValue value);

COWL_END_DECLS

#endif // COWL_ANNOT_VALUE_H
