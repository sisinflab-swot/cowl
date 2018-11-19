/// @author Ivano Bilenchi

#include "cowl_logger.h"
#include "cowl_private.h"

#include <stdio.h>
#include <stdarg.h>

#pragma mark - Types

typedef enum CowlLoggerType {
    COWL_LT_NULL,
    COWL_LT_CONSOLE,
    COWL_LT_FILE
} CowlLoggerType;

struct CowlLogger {
    CowlLoggerType const type;

    char const *path;
    FILE *file;
};

#pragma mark - Lifecycle

static CowlLogger* cowl_logger_alloc(CowlLoggerType type, void *context) {
    CowlLogger logger_init = { .type = type };
    CowlLogger *logger = malloc(sizeof(*logger));
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

    free(logger);
}

void cowl_logger_open(CowlLogger *logger) {
    if (logger->type != COWL_LT_FILE) return;

    if (!logger->file) {
        logger->file = fopen(logger->path, "a");
    }
}

void cowl_logger_close(CowlLogger *logger) {
    if (logger->type != COWL_LT_FILE) return;

    if (logger->file) {
        fclose(logger->file);
        logger->file = NULL;
    }
}

void cowl_logger_clear(CowlLogger *logger) {
    cowl_logger_close(logger);

    if (logger->type == COWL_LT_FILE) {
        remove(logger->path);
    }
}

#pragma mark - Logging

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

void cowl_logger_log_axioms_in_ontology(CowlLogger *logger, CowlOntology *ontology) {
    cowl_ontology_iterate_axioms(ontology, logger, axiom_logger);
}

static bool entity_logger(void *ctx, CowlEntity entity) {
    struct CowlLogger *logger = ctx;
    cowl_logger_log_entity(logger, entity);
    cowl_logger_logf(logger, "\n");
    return true;
}

void cowl_logger_log_entities_in_ontology(CowlLogger *logger, CowlOntology *ontology) {
    cowl_ontology_iterate_signature(ontology, logger, entity_logger);
}

void cowl_logger_log_ontology_id(CowlLogger *logger, CowlOntologyId *id) {
    cowl_logger_logf(logger, "Ontology(");
    cowl_logger_log_iri(logger, id->onto_iri);

    if (id->version_iri) {
        cowl_logger_logf(logger, " ");
        cowl_logger_log_iri(logger, id->version_iri);
    }

    cowl_logger_logf(logger, ")");
}

void cowl_logger_log_ontology(CowlLogger *logger, CowlOntology *ontology) {
    cowl_logger_log_ontology_id(logger, ontology->id);
    cowl_logger_logf(logger, "\n");
    cowl_logger_log_entities_in_ontology(logger, ontology);
    cowl_logger_log_axioms_in_ontology(logger, ontology);
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
        case CET_ANNOTATION_PROP: type = "AnnotationProperty"; break;
        case CET_NAMED_INDIVIDUAL: type = "NamedIndividual"; break;
        case CET_DATATYPE: type = "Datatype"; break;
    }

    cowl_logger_logf(logger, "%s(", type);
    cowl_logger_log_iri(logger, cowl_entity_get_iri(entity));
    cowl_logger_logf(logger, ")");
}

static void cowl_logger_log_cls_exp_set(CowlLogger *logger, CowlClsExpSet *set) {
    uint32_t current = 0, last = kh_count(set) - 1;

    kh_foreach_key(set, CowlClsExp *exp, {
        cowl_logger_log_cls_exp(logger, exp);
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

static void cowl_logger_log_nary_bool(CowlLogger *logger, CowlNAryBool *nary) {
    char const *str = nary->super.type == CCET_OBJ_INTERSECTION ? "Intersection" : "Union";
    cowl_logger_logf(logger, "Object%sOf(", str);
    cowl_logger_log_cls_exp_set(logger, nary->operands);
    cowl_logger_logf(logger, ")");
}

static void cowl_logger_log_obj_compl(CowlLogger *logger, CowlObjCompl *compl) {
    cowl_logger_logf(logger, "ObjectComplementOf(");
    cowl_logger_log_cls_exp(logger, compl->operand);
    cowl_logger_logf(logger, ")");
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

        case CCET_OBJ_INTERSECTION:
        case CCET_OBJ_UNION:
            cowl_logger_log_nary_bool(logger, (CowlNAryBool *)exp);
            break;

        case CCET_OBJ_COMPLEMENT:
            cowl_logger_log_obj_compl(logger, (CowlObjCompl *)exp);
            break;

        default:
            break;
    }
}

void cowl_logger_log_individual(CowlLogger *logger, CowlIndividual *individual) {
    if (individual->is_named) {
        CowlNamedIndividual *named_ind = (CowlNamedIndividual *)individual;
        cowl_logger_log_entity(logger, cowl_entity_wrap_named_individual(named_ind));
    } else {
        CowlAnonIndividual *anon_ind = (CowlAnonIndividual *)individual;
        cowl_logger_logf(logger, "AnonymousIndividual(");
        cowl_logger_log_string(logger, anon_ind->id);
        cowl_logger_logf(logger, ")");
    }
}

void cowl_logger_log_obj_prop_exp(CowlLogger *logger, CowlObjPropExp *exp) {
    if (exp->is_inverse) cowl_logger_logf(logger, "ObjectInverseOf(");
    cowl_logger_log_entity(logger, cowl_entity_wrap_obj_prop(cowl_obj_prop_exp_get_prop(exp)));
    if (exp->is_inverse) cowl_logger_logf(logger, ")");
}

static void cowl_logger_log_decl_axiom(CowlLogger *logger, CowlDeclAxiom *axiom) {
    cowl_logger_logf(logger, "Declaration(");
    cowl_logger_log_entity(logger, axiom->entity);
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
    char const *str = axiom->super.type == CAT_EQUIVALENT_CLASSES ? "Equivalent" : "Disjoint";
    cowl_logger_logf(logger, "%sClasses(", str);
    cowl_logger_log_cls_exp_set(logger, axiom->classes);
    cowl_logger_logf(logger, ")");
}

static void cowl_logger_log_cls_assert(CowlLogger *logger, CowlClsAssertAxiom *axiom) {
    cowl_logger_logf(logger, "ClassAssertion(");
    cowl_logger_log_individual(logger, axiom->individual);
    cowl_logger_logf(logger, " ");
    cowl_logger_log_cls_exp(logger, axiom->cls_exp);
    cowl_logger_logf(logger, ")");
}

static void cowl_logger_log_obj_prop_assert(CowlLogger *logger, CowlObjPropAssertAxiom *axiom) {
    cowl_logger_logf(logger, "ObjectPropertyAssertion(");
    cowl_logger_log_individual(logger, axiom->source);
    cowl_logger_logf(logger, " ");
    cowl_logger_log_obj_prop_exp(logger, axiom->prop_exp);
    cowl_logger_logf(logger, " ");
    cowl_logger_log_individual(logger, axiom->target);
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

static void cowl_logger_log_obj_prop_char(CowlLogger *logger, CowlObjPropCharAxiom *axiom) {
    const char *str;
    switch (axiom->super.type) {
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

void cowl_logger_log_axiom(CowlLogger *logger, CowlAxiom *axiom) {
    CowlAxiomType type = axiom->type;

    switch (type) {

        case CAT_DECLARATION:
            cowl_logger_log_decl_axiom(logger, (CowlDeclAxiom *)axiom);
            break;

        case CAT_SUB_CLASS:
            cowl_logger_log_sub_cls_axiom(logger, (CowlSubClsAxiom *)axiom);
            break;

        case CAT_EQUIVALENT_CLASSES:
        case CAT_DISJOINT_CLASSES:
            cowl_logger_log_nary_cls_axiom(logger, (CowlNAryClsAxiom *)axiom);
            break;

        case CAT_CLASS_ASSERTION:
            cowl_logger_log_cls_assert(logger, (CowlClsAssertAxiom *)axiom);
            break;

        case CAT_OBJ_PROP_ASSERTION:
            cowl_logger_log_obj_prop_assert(logger, (CowlObjPropAssertAxiom *)axiom);
            break;

        case CAT_OBJ_PROP_DOMAIN:
            cowl_logger_log_obj_prop_domain(logger, (CowlObjPropDomainAxiom *)axiom);
            break;

        case CAT_OBJ_PROP_RANGE:
            cowl_logger_log_obj_prop_range(logger, (CowlObjPropRangeAxiom *)axiom);
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

        default:
            break;
    }
}

void cowl_logger_log_error(CowlLogger *logger, CowlError error) {
    CowlString *string = cowl_error_to_string(error);
    cowl_logger_log_string(logger, string);
    cowl_string_release(string);
}

#pragma mark - Other

char const* cowl_logger_get_path(CowlLogger *logger) {
    if (logger->type != COWL_LT_FILE) return NULL;
    return logger->path;
}
