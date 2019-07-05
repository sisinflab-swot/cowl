/// @author Ivano Bilenchi

#include "cowl_annot_value.h"
#include "cowl_anon_ind.h"
#include "cowl_iri.h"
#include "cowl_literal.h"

CowlAnnotValue cowl_annot_value_retain(CowlAnnotValue value) {

#define GEN_CASE_RETAIN(CET, PREFIX, FIELD) \
    case CET: PREFIX##_retain(value.FIELD); break

    switch (value.type) {

        GEN_CASE_RETAIN(COWL_AVT_IRI, cowl_iri, iri);
        GEN_CASE_RETAIN(COWL_AVT_ANON_IND, cowl_anon_ind, anon_ind);
        GEN_CASE_RETAIN(COWL_AVT_LITERAL, cowl_literal, literal);

        default:
            break;
    }

    return value;
}

void cowl_annot_value_release(CowlAnnotValue value) {

#define GEN_CASE_RELEASE(CET, PREFIX, FIELD) \
    case CET: PREFIX##_release(value.FIELD); break

    switch (value.type) {

        GEN_CASE_RELEASE(COWL_AVT_IRI, cowl_iri, iri);
        GEN_CASE_RELEASE(COWL_AVT_ANON_IND, cowl_anon_ind, anon_ind);
        GEN_CASE_RELEASE(COWL_AVT_LITERAL, cowl_literal, literal);

        default:
            break;
    }
}

CowlString* cowl_annot_value_to_string(CowlAnnotValue value) {

#define GEN_CASE_TO_STRING(CET, PREFIX, FIELD) \
    case CET: return PREFIX##_to_string(value.FIELD)

    switch (value.type) {

        GEN_CASE_TO_STRING(COWL_AVT_IRI, cowl_iri, iri);
        GEN_CASE_TO_STRING(COWL_AVT_ANON_IND, cowl_anon_ind, anon_ind);
        GEN_CASE_TO_STRING(COWL_AVT_LITERAL, cowl_literal, literal);

        default:
            return NULL;
    }
}

bool cowl_annot_value_equals(CowlAnnotValue lhs, CowlAnnotValue rhs) {
    if (rhs.type != lhs.type) return false;

#define GEN_CASE_EQUALS(CET, PREFIX, FIELD) \
    case CET: return PREFIX##_equals(lhs.FIELD, rhs.FIELD)

    switch (lhs.type) {

        GEN_CASE_EQUALS(COWL_AVT_IRI, cowl_iri, iri);
        GEN_CASE_EQUALS(COWL_AVT_ANON_IND, cowl_anon_ind, anon_ind);
        GEN_CASE_EQUALS(COWL_AVT_LITERAL, cowl_literal, literal);

        default:
            return false;
    }
}

cowl_uint_t cowl_annot_value_hash(CowlAnnotValue value) {

#define GEN_CASE_HASH(CET, PREFIX, FIELD) \
    case CET: return PREFIX##_hash(value.FIELD)

    switch (value.type) {

        GEN_CASE_HASH(COWL_AVT_IRI, cowl_iri, iri);
        GEN_CASE_HASH(COWL_AVT_ANON_IND, cowl_anon_ind, anon_ind);
        GEN_CASE_HASH(COWL_AVT_LITERAL, cowl_literal, literal);

        default:
            return 0;
    }
}
