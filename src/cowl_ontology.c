/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_ontology_private.h"
#include "cowl_private.h"

typedef struct CowlAxiomCtx {
    cowl_ret ret;
    CowlOntology *onto;
    CowlAxiom *axiom;
} CowlAxiomCtx;

// Private prototypes

static CowlOntology* cowl_ontology_alloc(void);
static void cowl_ontology_free(CowlOntology *onto);
static cowl_ret cowl_ontology_add_primitive(CowlOntology *onto, CowlObject *obj);
static cowl_ret cowl_ontology_add_axiom_for_primitive(CowlOntology *onto, CowlAxiom *axiom,
                                                      CowlObject *obj);
static bool cowl_ontology_primitive_axiom_adder(void *ctx, void *obj);
static bool cowl_ontology_primitive_adder(void *ctx, void *obj);

// Public API

CowlOntology* cowl_ontology_retain(CowlOntology *onto) {
    return cowl_object_incr_ref(onto);
}

void cowl_ontology_release(CowlOntology *onto) {
    if (onto && !cowl_object_decr_ref(onto)) {
        cowl_ontology_free(onto);
    }
}

CowlOntologyId cowl_ontology_get_id(CowlOntology *onto) {
    return onto->id;
}

CowlObjectVec* cowl_ontology_get_annot(CowlOntology *onto) {
    return &onto->annotations;
}

CowlString* cowl_ontology_to_string(CowlOntology *onto)
    COWL_TO_STRING_IMPL(ontology, onto)

bool cowl_ontology_equals(CowlOntology *lhs, CowlOntology *rhs) {
    if (lhs == rhs) return true;

    // If the ontology IRIs are both NULL, then both ontologies are anonymous.
    // If they were equal, they would have passed the pointer equality check.
    if (!(lhs->id.ontology_iri || rhs->id.ontology_iri)) return false;

    return cowl_ontology_id_equals(lhs->id, rhs->id);
}

ulib_uint cowl_ontology_hash(CowlOntology *onto) {
    return cowl_hash_1(COWL_HASH_INIT_ONTO, cowl_ontology_id_hash(onto->id));
}

ulib_uint cowl_ontology_axiom_count(CowlOntology *onto) {
    ulib_uint count = 0;

    for (CowlAxiomType type = COWL_AT_FIRST; type < COWL_AT_COUNT; ++type) {
        count += uvec_count(CowlObjectPtr, &onto->axioms_by_type[type]);
    }

    uvec_foreach(CowlObjectPtr, &onto->imports, import) {
        count += cowl_ontology_axiom_count(*import.item);
    }

    return count;
}

ulib_uint cowl_ontology_imports_count(CowlOntology *onto) {
    ulib_uint count = uvec_count(CowlObjectPtr, &onto->imports);

    uvec_foreach(CowlObjectPtr, &onto->imports, import) {
        count += cowl_ontology_imports_count(*import.item);
    }

    return count;
}

ulib_uint cowl_ontology_axiom_count_for_type(CowlOntology *onto, CowlAxiomType type) {
    ulib_uint count = uvec_count(CowlObjectPtr, &onto->axioms_by_type[type]);

    uvec_foreach(CowlObjectPtr, &onto->imports, import) {
        count += cowl_ontology_axiom_count_for_type(*import.item, type);
    }

    return count;
}

static cowl_ret cowl_ontology_add_axiom_to_map(CowlObject *entity, CowlAxiom *axiom,
                                               UHash(CowlObjectTable) *map) {
    ulib_uint idx;
    uhash_ret ret = uhash_put(CowlObjectTable, map, entity, &idx);
    if (ret == UHASH_ERR) return COWL_ERR_MEM;

    UVec(CowlObjectPtr) *vec = uhash_value(CowlObjectTable, map, idx);

    if (ret == UHASH_INSERTED || !vec) {
        vec = uvec_alloc(CowlObjectPtr);
        uhash_value(CowlObjectTable, map, idx) = vec;
    }

    if (uvec_push(CowlObjectPtr, vec, axiom)) {
        return COWL_ERR_MEM;
    }

    return COWL_OK;
}

static cowl_ret cowl_ontology_add_primitive_to_map(CowlObject *entity,
                                                   UHash(CowlObjectTable) *map) {
    ulib_uint idx;
    uhash_ret ret = uhash_put(CowlObjectTable, map, entity, &idx);
    if (ret == UHASH_ERR) return COWL_ERR_MEM;

    if (ret == UHASH_INSERTED) {
        uhash_value(CowlObjectTable, map, idx) = NULL;
    }

    return COWL_OK;
}

#define COWL_ONTOLOGY_ENTITY_QUERY_IMPL(T, SINGULAR, PLURAL)                                        \
                                                                                                    \
ulib_uint cowl_ontology_##PLURAL##_count(CowlOntology *onto) {                                      \
    return uhash_count(CowlObjectTable, &onto->SINGULAR##_refs);                                    \
}                                                                                                   \
                                                                                                    \
bool cowl_ontology_iterate_##PLURAL(CowlOntology *onto, CowlIterator *iter) {                       \
    uhash_foreach(CowlObjectTable, &onto->SINGULAR##_refs, SINGULAR) {                              \
        if (!cowl_iterate(iter, *(SINGULAR).key)) return false;                                     \
    }                                                                                               \
    return true;                                                                                    \
}                                                                                                   \
                                                                                                    \
ulib_uint cowl_ontology_axiom_count_for_##SINGULAR(CowlOntology *onto, T *entity) {                 \
    UHash(CowlObjectTable) *map = &onto->SINGULAR##_refs;                                           \
    UVec(CowlObjectPtr) *axioms = uhmap_get(CowlObjectTable, map, entity, NULL);                    \
    if (!axioms) return 0;                                                                          \
    ulib_uint count = uvec_count(CowlObjectPtr, axioms);                                            \
                                                                                                    \
    uvec_foreach(CowlObjectPtr, &onto->imports, import) {                                           \
        count += cowl_ontology_axiom_count_for_##SINGULAR(*import.item, entity);                    \
    }                                                                                               \
                                                                                                    \
    return count;                                                                                   \
}                                                                                                   \
                                                                                                    \
bool cowl_ontology_iterate_axioms_for_##SINGULAR(CowlOntology *onto, T *entity,                     \
                                                 CowlIterator *iter) {                              \
    UHash(CowlObjectTable) *map = &onto->SINGULAR##_refs;                                           \
    UVec(CowlObjectPtr) *axioms = uhmap_get(CowlObjectTable, map, entity, NULL);                    \
                                                                                                    \
    uvec_foreach(CowlObjectPtr, axioms, axiom) {                                                    \
        if (!cowl_iterate(iter, *axiom.item)) return false;                                         \
    }                                                                                               \
                                                                                                    \
    uvec_foreach(CowlObjectPtr, &onto->imports, import) {                                           \
        if (!cowl_ontology_iterate_axioms_for_##SINGULAR(*import.item, entity, iter)) {             \
            return false;                                                                           \
        }                                                                                           \
    }                                                                                               \
                                                                                                    \
    return true;                                                                                    \
}

COWL_ONTOLOGY_ENTITY_QUERY_IMPL(CowlClass, class, classes)
COWL_ONTOLOGY_ENTITY_QUERY_IMPL(CowlDatatype, datatype, datatypes)
COWL_ONTOLOGY_ENTITY_QUERY_IMPL(CowlObjProp, obj_prop, obj_props)
COWL_ONTOLOGY_ENTITY_QUERY_IMPL(CowlDataProp, data_prop, data_props)
COWL_ONTOLOGY_ENTITY_QUERY_IMPL(CowlAnnotProp, annot_prop, annot_props)
COWL_ONTOLOGY_ENTITY_QUERY_IMPL(CowlNamedInd, named_ind, named_inds)
COWL_ONTOLOGY_ENTITY_QUERY_IMPL(CowlAnonInd, anon_ind, anon_inds)

bool cowl_ontology_has_entity(CowlOntology *onto, CowlEntity *entity) {
    UHash(CowlObjectTable) *table = NULL;

    switch (cowl_entity_get_type(entity)) {
        case COWL_ET_CLASS: table = &onto->class_refs; break;
        case COWL_ET_DATATYPE: table = &onto->datatype_refs; break;
        case COWL_ET_NAMED_IND: table = &onto->named_ind_refs; break;
        case COWL_ET_OBJ_PROP: table = &onto->obj_prop_refs; break;
        case COWL_ET_DATA_PROP: table = &onto->data_prop_refs; break;
        case COWL_ET_ANNOT_PROP: table = &onto->annot_prop_refs; break;
        default: break;
    }

    return table && uhash_contains(CowlObjectTable, table, entity);
}

bool cowl_ontology_iterate_primitives(CowlOntology *onto, CowlPrimitiveFlags flags,
                                      CowlIterator *iter) {
    if (uflags_is_set(COWL_PF, flags, COWL_PF_CLASS)) {
        uhash_foreach(CowlObjectTable, &onto->class_refs, cls) {
            if (!cowl_class_iterate_primitives(*cls.key, flags, iter)) return false;
        }
    }

    if (uflags_is_set(COWL_PF, flags, COWL_PF_DATATYPE)) {
        uhash_foreach(CowlObjectTable, &onto->datatype_refs, dt) {
            if (!cowl_datatype_iterate_primitives(*dt.key, flags, iter)) return false;
        }
    }

    if (uflags_is_set(COWL_PF, flags, COWL_PF_OBJ_PROP)) {
        uhash_foreach(CowlObjectTable, &onto->obj_prop_refs, prop) {
            if (!cowl_obj_prop_iterate_primitives(*prop.key, flags, iter)) return false;
        }
    }

    if (uflags_is_set(COWL_PF, flags, COWL_PF_DATA_PROP)) {
        uhash_foreach(CowlObjectTable, &onto->data_prop_refs, prop) {
            if (!cowl_data_prop_iterate_primitives(*prop.key, flags, iter)) return false;
        }
    }

    if (uflags_is_set(COWL_PF, flags, COWL_PF_ANNOT_PROP)) {
        uhash_foreach(CowlObjectTable, &onto->annot_prop_refs, prop) {
            if (!cowl_annot_prop_iterate_primitives(*prop.key, flags, iter)) return false;
        }
    }

    if (uflags_is_set(COWL_PF, flags, COWL_PF_NAMED_IND)) {
        uhash_foreach(CowlObjectTable, &onto->named_ind_refs, ind) {
            if (!cowl_named_ind_iterate_primitives(*ind.key, flags, iter)) return false;
        }
    }

    if (uflags_is_set(COWL_PF, flags, COWL_PF_ANON_IND)) {
        uhash_foreach(CowlObjectTable, &onto->anon_ind_refs, ind) {
            if (!cowl_anon_ind_iterate_primitives(*ind.key, flags, iter)) return false;
        }
    }

    return true;
}

bool cowl_ontology_iterate_imports(CowlOntology *onto, CowlIterator *iter) {
    uvec_foreach(CowlObjectPtr, &onto->imports, import) {
        if (!cowl_iterate(iter, *import.item)) return false;
    }

    uvec_foreach(CowlObjectPtr, &onto->imports, import) {
        if (!cowl_ontology_iterate_imports(*import.item, iter)) return false;
    }

    return true;
}

bool cowl_ontology_iterate_axioms(CowlOntology *onto, CowlIterator *iter) {
    for (CowlAxiomType type = COWL_AT_FIRST; type < COWL_AT_COUNT; ++type) {
        UVec(CowlObjectPtr) *axioms = &onto->axioms_by_type[type];
        uvec_foreach(CowlObjectPtr, axioms, axiom) {
            if (!cowl_iterate(iter, *axiom.item)) return false;
        }
    }

    uvec_foreach(CowlObjectPtr, &onto->imports, import) {
        if (!cowl_ontology_iterate_axioms(*import.item, iter)) {
            return false;
        }
    }

    return true;
}

bool cowl_ontology_iterate_axioms_of_type(CowlOntology *onto, CowlAxiomType type,
                                          CowlIterator *iter) {
    UVec(CowlObjectPtr) *axioms = &onto->axioms_by_type[type];

    uvec_foreach(CowlObjectPtr, axioms, axiom) {
        if (!cowl_iterate(iter, *axiom.item)) return false;
    }

    uvec_foreach(CowlObjectPtr, &onto->imports, import) {
        if (!cowl_ontology_iterate_axioms_of_type(*import.item, type, iter)) {
            return false;
        }
    }

    return true;
}

bool cowl_ontology_iterate_sub_classes(CowlOntology *onto, CowlClass *owl_class,
                                       CowlIterator *iter) {
    UHash(CowlObjectTable) *map = &onto->class_refs;
    UVec(CowlObjectPtr) *axioms = uhmap_get(CowlObjectTable, map, owl_class, NULL);

    uvec_foreach(CowlObjectPtr, axioms, axiom) {
        if (cowl_axiom_get_type(*axiom.item) != COWL_AT_SUB_CLASS) continue;
        CowlSubClsAxiom *sub_axiom = *axiom.item;

        if (cowl_cls_exp_equals((CowlClsExp *)owl_class, sub_axiom->super_class)) {
            if (!cowl_iterate(iter, sub_axiom->sub_class)) return false;
        }
    }

    uvec_foreach(CowlObjectPtr, &onto->imports, import) {
        if (!cowl_ontology_iterate_sub_classes(*import.item, owl_class, iter)) {
            return false;
        }
    }

    return true;
}

bool cowl_ontology_iterate_super_classes(CowlOntology *onto, CowlClass *owl_class,
                                         CowlIterator *iter) {
    UHash(CowlObjectTable) *map = &onto->class_refs;
    UVec(CowlObjectPtr) *axioms = uhmap_get(CowlObjectTable, map, owl_class, NULL);

    uvec_foreach(CowlObjectPtr, axioms, axiom) {
        if (cowl_axiom_get_type(*axiom.item) != COWL_AT_SUB_CLASS) continue;
        CowlSubClsAxiom *sub_axiom = *axiom.item;

        if (cowl_cls_exp_equals((CowlClsExp *)owl_class, sub_axiom->sub_class)) {
            if (!cowl_iterate(iter, sub_axiom->super_class)) return false;
        }
    }

    uvec_foreach(CowlObjectPtr, &onto->imports, import) {
        if (!cowl_ontology_iterate_super_classes(*import.item, owl_class, iter)) {
            return false;
        }
    }

    return true;
}

bool cowl_ontology_iterate_eq_classes(CowlOntology *onto, CowlClass *owl_class,
                                      CowlIterator *iter) {
    UHash(CowlObjectTable) *map = &onto->class_refs;
    UVec(CowlObjectPtr) *axioms = uhmap_get(CowlObjectTable, map, owl_class, NULL);

    uvec_foreach(CowlObjectPtr, axioms, axiom) {
        if (cowl_axiom_get_type(*axiom.item) != COWL_AT_EQUIV_CLASSES) continue;
        CowlObjectVec *eq_classes = ((CowlNAryClsAxiom *)*axiom.item)->classes;

        if (uvec_contains(CowlObjectPtr, eq_classes, owl_class)) {
            uvec_foreach(CowlObjectPtr, eq_classes, ce) {
                void *cls_exp = *ce.item;
                if (cls_exp != owl_class && !cowl_iterate(iter, cls_exp)) return false;
            }
        }
    }

    uvec_foreach(CowlObjectPtr, &onto->imports, import) {
        if (!cowl_ontology_iterate_eq_classes(*import.item, owl_class, iter)) {
            return false;
        }
    }

    return true;
}

bool cowl_ontology_iterate_types(CowlOntology *onto, CowlIndividual *ind, CowlIterator *iter) {
    UVec(CowlObjectPtr) *axioms;

    if (cowl_individual_is_named(ind)) {
        UHash(CowlObjectTable) *map = &onto->named_ind_refs;
        axioms = uhmap_get(CowlObjectTable, map, ind, NULL);
    } else {
        UHash(CowlObjectTable) *map = &onto->anon_ind_refs;
        axioms = uhmap_get(CowlObjectTable, map, ind, NULL);
    }

    uvec_foreach(CowlObjectPtr, axioms, axiom) {
        if (cowl_axiom_get_type(*axiom.item) != COWL_AT_CLASS_ASSERT) continue;
        CowlClsAssertAxiom *assert_axiom = *axiom.item;
        if (!cowl_iterate(iter, assert_axiom->cls_exp)) return false;
    }

    uvec_foreach(CowlObjectPtr, &onto->imports, import) {
        if (!cowl_ontology_iterate_types(*import.item, ind, iter)) return false;
    }

    return true;
}

// Private API

CowlOntology* cowl_ontology_get(void) {
    return cowl_ontology_alloc();
}

CowlOntology* cowl_ontology_alloc(void) {
    CowlOntology *onto = ulib_alloc(onto);
    if (onto) {
        *onto = (CowlOntology) {
            .super = COWL_OBJECT_INIT(COWL_OT_ONTOLOGY),
            .imports = uvec_init(CowlObjectPtr),
            .annotations = uvec_init(CowlObjectPtr),
            .annot_prop_refs = cowl_annot_prop_map_init(),
            .class_refs = cowl_class_map_init(),
            .data_prop_refs = cowl_data_prop_map_init(),
            .datatype_refs = cowl_datatype_map_init(),
            .obj_prop_refs = cowl_obj_prop_map_init(),
            .named_ind_refs = cowl_named_ind_map_init(),
            .anon_ind_refs = cowl_anon_ind_map_init()
        };

        for (CowlAxiomType t = COWL_AT_FIRST; t < COWL_AT_COUNT; ++t) {
            onto->axioms_by_type[t] = uvec_init(CowlObjectPtr);
        }
    }
    return onto;
}

void cowl_ontology_free(CowlOntology *onto) {
    cowl_iri_release(onto->id.ontology_iri);
    cowl_iri_release(onto->id.version_iri);

    cowl_object_vec_deinit_spec(ontology, &onto->imports);
    cowl_object_vec_deinit_spec(annotation, &onto->annotations);

    for (CowlAxiomType type = COWL_AT_FIRST; type < COWL_AT_COUNT; type++) {
        cowl_object_vec_deinit(&onto->axioms_by_type[type]);
    }

    UHash(CowlObjectTable) *tables[] = {
        &onto->annot_prop_refs, &onto->class_refs, &onto->data_prop_refs,
        &onto->datatype_refs, &onto->obj_prop_refs, &onto->named_ind_refs, &onto->anon_ind_refs
    };

    for (ulib_uint i = 0; i < ulib_array_count(tables); ++i) {
        uhash_foreach(CowlObjectTable, tables[i], vec) { uvec_free(CowlObjectPtr, *vec.val); }
        uhash_deinit(CowlObjectTable, tables[i]);
    }

    ulib_free(onto);
}

void cowl_ontology_set_iri(CowlOntology *onto, CowlIRI *iri) {
    cowl_iri_release(onto->id.ontology_iri);
    onto->id.ontology_iri = cowl_iri_retain(iri);
}

void cowl_ontology_set_version(CowlOntology *onto, CowlIRI *version) {
    cowl_iri_release(onto->id.version_iri);
    onto->id.version_iri = cowl_iri_retain(version);
}

cowl_ret cowl_ontology_add_annot(CowlOntology *onto, CowlAnnotation *annot) {
    if (uvec_push(CowlObjectPtr, &onto->annotations, annot) != UVEC_OK) return COWL_ERR_MEM;
    cowl_annotation_retain(annot);

    CowlAxiomCtx ctx = { .onto = onto };
    CowlIterator iter = cowl_iterator_init(&ctx, cowl_ontology_primitive_adder);
    cowl_annotation_iterate_primitives(annot, COWL_PF_ALL, &iter);
    return ctx.ret;
}

cowl_ret cowl_ontology_add_import(CowlOntology *onto, CowlOntology *import) {
    if (uvec_push(CowlObjectPtr, &onto->imports, import) != UVEC_OK) return COWL_ERR_MEM;
    cowl_ontology_retain(import);

    CowlAxiomCtx ctx = { .onto = onto };
    CowlIterator iter = cowl_iterator_init(&ctx, cowl_ontology_primitive_adder);
    cowl_ontology_iterate_primitives(import, COWL_PF_ALL, &iter);
    return ctx.ret;
}

cowl_ret cowl_ontology_add_primitive(CowlOntology *onto, CowlObject *obj) {
    switch (cowl_object_get_type(obj)) {
        case COWL_OT_CE_CLASS: return cowl_ontology_add_primitive_to_map(obj, &onto->class_refs);
        case COWL_OT_DPE_DATA_PROP: return cowl_ontology_add_primitive_to_map(obj, &onto->data_prop_refs);
        case COWL_OT_DR_DATATYPE: return cowl_ontology_add_primitive_to_map(obj, &onto->datatype_refs);
        case COWL_OT_OPE_OBJ_PROP: return cowl_ontology_add_primitive_to_map(obj, &onto->obj_prop_refs);
        case COWL_OT_ANNOT_PROP: return cowl_ontology_add_primitive_to_map(obj, &onto->annot_prop_refs);
        case COWL_OT_I_NAMED: return cowl_ontology_add_primitive_to_map(obj, &onto->named_ind_refs);
        case COWL_OT_I_ANONYMOUS: return cowl_ontology_add_primitive_to_map(obj, &onto->anon_ind_refs);
        default: return COWL_ERR;
    }
}

cowl_ret cowl_ontology_add_axiom(CowlOntology *onto, CowlAxiom *axiom) {
    CowlAxiomType type = cowl_axiom_get_type(axiom);
    UVec(CowlObjectPtr) *axioms = &onto->axioms_by_type[type];
    if (uvec_push(CowlObjectPtr, axioms, axiom)) return COWL_ERR_MEM;

    cowl_axiom_retain(axiom);
    CowlAxiomCtx ctx = { .onto = onto, .axiom = axiom };
    CowlIterator iter = cowl_iterator_init(&ctx, cowl_ontology_primitive_axiom_adder);
    if (!cowl_axiom_iterate_primitives(axiom, COWL_PF_ALL, &iter) && ctx.ret) return COWL_ERR_MEM;

    return COWL_OK;
}

cowl_ret cowl_ontology_add_axiom_for_primitive(CowlOntology *onto, CowlAxiom *axiom,
                                               CowlObject *obj) {
    switch (cowl_object_get_type(obj)) {

        case COWL_OT_CE_CLASS:
            return cowl_ontology_add_axiom_to_map(obj, axiom, &onto->class_refs);

        case COWL_OT_DPE_DATA_PROP:
            return cowl_ontology_add_axiom_to_map(obj, axiom, &onto->data_prop_refs);

        case COWL_OT_DR_DATATYPE:
            return cowl_ontology_add_axiom_to_map(obj, axiom, &onto->datatype_refs);

        case COWL_OT_OPE_OBJ_PROP:
            return cowl_ontology_add_axiom_to_map(obj, axiom, &onto->obj_prop_refs);

        case COWL_OT_ANNOT_PROP:
            return cowl_ontology_add_axiom_to_map(obj, axiom, &onto->annot_prop_refs);

        case COWL_OT_I_NAMED:
            return cowl_ontology_add_axiom_to_map(obj, axiom, &onto->named_ind_refs);

        case COWL_OT_I_ANONYMOUS:
            return cowl_ontology_add_axiom_to_map(obj, axiom, &onto->anon_ind_refs);

        default:
            return COWL_ERR;
    }
}

// Iterator functions

bool cowl_ontology_primitive_axiom_adder(void *ctx, void *obj) {
    CowlAxiomCtx *axiom_ctx = ctx;
    cowl_ret ret = cowl_ontology_add_axiom_for_primitive(axiom_ctx->onto, axiom_ctx->axiom, obj);
    axiom_ctx->ret = ret;
    return ret == COWL_OK;
}

bool cowl_ontology_primitive_adder(void *ctx, void *obj) {
    CowlAxiomCtx *axiom_ctx = ctx;
    cowl_ret ret = cowl_ontology_add_primitive(axiom_ctx->onto, obj);
    axiom_ctx->ret = ret;
    return ret == COWL_OK;
}
