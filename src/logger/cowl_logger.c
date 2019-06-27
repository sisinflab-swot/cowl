/// @author Ivano Bilenchi

#include "cowl_logger.h"
#include "cowl_private.h"

#include <stdio.h>
#include <stdarg.h>

static void cowl_logger_log_anon_ind(CowlLogger *logger, CowlAnonInd *ind);
static void cowl_logger_log_ontology_header(CowlLogger *logger, CowlOntology *onto);

static void cowl_logger_log_cls_exp_set(CowlLogger *logger, CowlClsExpSet *set);
static void cowl_logger_log_obj_prop_exp_set(CowlLogger *logger, CowlObjPropExpSet *set);
static void cowl_logger_log_obj_prop_exp_vec(CowlLogger *logger, CowlObjPropExpVec *vec);
static void cowl_logger_log_data_prop_exp_set(CowlLogger *logger, CowlDataPropExpSet *set);
static void cowl_logger_log_data_range_set(CowlLogger *logger, CowlDataRangeSet *set);
static void cowl_logger_log_facet_restr_set(CowlLogger *logger, CowlFacetRestrSet *set);
static void cowl_logger_log_individual_set(CowlLogger *logger, CowlIndividualSet *set);
static void cowl_logger_log_literal_set(CowlLogger *logger, CowlLiteralSet *set);

static void cowl_logger_log_obj_quant(CowlLogger *logger, CowlObjQuant *restr);
static void cowl_logger_log_obj_card(CowlLogger *logger, CowlObjCard *card);
static void cowl_logger_log_obj_has_value(CowlLogger *logger, CowlObjHasValue *exp);
static void cowl_logger_log_obj_has_self(CowlLogger *logger, CowlObjHasSelf *exp);
static void cowl_logger_log_nary_bool(CowlLogger *logger, CowlNAryBool *nary);
static void cowl_logger_log_obj_compl(CowlLogger *logger, CowlObjCompl *exp);
static void cowl_logger_log_obj_one_of(CowlLogger *logger, CowlObjOneOf *exp);
static void cowl_logger_log_data_quant(CowlLogger *logger, CowlDataQuant *exp);
static void cowl_logger_log_data_card(CowlLogger *logger, CowlDataCard *exp);
static void cowl_logger_log_data_has_value(CowlLogger *logger, CowlDataHasValue *exp);
static void cowl_logger_log_datatype_restr(CowlLogger *logger, CowlDatatypeRestr *restr);
static void cowl_logger_log_nary_data(CowlLogger *logger, CowlNAryData *nary);
static void cowl_logger_log_data_compl(CowlLogger *logger, CowlDataCompl *range);
static void cowl_logger_log_data_one_of(CowlLogger *logger, CowlDataOneOf *range);

static void cowl_logger_log_decl_axiom(CowlLogger *logger, CowlDeclAxiom *axiom);
static void cowl_logger_log_datatype_def_axiom(CowlLogger *logger, CowlDatatypeDefAxiom *axiom);
static void cowl_logger_log_sub_cls_axiom(CowlLogger *logger, CowlSubClsAxiom *axiom);
static void cowl_logger_log_nary_cls_axiom(CowlLogger *logger, CowlNAryClsAxiom *axiom);
static void cowl_logger_log_disj_union_axiom(CowlLogger *logger, CowlDisjUnionAxiom *axiom);
static void cowl_logger_log_cls_assert(CowlLogger *logger, CowlClsAssertAxiom *axiom);
static void cowl_logger_log_nary_ind_axiom(CowlLogger *logger, CowlNAryIndAxiom *axiom);
static void cowl_logger_log_obj_prop_assert(CowlLogger *logger, CowlObjPropAssertAxiom *axiom);
static void cowl_logger_log_data_prop_assert(CowlLogger *logger, CowlDataPropAssertAxiom *axiom);
static void cowl_logger_log_sub_obj_prop_axiom(CowlLogger *logger, CowlSubObjPropAxiom *axiom);
static void cowl_logger_log_sub_obj_prop_chain_axiom(CowlLogger *logger,
                                                     CowlSubObjPropChainAxiom *axiom);
static void cowl_logger_log_inv_obj_prop_axiom(CowlLogger *logger, CowlInvObjPropAxiom *axiom);
static void cowl_logger_log_nary_obj_prop_axiom(CowlLogger *logger, CowlNAryObjPropAxiom *axiom);
static void cowl_logger_log_obj_prop_char(CowlLogger *logger, CowlObjPropCharAxiom *axiom);
static void cowl_logger_log_obj_prop_domain(CowlLogger *logger, CowlObjPropDomainAxiom *axiom);
static void cowl_logger_log_obj_prop_range(CowlLogger *logger, CowlObjPropRangeAxiom *axiom);
static void cowl_logger_log_sub_data_prop_axiom(CowlLogger *logger, CowlSubDataPropAxiom *axiom);
static void cowl_logger_log_nary_data_prop_axiom(CowlLogger *logger, CowlNAryDataPropAxiom *axiom);
static void cowl_logger_log_func_data_prop_axiom(CowlLogger *logger, CowlFuncDataPropAxiom *axiom);
static void cowl_logger_log_data_prop_domain(CowlLogger *logger, CowlDataPropDomainAxiom *axiom);
static void cowl_logger_log_data_prop_range(CowlLogger *logger, CowlDataPropRangeAxiom *axiom);
static void cowl_logger_log_has_key_axiom(CowlLogger *logger, CowlHasKeyAxiom *axiom);
static void cowl_logger_log_annot_assert(CowlLogger *logger, CowlAnnotAssertAxiom *axiom);
static void cowl_logger_log_sub_annot_prop_axiom(CowlLogger *logger, CowlSubAnnotPropAxiom *axiom);
static void cowl_logger_log_annot_prop_domain_axiom(CowlLogger *logger,
                                                    CowlAnnotPropDomainAxiom *axiom);
static void cowl_logger_log_annot_prop_range_axiom(CowlLogger *logger,
                                                   CowlAnnotPropRangeAxiom *axiom);

typedef enum CowlLoggerType {
    COWL_LT_NULL,
    COWL_LT_CONSOLE,
    COWL_LT_FILE
} CowlLoggerType;

cowl_struct(CowlLogger) {
    CowlLoggerType const type;

    char const *path;
    FILE *file;
};

static CowlLogger* cowl_logger_alloc(CowlLoggerType type, void *context) {
    CowlLogger logger_init = { .type = type };
    cowl_struct(CowlLogger) *logger = malloc(sizeof(*logger));
    memcpy(logger, &logger_init, sizeof(*logger));

    if (type == COWL_LT_FILE) {
        logger->path = context;
        logger->file = NULL;
    }

    cowl_logger_open(logger);
    return logger;
}

CowlLogger* cowl_logger_alloc_console(void) {
    return cowl_logger_alloc(COWL_LT_CONSOLE, NULL);
}

CowlLogger* cowl_logger_alloc_file(char const *path) {
    return cowl_logger_alloc(COWL_LT_FILE, strdup(path));
}

CowlLogger* cowl_logger_alloc_null(void) {
    return cowl_logger_alloc(COWL_LT_NULL, NULL);
}

void cowl_logger_free(CowlLogger *logger) {
    if (!logger) return;

    if (logger->type == COWL_LT_FILE) {
        cowl_logger_close(logger);
        free((void *)logger->path);
    }

    free((void *)logger);
}

void cowl_logger_open(CowlLogger *logger) {
    if (logger->type != COWL_LT_FILE) return;

    if (!logger->file) {
        ((cowl_struct(CowlLogger) *)logger)->file = fopen(logger->path, "a");
    }
}

void cowl_logger_close(CowlLogger *logger) {
    if (logger->type != COWL_LT_FILE) return;

    if (logger->file) {
        fclose(logger->file);
        ((cowl_struct(CowlLogger)*)logger)->file = NULL;
    }
}

void cowl_logger_clear(CowlLogger *logger) {
    cowl_logger_close(logger);

    if (logger->type == COWL_LT_FILE) {
        remove(logger->path);
    }
}

void cowl_logger_logf(CowlLogger *logger, char const *format, ...) {
    va_list args;
    va_start(args, format);

    switch(logger->type) {
        case COWL_LT_CONSOLE:
            vprintf(format, args);
            break;

        case COWL_LT_FILE:
            vfprintf(logger->file, format, args);
            break;

        default:
            break;
    }

    va_end(args);
}

void cowl_logger_log_string(CowlLogger *logger, CowlString *string) {
    cowl_logger_logf(logger, "%s", string->cstring);
}

static bool axiom_logger(void *ctx, CowlAxiom *axiom) {
    CowlLogger *logger = ctx;
    cowl_logger_log_axiom(logger, axiom);
    cowl_logger_logf(logger, "\n");
    return true;
}

void cowl_logger_log_axioms_in_ontology(CowlLogger *logger, CowlOntology *onto) {
    cowl_ontology_iterate_axioms(onto, (void *)logger, axiom_logger);
}

static bool entity_logger(void *ctx, CowlEntity entity) {
    cowl_struct(CowlLogger) *logger = ctx;
    cowl_logger_log_entity(logger, entity);
    cowl_logger_logf(logger, "\n");
    return true;
}

void cowl_logger_log_entities_in_ontology(CowlLogger *logger, CowlOntology *onto) {
    cowl_ontology_iterate_signature(onto, (void *)logger, entity_logger);
}

void cowl_logger_log_ontology_id(CowlLogger *logger, CowlOntologyId *id) {
    cowl_logger_log_iri(logger, id->onto_iri);

    if (id->version_iri) {
        cowl_logger_logf(logger, " ");
        cowl_logger_log_iri(logger, id->version_iri);
    }
}

void cowl_logger_log_ontology(CowlLogger *logger, CowlOntology *onto) {
    cowl_logger_log_ontology_header(logger, onto);
    cowl_logger_logf(logger, "\n");
    cowl_logger_log_entities_in_ontology(logger, onto);
    cowl_logger_log_axioms_in_ontology(logger, onto);
}

void cowl_logger_log_annotation(CowlLogger *logger, CowlAnnotation *annotation) {
    cowl_logger_logf(logger, "Annotation(");
    cowl_logger_log_annot_prop(logger, annotation->prop);
    cowl_logger_logf(logger, " ");
    cowl_logger_log_annot_value(logger, annotation->value);
    cowl_logger_logf(logger, ")");
}

void cowl_logger_log_iri(CowlLogger *logger, CowlIRI *iri) {
    cowl_logger_logf(logger, "<%s%s>", iri->ns->cstring, iri->rem->cstring);
}

void cowl_logger_log_entity(CowlLogger *logger, CowlEntity entity) {
    char const *type = NULL;

    switch (entity.type) {
        case CET_CLASS: type = "Class"; break;
        case CET_OBJ_PROP: type = "ObjectProperty"; break;
        case CET_DATA_PROP: type = "DataProperty"; break;
        case CET_ANNOT_PROP: type = "AnnotationProperty"; break;
        case CET_NAMED_IND: type = "Namedind"; break;
        case CET_DATATYPE: type = "Datatype"; break;
    }

    cowl_logger_logf(logger, "%s(", type);
    cowl_logger_log_iri(logger, cowl_entity_get_iri(entity));
    cowl_logger_logf(logger, ")");
}

void cowl_logger_log_annot_value(CowlLogger *logger, CowlAnnotValue value) {
    switch (value.type) {
        case CAVT_ANON_IND: cowl_logger_log_anon_ind(logger, value.anon_ind); break;
        case CAVT_IRI: cowl_logger_log_iri(logger, value.iri); break;
        case CAVT_LITERAL: cowl_logger_log_literal(logger, value.literal); break;
    }
}

void cowl_logger_log_annot_prop(CowlLogger *logger, CowlAnnotProp *prop) {
    cowl_logger_log_entity(logger, cowl_entity_wrap_annot_prop(prop));
}

void cowl_logger_log_cls_exp(CowlLogger *logger, CowlClsExp *exp) {
    switch (exp->type) {

        case CCET_CLASS:
            cowl_logger_log_entity(logger, cowl_entity_wrap_class((CowlClass *)exp));
            break;

        case CCET_OBJ_SOME:
        case CCET_OBJ_ALL:
            cowl_logger_log_obj_quant(logger, (CowlObjQuant *)exp);
            break;

        case CCET_OBJ_MIN_CARD:
        case CCET_OBJ_MAX_CARD:
        case CCET_OBJ_EXACT_CARD:
            cowl_logger_log_obj_card(logger, (CowlObjCard *)exp);
            break;

        case CCET_OBJ_HAS_VALUE:
            cowl_logger_log_obj_has_value(logger, (CowlObjHasValue *)exp);
            break;

        case CCET_OBJ_HAS_SELF:
            cowl_logger_log_obj_has_self(logger, (CowlObjHasSelf *)exp);
            break;

        case CCET_OBJ_INTERSECTION:
        case CCET_OBJ_UNION:
            cowl_logger_log_nary_bool(logger, (CowlNAryBool *)exp);
            break;

        case CCET_OBJ_COMPLEMENT:
            cowl_logger_log_obj_compl(logger, (CowlObjCompl *)exp);
            break;

        case CCET_OBJ_ONE_OF:
            cowl_logger_log_obj_one_of(logger, (CowlObjOneOf *)exp);
            break;

        case CCET_DATA_SOME:
        case CCET_DATA_ALL:
            cowl_logger_log_data_quant(logger, (CowlDataQuant *)exp);
            break;

        case CCET_DATA_MIN_CARD:
        case CCET_DATA_MAX_CARD:
        case CCET_DATA_EXACT_CARD:
            cowl_logger_log_data_card(logger, (CowlDataCard *)exp);
            break;

        case CCET_DATA_HAS_VALUE:
            cowl_logger_log_data_has_value(logger, (CowlDataHasValue *)exp);
            break;

        default:
            break;
    }
}

void cowl_logger_log_data_prop_exp(CowlLogger *logger, CowlDataPropExp *exp) {
    cowl_logger_log_entity(logger, cowl_entity_wrap_data_prop((CowlDataProp *)exp));
}

void cowl_logger_log_data_range(CowlLogger *logger, CowlDataRange *range) {
    switch (range->type) {

        case CDRT_DATATYPE:
            cowl_logger_log_entity(logger, cowl_entity_wrap_datatype((CowlDatatype *)range));
            break;

        case CDRT_DATATYPE_RESTRICTION:
            cowl_logger_log_datatype_restr(logger, (CowlDatatypeRestr *)range);
            break;

        case CDRT_DATA_INTERSECTION:
        case CDRT_DATA_UNION:
            cowl_logger_log_nary_data(logger, (CowlNAryData *)range);
            break;

        case CDRT_DATA_COMPLEMENT:
            cowl_logger_log_data_compl(logger, (CowlDataCompl *)range);
            break;

        case CDRT_DATA_ONE_OF:
            cowl_logger_log_data_one_of(logger, (CowlDataOneOf *)range);
            break;

        default:
            break;
    }
}

void cowl_logger_log_individual(CowlLogger *logger, CowlIndividual *ind) {
    if (ind->is_named) {
        CowlNamedInd *named_ind = (CowlNamedInd *)ind;
        cowl_logger_log_entity(logger, cowl_entity_wrap_named_ind(named_ind));
    } else {
        cowl_logger_log_anon_ind(logger, (CowlAnonInd *)ind);
    }
}

void cowl_logger_log_literal(CowlLogger *logger, CowlLiteral *literal) {
    CowlString *string = cowl_literal_to_string(literal);
    cowl_logger_log_string(logger, string);
    cowl_string_release(string);
}

void cowl_logger_log_obj_prop_exp(CowlLogger *logger, CowlObjPropExp *exp) {
    if (exp->is_inverse) cowl_logger_logf(logger, "ObjectInverseOf(");
    cowl_logger_log_entity(logger, cowl_entity_wrap_obj_prop(cowl_obj_prop_exp_get_prop(exp)));
    if (exp->is_inverse) cowl_logger_logf(logger, ")");
}

void cowl_logger_log_axiom(CowlLogger *logger, CowlAxiom *axiom) {
    CowlAxiomType type = cowl_axiom_get_type(axiom);

    switch (type) {

        case CAT_DECLARATION:
            cowl_logger_log_decl_axiom(logger, (CowlDeclAxiom *)axiom);
            break;

        case CAT_DATATYPE_DEFINITION:
            cowl_logger_log_datatype_def_axiom(logger, (CowlDatatypeDefAxiom *)axiom);
            break;

        case CAT_SUB_CLASS:
            cowl_logger_log_sub_cls_axiom(logger, (CowlSubClsAxiom *)axiom);
            break;

        case CAT_EQUIVALENT_CLASSES:
        case CAT_DISJOINT_CLASSES:
            cowl_logger_log_nary_cls_axiom(logger, (CowlNAryClsAxiom *)axiom);
            break;

        case CAT_DISJOINT_UNION:
            cowl_logger_log_disj_union_axiom(logger, (CowlDisjUnionAxiom *)axiom);
            break;

        case CAT_CLASS_ASSERTION:
            cowl_logger_log_cls_assert(logger, (CowlClsAssertAxiom *)axiom);
            break;

        case CAT_SAME_INDIVIDUAL:
        case CAT_DIFFERENT_INDIVIDUALS:
            cowl_logger_log_nary_ind_axiom(logger, (CowlNAryIndAxiom *)axiom);
            break;

        case CAT_OBJ_PROP_ASSERTION:
        case CAT_NEGATIVE_OBJ_PROP_ASSERTION:
            cowl_logger_log_obj_prop_assert(logger, (CowlObjPropAssertAxiom *)axiom);
            break;

        case CAT_DATA_PROP_ASSERTION:
        case CAT_NEGATIVE_DATA_PROP_ASSERTION:
            cowl_logger_log_data_prop_assert(logger, (CowlDataPropAssertAxiom *)axiom);
            break;

        case CAT_SUB_OBJ_PROP:
            cowl_logger_log_sub_obj_prop_axiom(logger, (CowlSubObjPropAxiom *)axiom);
            break;

        case CAT_SUB_OBJ_PROP_CHAIN:
            cowl_logger_log_sub_obj_prop_chain_axiom(logger, (CowlSubObjPropChainAxiom *)axiom);
            break;

        case CAT_INVERSE_OBJ_PROP:
            cowl_logger_log_inv_obj_prop_axiom(logger, (CowlInvObjPropAxiom *)axiom);
            break;

        case CAT_EQUIVALENT_OBJ_PROP:
        case CAT_DISJOINT_OBJ_PROP:
            cowl_logger_log_nary_obj_prop_axiom(logger, (CowlNAryObjPropAxiom *)axiom);
            break;

        case CAT_FUNCTIONAL_OBJ_PROP:
        case CAT_INVERSE_FUNCTIONAL_OBJ_PROP:
        case CAT_SYMMETRIC_OBJ_PROP:
        case CAT_ASYMMETRIC_OBJ_PROP:
        case CAT_REFLEXIVE_OBJ_PROP:
        case CAT_IRREFLEXIVE_OBJ_PROP:
        case CAT_TRANSITIVE_OBJ_PROP:
            cowl_logger_log_obj_prop_char(logger, (CowlObjPropCharAxiom *)axiom);
            break;

        case CAT_OBJ_PROP_DOMAIN:
            cowl_logger_log_obj_prop_domain(logger, (CowlObjPropDomainAxiom *)axiom);
            break;

        case CAT_OBJ_PROP_RANGE:
            cowl_logger_log_obj_prop_range(logger, (CowlObjPropRangeAxiom *)axiom);
            break;

        case CAT_SUB_DATA_PROP:
            cowl_logger_log_sub_data_prop_axiom(logger, (CowlSubDataPropAxiom *)axiom);
            break;

        case CAT_EQUIVALENT_DATA_PROP:
        case CAT_DISJOINT_DATA_PROP:
            cowl_logger_log_nary_data_prop_axiom(logger, (CowlNAryDataPropAxiom *)axiom);
            break;

        case CAT_FUNCTIONAL_DATA_PROP:
            cowl_logger_log_func_data_prop_axiom(logger, (CowlFuncDataPropAxiom *)axiom);
            break;

        case CAT_DATA_PROP_DOMAIN:
            cowl_logger_log_data_prop_domain(logger, (CowlDataPropDomainAxiom *)axiom);
            break;

        case CAT_DATA_PROP_RANGE:
            cowl_logger_log_data_prop_range(logger, (CowlDataPropRangeAxiom *)axiom);
            break;

        case CAT_HAS_KEY:
            cowl_logger_log_has_key_axiom(logger, (CowlHasKeyAxiom *)axiom);
            break;

        case CAT_ANNOT_ASSERTION:
            cowl_logger_log_annot_assert(logger, (CowlAnnotAssertAxiom *)axiom);
            break;

        case CAT_SUB_ANNOT_PROP:
            cowl_logger_log_sub_annot_prop_axiom(logger, (CowlSubAnnotPropAxiom *)axiom);
            break;

        case CAT_ANNOT_PROP_DOMAIN:
            cowl_logger_log_annot_prop_domain_axiom(logger, (CowlAnnotPropDomainAxiom *)axiom);
            break;

        case CAT_ANNOT_PROP_RANGE:
            cowl_logger_log_annot_prop_range_axiom(logger, (CowlAnnotPropRangeAxiom *)axiom);
            break;

        default:
            break;
    }
}

void cowl_logger_log_error(CowlLogger *logger, CowlError error) {
    CowlString *string = cowl_error_to_string(error);
    cowl_logger_log_string(logger, string);
    cowl_string_release(string);
}

char const* cowl_logger_get_path(CowlLogger *logger) {
    if (logger->type != COWL_LT_FILE) return NULL;
    return logger->path;
}

static void cowl_logger_log_ontology_header(CowlLogger *logger, CowlOntology *onto) {
    cowl_logger_logf(logger, "Ontology(");
    cowl_logger_log_ontology_id(logger, onto->id);

    vector_foreach(CowlAnnotationPtr, onto->annotations, annot, {
        cowl_logger_logf(logger, "\n");
        cowl_logger_log_annotation(logger, annot);
    });

    cowl_logger_logf(logger, ")");
}

static void cowl_logger_log_anon_ind(CowlLogger *logger, CowlAnonInd *ind) {
    CowlString *string = cowl_anon_ind_to_string(ind);
    cowl_logger_logf(logger, "AnonymousIndividual(");
    cowl_logger_log_string(logger, string);
    cowl_logger_logf(logger, ")");
    cowl_string_release(string);
}

static void cowl_logger_log_cls_exp_set(CowlLogger *logger, CowlClsExpSet *set) {
    cowl_uint_t current = 0, last = uhash_count(set) - 1;

    uhash_foreach_key(CowlClsExpSet, set, exp, {
        cowl_logger_log_cls_exp(logger, exp);
        if (current++ < last) cowl_logger_logf(logger, " ");
    });
}

static void cowl_logger_log_obj_prop_exp_set(CowlLogger *logger, CowlObjPropExpSet *set) {
    cowl_uint_t current = 0, last = uhash_count(set) - 1;

    uhash_foreach_key(CowlObjPropExpSet, set, exp, {
        cowl_logger_log_obj_prop_exp(logger, exp);
        if (current++ < last) cowl_logger_logf(logger, " ");
    });
}

static void cowl_logger_log_obj_prop_exp_vec(CowlLogger *logger, CowlObjPropExpVec *vec) {
    cowl_uint_t last = vector_count(vec);

    vector_iterate(CowlObjPropExpPtr, vec, prop, idx, {
        cowl_logger_log_obj_prop_exp(logger, prop);
        if (idx < last) cowl_logger_logf(logger, " ");
    });
}

static void cowl_logger_log_data_prop_exp_set(CowlLogger *logger, CowlDataPropExpSet *set) {
    cowl_uint_t current = 0, last = uhash_count(set) - 1;

    uhash_foreach_key(CowlDataPropExpSet, set, exp, {
        cowl_logger_log_data_prop_exp(logger, exp);
        if (current++ < last) cowl_logger_logf(logger, " ");
    });
}

static void cowl_logger_log_data_range_set(CowlLogger *logger, CowlDataRangeSet *set) {
    cowl_uint_t current = 0, last = uhash_count(set) - 1;

    uhash_foreach_key(CowlDataRangeSet, set, range, {
        cowl_logger_log_data_range(logger, range);
        if (current++ < last) cowl_logger_logf(logger, " ");
    });
}

static void cowl_logger_log_facet_restr_set(CowlLogger *logger, CowlFacetRestrSet *set) {
    cowl_uint_t current = 0, last = uhash_count(set) - 1;

    uhash_foreach_key(CowlFacetRestrSet, set, restr, {
        cowl_logger_log_iri(logger, cowl_facet_get_iri(restr->facet));
        cowl_logger_logf(logger, " ");
        cowl_logger_log_literal(logger, restr->value);
        if (current++ < last) cowl_logger_logf(logger, " ");
    });
}

static void cowl_logger_log_individual_set(CowlLogger *logger, CowlIndividualSet *set) {
    cowl_uint_t current = 0, last = uhash_count(set) - 1;

    uhash_foreach_key(CowlIndividualSet, set, ind, {
        cowl_logger_log_individual(logger, ind);
        if (current++ < last) cowl_logger_logf(logger, " ");
    });
}

static void cowl_logger_log_literal_set(CowlLogger *logger, CowlLiteralSet *set) {
    cowl_uint_t current = 0, last = uhash_count(set) - 1;

    uhash_foreach_key(CowlLiteralSet, set, literal, {
        cowl_logger_log_literal(logger, literal);
        if (current++ < last) cowl_logger_logf(logger, " ");
    });
}

static void cowl_logger_log_obj_quant(CowlLogger *logger, CowlObjQuant *restr) {
    char const *str = restr->super.type == CCET_OBJ_SOME ? "Some" : "All";
    cowl_logger_logf(logger, "Object%sValuesFrom(", str);
    cowl_logger_log_obj_prop_exp(logger, restr->prop);
    cowl_logger_logf(logger, " ");
    cowl_logger_log_cls_exp(logger, restr->filler);
    cowl_logger_logf(logger, ")");
}

static void cowl_logger_log_obj_card(CowlLogger *logger, CowlObjCard *card) {
    char const *str;

    switch (card->super.type) {
        case CCET_OBJ_MIN_CARD: str = "Min"; break;
        case CCET_OBJ_MAX_CARD: str = "Max"; break;
        default: str = "Exact"; break;
    }

    cowl_logger_logf(logger, "Object%sCardinality(%lu ", str, card->cardinality);
    cowl_logger_log_obj_prop_exp(logger, card->prop);

    if (card->filler) {
        cowl_logger_logf(logger, " ");
        cowl_logger_log_cls_exp(logger, card->filler);
    }

    cowl_logger_logf(logger, ")");
}

static void cowl_logger_log_obj_has_value(CowlLogger *logger, CowlObjHasValue *exp) {
    cowl_logger_logf(logger, "ObjectHasValue(");
    cowl_logger_log_obj_prop_exp(logger, exp->prop);
    cowl_logger_logf(logger, " ");
    cowl_logger_log_individual(logger, exp->ind);
    cowl_logger_logf(logger, ")");
}

static void cowl_logger_log_obj_has_self(CowlLogger *logger, CowlObjHasSelf *exp) {
    cowl_logger_logf(logger, "ObjectHasSelf(");
    cowl_logger_log_obj_prop_exp(logger, exp->prop);
    cowl_logger_logf(logger, ")");
}

static void cowl_logger_log_nary_bool(CowlLogger *logger, CowlNAryBool *nary) {
    char const *str = nary->super.type == CCET_OBJ_INTERSECTION ? "Intersection" : "Union";
    cowl_logger_logf(logger, "Object%sOf(", str);
    cowl_logger_log_cls_exp_set(logger, nary->operands);
    cowl_logger_logf(logger, ")");
}

static void cowl_logger_log_obj_compl(CowlLogger *logger, CowlObjCompl *exp) {
    cowl_logger_logf(logger, "ObjectComplementOf(");
    cowl_logger_log_cls_exp(logger, exp->operand);
    cowl_logger_logf(logger, ")");
}

static void cowl_logger_log_obj_one_of(CowlLogger *logger, CowlObjOneOf *exp) {
    cowl_logger_logf(logger, "ObjectOneOf(");
    cowl_logger_log_individual_set(logger, exp->inds);
    cowl_logger_logf(logger, ")");
}

static void cowl_logger_log_data_quant(CowlLogger *logger, CowlDataQuant *exp) {
    char const *str = exp->super.type == CCET_DATA_SOME ? "Some" : "All";
    cowl_logger_logf(logger, "Data%sValuesFrom(", str);
    cowl_logger_log_data_prop_exp(logger, exp->prop);
    cowl_logger_logf(logger, " ");
    cowl_logger_log_data_range(logger, exp->range);
    cowl_logger_logf(logger, ")");
}

static void cowl_logger_log_data_card(CowlLogger *logger, CowlDataCard *exp) {
    char const *str;

    switch (exp->super.type) {
        case CCET_DATA_MIN_CARD: str = "Min"; break;
        case CCET_DATA_MAX_CARD: str = "Max"; break;
        default: str = "Exact"; break;
    }

    cowl_logger_logf(logger, "Data%sCardinality(%lu ", str, exp->cardinality);
    cowl_logger_log_data_prop_exp(logger, exp->prop);

    if (exp->range) {
        cowl_logger_logf(logger, " ");
        cowl_logger_log_data_range(logger, exp->range);
    }

    cowl_logger_logf(logger, ")");
}

static void cowl_logger_log_data_has_value(CowlLogger *logger, CowlDataHasValue *exp) {
    cowl_logger_logf(logger, "DataHasValue(");
    cowl_logger_log_data_prop_exp(logger, exp->prop);
    cowl_logger_logf(logger, " ");
    cowl_logger_log_literal(logger, exp->value);
    cowl_logger_logf(logger, ")");
}

static void cowl_logger_log_datatype_restr(CowlLogger *logger, CowlDatatypeRestr *restr) {
    cowl_logger_logf(logger, "DatatypeRestriction(");
    cowl_logger_log_iri(logger, restr->datatype->iri);
    cowl_logger_logf(logger, " ");
    cowl_logger_log_facet_restr_set(logger, restr->restrictions);
    cowl_logger_logf(logger, ")");
}

static void cowl_logger_log_nary_data(CowlLogger *logger, CowlNAryData *nary) {
    char const *str = nary->super.type == CDRT_DATA_INTERSECTION ? "Intersection" : "Union";
    cowl_logger_logf(logger, "Data%sOf(", str);
    cowl_logger_log_data_range_set(logger, nary->operands);
    cowl_logger_logf(logger, ")");
}

static void cowl_logger_log_data_compl(CowlLogger *logger, CowlDataCompl *range) {
    cowl_logger_logf(logger, "DataComplementOf(");
    cowl_logger_log_data_range(logger, range->operand);
    cowl_logger_logf(logger, ")");
}

static void cowl_logger_log_data_one_of(CowlLogger *logger, CowlDataOneOf *range) {
    cowl_logger_logf(logger, "DataOneOf(");
    cowl_logger_log_literal_set(logger, range->values);
    cowl_logger_logf(logger, ")");
}

static void cowl_logger_log_decl_axiom(CowlLogger *logger, CowlDeclAxiom *axiom) {
    cowl_logger_logf(logger, "Declaration(");
    cowl_logger_log_entity(logger, axiom->entity);
    cowl_logger_logf(logger, ")");
}

static void cowl_logger_log_datatype_def_axiom(CowlLogger *logger, CowlDatatypeDefAxiom *axiom) {
    cowl_logger_logf(logger, "DatatypeDefinition(");
    cowl_logger_log_entity(logger, cowl_entity_wrap_datatype(axiom->datatype));
    cowl_logger_logf(logger, " ");
    cowl_logger_log_data_range(logger, axiom->range);
    cowl_logger_logf(logger, ")");
}

static void cowl_logger_log_sub_cls_axiom(CowlLogger *logger, CowlSubClsAxiom *axiom) {
    cowl_logger_logf(logger, "SubClassOf(");
    cowl_logger_log_cls_exp(logger, axiom->sub_class);
    cowl_logger_logf(logger, " ");
    cowl_logger_log_cls_exp(logger, axiom->super_class);
    cowl_logger_logf(logger, ")");
}

static void cowl_logger_log_nary_cls_axiom(CowlLogger *logger, CowlNAryClsAxiom *axiom) {
    CowlAxiomType const type = cowl_axiom_flags_get_type(axiom->super.flags);
    char const *str = type == CAT_EQUIVALENT_CLASSES ? "Equivalent" : "Disjoint";
    cowl_logger_logf(logger, "%sClasses(", str);
    cowl_logger_log_cls_exp_set(logger, axiom->classes);
    cowl_logger_logf(logger, ")");
}

static void cowl_logger_log_disj_union_axiom(CowlLogger *logger, CowlDisjUnionAxiom *axiom) {
    cowl_logger_logf(logger, "DisjointUnion(");
    cowl_logger_log_cls_exp(logger, (CowlClsExp *)axiom->cls);
    cowl_logger_logf(logger, " ");
    cowl_logger_log_cls_exp_set(logger, axiom->disjoints);
    cowl_logger_logf(logger, ")");
}

static void cowl_logger_log_cls_assert(CowlLogger *logger, CowlClsAssertAxiom *axiom) {
    cowl_logger_logf(logger, "ClassAssertion(");
    cowl_logger_log_individual(logger, axiom->ind);
    cowl_logger_logf(logger, " ");
    cowl_logger_log_cls_exp(logger, axiom->cls_exp);
    cowl_logger_logf(logger, ")");
}

static void cowl_logger_log_nary_ind_axiom(CowlLogger *logger, CowlNAryIndAxiom *axiom) {
    CowlAxiomType const type = cowl_axiom_flags_get_type(axiom->super.flags);
    char const *str = type == CAT_SAME_INDIVIDUAL ? "SameIndividual" : "DifferentIndividuals";
    cowl_logger_logf(logger, "%s(", str);
    cowl_logger_log_individual_set(logger, axiom->operands);
    cowl_logger_logf(logger, ")");
}

static void cowl_logger_log_obj_prop_assert(CowlLogger *logger, CowlObjPropAssertAxiom *axiom) {
    CowlAxiomType const type = cowl_axiom_flags_get_type(axiom->super.flags);
    cowl_logger_logf(logger, "%sObjectPropertyAssertion(",
                     type == CAT_NEGATIVE_OBJ_PROP_ASSERTION ? "Negative" : "");
    cowl_logger_log_individual(logger, axiom->source);
    cowl_logger_logf(logger, " ");
    cowl_logger_log_obj_prop_exp(logger, axiom->prop_exp);
    cowl_logger_logf(logger, " ");
    cowl_logger_log_individual(logger, axiom->target);
    cowl_logger_logf(logger, ")");
}

static void cowl_logger_log_data_prop_assert(CowlLogger *logger, CowlDataPropAssertAxiom *axiom) {
    CowlAxiomType const type = cowl_axiom_flags_get_type(axiom->super.flags);
    cowl_logger_logf(logger, "%sDataPropertyAssertion(",
                     type == CAT_NEGATIVE_OBJ_PROP_ASSERTION ? "Negative" : "");
    cowl_logger_log_individual(logger, axiom->source);
    cowl_logger_logf(logger, " ");
    cowl_logger_log_data_prop_exp(logger, axiom->prop);
    cowl_logger_logf(logger, " ");
    cowl_logger_log_literal(logger, axiom->target);
    cowl_logger_logf(logger, ")");
}

static void cowl_logger_log_sub_obj_prop_axiom(CowlLogger *logger, CowlSubObjPropAxiom *axiom) {
    cowl_logger_logf(logger, "SubObjectPropertyOf(");
    cowl_logger_log_obj_prop_exp(logger, axiom->sub_prop);
    cowl_logger_logf(logger, " ");
    cowl_logger_log_obj_prop_exp(logger, axiom->super_prop);
    cowl_logger_logf(logger, ")");
}

static void cowl_logger_log_sub_obj_prop_chain_axiom(CowlLogger *logger,
                                                     CowlSubObjPropChainAxiom *axiom) {
    cowl_logger_logf(logger, "SubObjectPropertyOf(ObjectPropertyChain(");
    cowl_logger_log_obj_prop_exp_vec(logger, axiom->sub_props);
    cowl_logger_logf(logger, ") ");
    cowl_logger_log_obj_prop_exp(logger, axiom->super_prop);
    cowl_logger_logf(logger, ")");
}

static void cowl_logger_log_inv_obj_prop_axiom(CowlLogger *logger, CowlInvObjPropAxiom *axiom) {
    cowl_logger_logf(logger, "InverseObjectProperties(");
    cowl_logger_log_obj_prop_exp(logger, axiom->first);
    cowl_logger_logf(logger, " ");
    cowl_logger_log_obj_prop_exp(logger, axiom->second);
    cowl_logger_logf(logger, ")");
}

static void cowl_logger_log_nary_obj_prop_axiom(CowlLogger *logger, CowlNAryObjPropAxiom *axiom) {
    CowlAxiomType const type = cowl_axiom_flags_get_type(axiom->super.flags);
    char const *str = type == CAT_EQUIVALENT_OBJ_PROP ? "Equivalent" : "Disjoint";
    cowl_logger_logf(logger, "%sObjectProperties(", str);
    cowl_logger_log_obj_prop_exp_set(logger, axiom->props);
    cowl_logger_logf(logger, ")");
}

static void cowl_logger_log_obj_prop_char(CowlLogger *logger, CowlObjPropCharAxiom *axiom) {
    CowlAxiomType const type = cowl_axiom_flags_get_type(axiom->super.flags);
    const char *str;
    switch (type) {
        case CAT_FUNCTIONAL_OBJ_PROP: str = "Functional"; break;
        case CAT_INVERSE_FUNCTIONAL_OBJ_PROP: str = "InverseFunctional"; break;
        case CAT_SYMMETRIC_OBJ_PROP: str = "Symmetric"; break;
        case CAT_ASYMMETRIC_OBJ_PROP: str = "Asymmetric"; break;
        case CAT_REFLEXIVE_OBJ_PROP: str = "Reflexive"; break;
        case CAT_IRREFLEXIVE_OBJ_PROP: str = "Irreflexive"; break;
        default: str = "Transitive"; break;
    }
    cowl_logger_logf(logger, "%sObjectProperty(", str);
    cowl_logger_log_obj_prop_exp(logger, axiom->prop_exp);
    cowl_logger_logf(logger, ")");
}

static void cowl_logger_log_obj_prop_domain(CowlLogger *logger, CowlObjPropDomainAxiom *axiom) {
    cowl_logger_logf(logger, "ObjectPropertyDomain(");
    cowl_logger_log_obj_prop_exp(logger, axiom->prop_exp);
    cowl_logger_logf(logger, " ");
    cowl_logger_log_cls_exp(logger, axiom->domain);
    cowl_logger_logf(logger, ")");
}

static void cowl_logger_log_obj_prop_range(CowlLogger *logger, CowlObjPropRangeAxiom *axiom) {
    cowl_logger_logf(logger, "ObjectPropertyRange(");
    cowl_logger_log_obj_prop_exp(logger, axiom->prop_exp);
    cowl_logger_logf(logger, " ");
    cowl_logger_log_cls_exp(logger, axiom->range);
    cowl_logger_logf(logger, ")");
}

static void cowl_logger_log_sub_data_prop_axiom(CowlLogger *logger, CowlSubDataPropAxiom *axiom) {
    cowl_logger_logf(logger, "SubDataPropertyOf(");
    cowl_logger_log_data_prop_exp(logger, axiom->sub_prop);
    cowl_logger_logf(logger, " ");
    cowl_logger_log_data_prop_exp(logger, axiom->super_prop);
    cowl_logger_logf(logger, ")");
}

static void cowl_logger_log_nary_data_prop_axiom(CowlLogger *logger, CowlNAryDataPropAxiom *axiom) {
    CowlAxiomType const type = cowl_axiom_flags_get_type(axiom->super.flags);
    char const *str = type == CAT_EQUIVALENT_DATA_PROP ? "Equivalent" : "Disjoint";
    cowl_logger_logf(logger, "%sDataProperties(", str);
    cowl_logger_log_data_prop_exp_set(logger, axiom->props);
    cowl_logger_logf(logger, ")");
}

static void cowl_logger_log_func_data_prop_axiom(CowlLogger *logger, CowlFuncDataPropAxiom *axiom) {
    cowl_logger_logf(logger, "FunctionalDataProperty(");
    cowl_logger_log_data_prop_exp(logger, axiom->prop);
    cowl_logger_logf(logger, ")");
}

static void cowl_logger_log_data_prop_domain(CowlLogger *logger, CowlDataPropDomainAxiom *axiom) {
    cowl_logger_logf(logger, "DataPropertyDomain(");
    cowl_logger_log_data_prop_exp(logger, axiom->prop_exp);
    cowl_logger_logf(logger, " ");
    cowl_logger_log_cls_exp(logger, axiom->domain);
    cowl_logger_logf(logger, ")");
}

static void cowl_logger_log_data_prop_range(CowlLogger *logger, CowlDataPropRangeAxiom *axiom) {
    cowl_logger_logf(logger, "DataPropertyRange(");
    cowl_logger_log_data_prop_exp(logger, axiom->prop_exp);
    cowl_logger_logf(logger, " ");
    cowl_logger_log_data_range(logger, axiom->range);
    cowl_logger_logf(logger, ")");
}

static void cowl_logger_log_has_key_axiom(CowlLogger *logger, CowlHasKeyAxiom *axiom) {
    cowl_logger_logf(logger, "HasKey(");
    cowl_logger_log_cls_exp(logger, axiom->cls_exp);
    cowl_logger_logf(logger, " ");
    cowl_logger_log_obj_prop_exp_set(logger, axiom->obj_props);
    cowl_logger_logf(logger, " ");
    cowl_logger_log_data_prop_exp_set(logger, axiom->data_props);
    cowl_logger_logf(logger, ")");
}

static void cowl_logger_log_annot_assert(CowlLogger *logger, CowlAnnotAssertAxiom *axiom) {
    cowl_logger_logf(logger, "AnnotationAssertion(");
    cowl_logger_log_annot_value(logger, axiom->subject);
    cowl_logger_logf(logger, " ");
    cowl_logger_log_annot_prop(logger, axiom->prop);
    cowl_logger_logf(logger, " ");
    cowl_logger_log_annot_value(logger, axiom->value);
    cowl_logger_logf(logger, ")");
}

static void cowl_logger_log_sub_annot_prop_axiom(CowlLogger *logger, CowlSubAnnotPropAxiom *axiom) {
    cowl_logger_logf(logger, "SubAnnotationPropertyOf(");
    cowl_logger_log_annot_prop(logger, axiom->sub_prop);
    cowl_logger_logf(logger, " ");
    cowl_logger_log_annot_prop(logger, axiom->super_prop);
    cowl_logger_logf(logger, ")");
}

static void cowl_logger_log_annot_prop_domain_axiom(CowlLogger *logger,
                                                    CowlAnnotPropDomainAxiom *axiom) {
    cowl_logger_logf(logger, "AnnotationPropertyDomain(");
    cowl_logger_log_annot_prop(logger, axiom->prop);
    cowl_logger_logf(logger, " ");
    cowl_logger_log_iri(logger, axiom->domain);
    cowl_logger_logf(logger, ")");
}

static void cowl_logger_log_annot_prop_range_axiom(CowlLogger *logger,
                                                   CowlAnnotPropRangeAxiom *axiom) {
    cowl_logger_logf(logger, "AnnotationPropertyRange(");
    cowl_logger_log_annot_prop(logger, axiom->prop);
    cowl_logger_logf(logger, " ");
    cowl_logger_log_iri(logger, axiom->range);
    cowl_logger_logf(logger, ")");
}
