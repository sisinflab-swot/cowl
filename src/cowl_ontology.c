/// @author Ivano Bilenchi

#include "cowl_ontology_private.h"
#include "cowl_anon_individual.h"
#include "cowl_axiom_private.h"
#include "cowl_class.h"
#include "cowl_cls_assert_axiom_private.h"
#include "cowl_cls_exp_private.h"
#include "cowl_decl_axiom_private.h"
#include "cowl_disj_cls_axiom_private.h"
#include "cowl_eq_cls_axiom_private.h"
#include "cowl_individual_private.h"
#include "cowl_named_individual.h"
#include "cowl_obj_prop.h"
#include "cowl_obj_prop_assert_axiom_private.h"
#include "cowl_obj_prop_domain_axiom_private.h"
#include "cowl_obj_prop_exp_private.h"
#include "cowl_obj_prop_range_axiom_private.h"
#include "cowl_ontology_id.h"
#include "cowl_sub_cls_axiom_private.h"

#pragma mark - Types

KHASH_MAP_UTILS_IMPL(CowlClassAxiomMap, CowlClass const*, khash_t(CowlAxiomSet)*,
                     cowl_class_hash, cowl_class_equals);

KHASH_MAP_UTILS_IMPL(CowlObjPropAxiomMap, CowlObjProp const*, khash_t(CowlAxiomSet) *,
                     cowl_obj_prop_hash, cowl_obj_prop_equals);

KHASH_MAP_UTILS_IMPL(CowlNamedIndAxiomMap, CowlNamedIndividual const*, khash_t(CowlAxiomSet) *,
                     cowl_named_individual_hash, cowl_named_individual_equals);

KHASH_MAP_UTILS_IMPL(CowlAnonIndAxiomMap, CowlAnonIndividual const*, khash_t(CowlAxiomSet) *,
                     cowl_anon_individual_hash, cowl_anon_individual_equals);

typedef struct CowlAxiomEntityCtx {
    CowlOntology *onto;
    CowlAxiom const *axiom;
    bool added;
} CowlAxiomEntityCtx;

#pragma mark - Private prototypes

static bool cowl_ontology_entity_adder(void *ctx, CowlEntity entity);
static bool cowl_ontology_add_axiom_for_entity(CowlOntology *onto, CowlAxiom const *axiom,
                                               CowlEntity entity);
static bool cowl_ontology_add_axiom_for_cls_exp(CowlOntology *onto, CowlAxiom const *axiom,
                                                CowlClsExp const *exp);
static bool cowl_ontology_add_axiom_for_prop_exp(CowlOntology *onto, CowlAxiom const *axiom,
                                                 CowlObjPropExp const *prop_exp);
static bool cowl_ontology_add_axiom_for_individual(CowlOntology *onto, CowlAxiom const *axiom,
                                                   CowlIndividual const *individual);

#pragma mark - Utils

#define cowl_add_axiom_to_set_in_map(T, map, key, axiom, added) do {                                \
    bool __cowl_absent;                                                                             \
    khint_t k = kh_put_key(T, map, key, &__cowl_absent);                                            \
                                                                                                    \
    khash_t(CowlAxiomSet) *__cowl_axioms;                                                           \
                                                                                                    \
    if (__cowl_absent) {                                                                            \
        __cowl_axioms = kh_init(CowlAxiomSet);                                                      \
        kh_value(map, k) = __cowl_axioms;                                                           \
    } else {                                                                                        \
        __cowl_axioms = kh_value(map, k);                                                           \
    }                                                                                               \
                                                                                                    \
    added = kh_insert(CowlAxiomSet, __cowl_axioms, axiom);                                          \
} while(0)

#define cowl_add_axiom_to_set_in_array(array, idx, axiom, added) do {                               \
    khash_t(CowlAxiomSet) *__cowl_axioms = array[idx];                                              \
                                                                                                    \
    if (__cowl_axioms) {                                                                            \
        __cowl_axioms = kh_init(CowlAxiomSet);                                                      \
        array[idx] = __cowl_axioms;                                                                 \
    }                                                                                               \
                                                                                                    \
    added = kh_insert(CowlAxiomSet, __cowl_axioms, axiom);                                          \
} while(0)

#pragma mark - Public API

CowlOntologyId const* cowl_ontology_get_id(CowlOntology const *onto) {
    return onto->id;
}

bool cowl_ontology_equals(CowlOntology const *lhs, CowlOntology const *rhs) {
    return cowl_ontology_id_equals(lhs->id, rhs->id);
}

uint32_t cowl_ontology_hash(CowlOntology const *onto) {
    return cowl_ontology_id_hash(onto->id);
}

void cowl_ontology_iterate_axioms(CowlOntology const *onto, void *ctx, CowlAxiomIterator iter) {
    for (CowlAxiomType type = 0; type < CAT_COUNT; ++type) {
        khash_t(CowlAxiomSet) *axioms = onto->axioms_by_type[type];
        kh_foreach_key(axioms, CowlAxiom const *axiom, {
            if (!iter(ctx, axiom)) return;
        });
    }
}

void cowl_ontology_iterate_axioms_of_type(CowlOntology const *onto, CowlAxiomType type,
                                       void *ctx, CowlAxiomIterator iter) {
    khash_t(CowlAxiomSet) *axioms = onto->axioms_by_type[type];

    kh_foreach_key(axioms, CowlAxiom const *axiom, {
        if (!iter(ctx, axiom)) return;
    });
}

void cowl_ontology_iterate_axioms_for_class(CowlOntology const *onto, CowlClass const *owl_class,
                                         void *ctx, CowlAxiomIterator iter) {
    khash_t(CowlAxiomSet) *axioms = kh_get_val(CowlClassAxiomMap, onto->class_refs,
                                               owl_class, NULL);

    kh_foreach_key(axioms, CowlAxiom const *axiom, {
        if (!iter(ctx, axiom)) return;
    });
}

void cowl_ontology_iterate_axioms_for_obj_prop(CowlOntology const *onto, CowlObjProp const *obj_prop,
                                            void *ctx, CowlAxiomIterator iter) {
    khash_t(CowlAxiomSet) *axioms = kh_get_val(CowlObjPropAxiomMap, onto->obj_prop_refs,
                                               obj_prop, NULL);

    kh_foreach_key(axioms, CowlAxiom const *axiom, {
        if (!iter(ctx, axiom)) return;
    });
}

void cowl_ontology_iterate_axioms_for_named_individual(CowlOntology const *onto,
                                                    CowlNamedIndividual const *individual,
                                                    void *ctx, CowlAxiomIterator iter) {
    khash_t(CowlAxiomSet) *axioms = kh_get_val(CowlNamedIndAxiomMap, onto->named_ind_refs,
                                               individual, NULL);

    kh_foreach_key(axioms, CowlAxiom const *axiom, {
        if (!iter(ctx, axiom)) return;
    });
}

void cowl_ontology_iterate_sub_classes(CowlOntology const *onto, CowlClass const *owl_class,
                                    void *ctx, CowlClsExpIterator iter) {
    khash_t(CowlAxiomSet) *axioms = kh_get_val(CowlClassAxiomMap, onto->class_refs,
                                               owl_class, NULL);

    kh_foreach_key(axioms, CowlAxiom const *axiom, {
        if (axiom->type == CAT_SUB_CLASS) {
            CowlSubClsAxiom *sub_axiom = (CowlSubClsAxiom *)axiom;

            if (cowl_cls_exp_equals((CowlClsExp *)owl_class, sub_axiom->super_class)) {
                if (!iter(ctx, sub_axiom->sub_class)) return;
            }
        }
    });
}

void cowl_ontology_iterate_super_classes(CowlOntology const *onto, CowlClass const *owl_class,
                                      void *ctx, CowlClsExpIterator iter) {
    khash_t(CowlAxiomSet) *axioms = kh_get_val(CowlClassAxiomMap, onto->class_refs,
                                               owl_class, NULL);

    kh_foreach_key(axioms, CowlAxiom const *axiom, {
        if (axiom->type == CAT_SUB_CLASS) {
            CowlSubClsAxiom *sub_axiom = (CowlSubClsAxiom *)axiom;

            if (cowl_cls_exp_equals((CowlClsExp *)owl_class, sub_axiom->sub_class)) {
                if (!iter(ctx, sub_axiom->super_class)) return;
            }
        }
    });
}

void cowl_ontology_iterate_eq_classes(CowlOntology const *onto, CowlClass const *owl_class,
                                   void *ctx, CowlClsExpIterator iter) {
    khash_t(CowlAxiomSet) *axioms = kh_get_val(CowlClassAxiomMap, onto->class_refs,
                                               owl_class, NULL);

    kh_foreach_key(axioms, CowlAxiom const *axiom, {
        if (axiom->type == CAT_EQUIVALENT_CLASSES) {
            khash_t(CowlClsExpSet) const *eq_classes = ((CowlEqClsAxiom *)axiom)->classes;

            khint_t cls_idx = kh_get(CowlClsExpSet, eq_classes, (CowlClsExp *)owl_class);
            if (cls_idx < kh_end(eq_classes)) {
                for (khint_t i = kh_begin(eq_classes); i != kh_end(eq_classes); ++i) {
                    if (i != cls_idx && !iter(ctx, kh_key(eq_classes, i))) return;
                }
            }
        }
    });
}

void cowl_ontology_iterate_types(CowlOntology const *onto, CowlIndividual const *individual,
                              void *ctx, CowlClsExpIterator iter) {
    khash_t(CowlAxiomSet) *axioms;

    if (individual->is_named) {
        axioms = kh_get_val(CowlNamedIndAxiomMap, onto->named_ind_refs,
                            (CowlNamedIndividual *)individual, NULL);
    } else {
        axioms = kh_get_val(CowlAnonIndAxiomMap, onto->anon_ind_refs,
                            (CowlAnonIndividual *)individual, NULL);
    }

    kh_foreach_key(axioms, CowlAxiom const *axiom, {
        if (axiom->type == CAT_CLASS_ASSERTION) {
            CowlClsAssertAxiom *assert_axiom = (CowlClsAssertAxiom *)axiom;
            if (!iter(ctx, assert_axiom->cls_exp)) return;
        }
    });
}

#pragma mark - Private API

bool cowl_ontology_add_axiom(CowlOntology *ontology, CowlAxiom const *axiom) {
    bool added = false;

    bool temp_added;
    cowl_add_axiom_to_set_in_array(ontology->axioms_by_type, axiom->type, axiom, temp_added);
    added |= temp_added;

    switch (axiom->type) {

        case CAT_CLASS_ASSERTION: {
            CowlClsAssertAxiom *as_axiom = (CowlClsAssertAxiom *)axiom;
            added |= cowl_ontology_add_axiom_for_individual(ontology, axiom, as_axiom->individual);
            added |= cowl_ontology_add_axiom_for_cls_exp(ontology, axiom, as_axiom->cls_exp);
            break;
        }

        case CAT_DECLARATION: {
            CowlDeclAxiom *decl_axiom = (CowlDeclAxiom *)axiom;
            added |= cowl_ontology_add_axiom_for_entity(ontology, axiom, decl_axiom->entity);
            break;
        }

        case CAT_DISJOINT_CLASSES: {
            CowlDisjClsAxiom *disj_axiom = (CowlDisjClsAxiom *)axiom;

            CowlAxiomEntityCtx ctx = { .onto = ontology, .axiom = axiom, .added = false };
            cowl_disj_cls_axiom_iterate_signature(disj_axiom, &ctx, cowl_ontology_entity_adder);
            added |= ctx.added;
            break;
        }

        case CAT_EQUIVALENT_CLASSES: {
            CowlEqClsAxiom *eq_axiom = (CowlEqClsAxiom *)axiom;
            CowlAxiomEntityCtx ctx = { .onto = ontology, .axiom = axiom, .added = false };
            cowl_eq_cls_axiom_iterate_signature(eq_axiom, &ctx, cowl_ontology_entity_adder);
            added |= ctx.added;
            break;
        }

        case CAT_OBJ_PROP_ASSERTION: {
            CowlObjPropAssertAxiom *as_axiom = (CowlObjPropAssertAxiom *)axiom;
            added |= cowl_ontology_add_axiom_for_individual(ontology, axiom, as_axiom->source);
            added |= cowl_ontology_add_axiom_for_individual(ontology, axiom, as_axiom->target);
            added |= cowl_ontology_add_axiom_for_prop_exp(ontology, axiom, as_axiom->prop_exp);
            break;
        }

        case CAT_OBJ_PROP_DOMAIN: {
            CowlObjPropDomainAxiom *dom_axiom = (CowlObjPropDomainAxiom *)axiom;
            added |= cowl_ontology_add_axiom_for_prop_exp(ontology, axiom, dom_axiom->prop_exp);
            added |= cowl_ontology_add_axiom_for_cls_exp(ontology, axiom, dom_axiom->domain);
            break;
        }

        case CAT_OBJ_PROP_RANGE: {
            CowlObjPropRangeAxiom *r_axiom = (CowlObjPropRangeAxiom *)axiom;
            added |= cowl_ontology_add_axiom_for_prop_exp(ontology, axiom, r_axiom->prop_exp);
            added |= cowl_ontology_add_axiom_for_cls_exp(ontology, axiom, r_axiom->range);
            break;
        }

        case CAT_SUB_CLASS: {
            CowlSubClsAxiom *sub_axiom = (CowlSubClsAxiom *)axiom;
            added |= cowl_ontology_add_axiom_for_cls_exp(ontology, axiom, sub_axiom->super_class);
            added |= cowl_ontology_add_axiom_for_cls_exp(ontology, axiom, sub_axiom->sub_class);
            break;
        }

        default:
            break;
    }

    return added;
}

static bool cowl_ontology_add_axiom_for_entity(CowlOntology *onto, CowlAxiom const *axiom,
                                               CowlEntity entity) {
    bool added;

    switch (entity.type) {

        case CET_CLASS:
            cowl_add_axiom_to_set_in_map(CowlClassAxiomMap, onto->class_refs,
                                         entity.owl_class, axiom, added);
            break;

        case CET_OBJ_PROP:
            cowl_add_axiom_to_set_in_map(CowlObjPropAxiomMap, onto->obj_prop_refs,
                                         entity.obj_prop, axiom, added);
            break;

        case CET_NAMED_INDIVIDUAL:
            cowl_add_axiom_to_set_in_map(CowlNamedIndAxiomMap, onto->named_ind_refs,
                                         entity.named_ind, axiom, added);
            break;

        default:
            added = false;
            break;
    }

    return added;
}

static bool cowl_ontology_entity_adder(void *ctx, CowlEntity entity) {
    CowlAxiomEntityCtx *axiom_ctx = (CowlAxiomEntityCtx *)ctx;
    axiom_ctx->added |= cowl_ontology_add_axiom_for_entity(axiom_ctx->onto,
                                                           axiom_ctx->axiom, entity);
    return true;
}

static bool cowl_ontology_add_axiom_for_cls_exp(CowlOntology *onto, CowlAxiom const *axiom,
                                                CowlClsExp const *exp) {
    bool added;

    if (exp->type == CCET_CLASS) {
        cowl_add_axiom_to_set_in_map(CowlClassAxiomMap, onto->class_refs,
                                     (CowlClass *)exp, axiom, added);
    } else {
        CowlAxiomEntityCtx ctx = { .onto = onto, .axiom = axiom, .added = false };
        cowl_cls_exp_iterate_signature(exp, &ctx, cowl_ontology_entity_adder);
        added = ctx.added;
    }

    return added;
}

static bool cowl_ontology_add_axiom_for_individual(CowlOntology *onto, CowlAxiom const *axiom,
                                                   CowlIndividual const *individual) {
    bool added;

    if (individual->is_named) {
        cowl_add_axiom_to_set_in_map(CowlNamedIndAxiomMap, onto->named_ind_refs,
                                     (CowlNamedIndividual *)individual, axiom, added);
    } else {
        cowl_add_axiom_to_set_in_map(CowlAnonIndAxiomMap, onto->anon_ind_refs,
                                     (CowlAnonIndividual *)individual, axiom, added);
    }

    return added;
}

static bool cowl_ontology_add_axiom_for_prop_exp(CowlOntology *onto, CowlAxiom const *axiom,
                                                 CowlObjPropExp const *prop_exp) {
    bool added = false;

    if (!prop_exp->is_inverse) {
        cowl_add_axiom_to_set_in_map(CowlObjPropAxiomMap, onto->obj_prop_refs,
                                     (CowlObjProp *)prop_exp, axiom, added);
    }

    return added;
}
