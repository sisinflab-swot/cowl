/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2022 SisInf Lab, Polytechnic University of Bari
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

static inline cowl_ret cowl_vector_ptr_add(CowlVector **vec, void *obj) {
    if (!(*vec || (*vec = cowl_vector_ordered_empty()))) return COWL_ERR_MEM;
    return cowl_vector_add(*vec, obj) ? COWL_ERR_MEM : COWL_OK;
}

void cowl_ontology_release(CowlOntology *onto) {
    if (!onto || cowl_object_decr_ref(onto)) return;

    cowl_iri_release(onto->id.iri);
    cowl_iri_release(onto->id.version);

    cowl_vector_release(onto->annotations);
    cowl_vector_release(onto->imports);

    for (CowlAxiomType type = COWL_AT_FIRST; type < COWL_AT_COUNT; type++) {
        cowl_vector_release(onto->axioms_by_type[type]);
    }

    for (ulib_uint i = 0; i < ulib_array_count(onto->refs); ++i) {
        uhash_foreach(CowlObjectTable, &onto->refs[i], vec) {
            cowl_vector_release_ex(*vec.val, false);
        }
        uhash_deinit(CowlObjectTable, &onto->refs[i]);
    }

    ulib_free(onto);
}

CowlOntologyId cowl_ontology_get_id(CowlOntology *onto) {
    return onto->id;
}

CowlVector* cowl_ontology_get_annot(CowlOntology *onto) {
    return onto->annotations;
}

bool cowl_ontology_equals(CowlOntology *lhs, CowlOntology *rhs) {
    if (lhs == rhs) return true;

    // If the ontology IRIs are both NULL, then both ontologies are anonymous.
    // If they were equal, they would have passed the pointer equality check.
    if (!(lhs->id.iri || rhs->id.iri)) return false;

    return cowl_ontology_id_equals(lhs->id, rhs->id);
}

ulib_uint cowl_ontology_hash(CowlOntology *onto) {
    return cowl_ontology_id_hash(onto->id);
}

ulib_uint cowl_ontology_axiom_count(CowlOntology *onto, bool imports) {
    ulib_uint count = 0;

    for (CowlAxiomType type = COWL_AT_FIRST; type < COWL_AT_COUNT; ++type) {
        count += cowl_vector_count(onto->axioms_by_type[type]);
    }

    if (imports) {
        cowl_vector_foreach(onto->imports, import) {
            count += cowl_ontology_axiom_count(*import.item, true);
        }
    }

    return count;
}

ulib_uint cowl_ontology_imports_count(CowlOntology *onto, bool imports) {
    ulib_uint count = cowl_vector_count(onto->imports);

    if (imports) {
        cowl_vector_foreach(onto->imports, import) {
            count += cowl_ontology_imports_count(*import.item, true);
        }
    }

    return count;
}

ulib_uint cowl_ontology_axiom_count_for_type(CowlOntology *onto, CowlAxiomType type, bool imports) {
    ulib_uint count = cowl_vector_count(onto->axioms_by_type[type]);

    if (imports) {
        cowl_vector_foreach(onto->imports, import) {
            count += cowl_ontology_axiom_count_for_type(*import.item, type, true);
        }
    }

    return count;
}

ulib_uint cowl_ontology_axiom_count_for_primitive(CowlOntology *onto, void *primitive,
                                                  bool imports) {
    UHash(CowlObjectTable) *table = &onto->refs[cowl_primitive_get_type(primitive)];
    ulib_uint count = cowl_vector_count(uhmap_get(CowlObjectTable, table, primitive, NULL));

    if (imports) {
        cowl_vector_foreach(onto->imports, import) {
            count += cowl_ontology_axiom_count_for_primitive(*import.item, primitive, true);
        }
    }

    return count;
}

ulib_uint cowl_ontology_primitives_count(CowlOntology *onto, CowlPrimitiveFlags flags,
                                         bool imports) {
    ulib_uint count = 0;

    for (CowlPrimitiveType i = COWL_PT_FIRST; i < COWL_PT_COUNT; ++i) {
        if (cowl_primitive_flags_has_type(flags, i)) {
            count += uhash_count(CowlObjectTable, &onto->refs[i]);
        }
    }

    if (imports) {
        cowl_vector_foreach(onto->imports, import) {
            count += cowl_ontology_primitives_count(*import.item, flags, true);
        }
    }

    return count;
}

bool cowl_ontology_has_primitive(CowlOntology *onto, void *primitive, bool imports) {
    UHash(CowlObjectTable) *refs = &onto->refs[cowl_primitive_get_type(primitive)];
    if (uhash_contains(CowlObjectTable, refs, primitive)) return true;

    if (imports) {
        cowl_vector_foreach(onto->imports, import) {
            if (cowl_ontology_has_primitive(*import.item, primitive, true)) return true;
        }
    }

    return false;
}

bool cowl_ontology_iterate_primitives(CowlOntology *onto, CowlPrimitiveFlags flags,
                                      CowlIterator *iter, bool imports) {
    for (CowlPrimitiveType i = COWL_PT_FIRST; i < COWL_PT_COUNT; ++i) {
        if (!cowl_primitive_flags_has_type(flags, i)) continue;
        uhash_foreach(CowlObjectTable, &onto->refs[i], p) {
            if (!cowl_class_iterate_primitives(*p.key, flags, iter)) return false;
        }
    }

    if (imports) {
        cowl_vector_foreach(onto->imports, import) {
            if (!cowl_ontology_iterate_primitives(*import.item, flags, iter, true)) return false;
        }
    }

    return true;
}

bool cowl_ontology_iterate_imports(CowlOntology *onto, CowlIterator *iter, bool imports) {
    cowl_vector_foreach(onto->imports, import) {
        if (!cowl_iterate(iter, *import.item)) return false;
    }

    if (imports) {
        cowl_vector_foreach(onto->imports, import) {
            if (!cowl_ontology_iterate_imports(*import.item, iter, true)) return false;
        }
    }

    return true;
}

bool cowl_ontology_iterate_axioms(CowlOntology *onto, CowlIterator *iter, bool imports) {
    for (CowlAxiomType type = COWL_AT_FIRST; type < COWL_AT_COUNT; ++type) {
        cowl_vector_foreach(onto->axioms_by_type[type], axiom) {
            if (!cowl_iterate(iter, *axiom.item)) return false;
        }
    }

    if (imports) {
        cowl_vector_foreach(onto->imports, import) {
            if (!cowl_ontology_iterate_axioms(*import.item, iter, true)) {
                return false;
            }
        }
    }

    return true;
}

bool cowl_ontology_iterate_axioms_of_type(CowlOntology *onto, CowlAxiomType type,
                                          CowlIterator *iter, bool imports) {
    cowl_vector_foreach(onto->axioms_by_type[type], axiom) {
        if (!cowl_iterate(iter, *axiom.item)) return false;
    }

    if (imports) {
        cowl_vector_foreach(onto->imports, import) {
            if (!cowl_ontology_iterate_axioms_of_type(*import.item, type, iter, true)) {
                return false;
            }
        }
    }

    return true;
}

bool cowl_ontology_iterate_axioms_for_primitive(CowlOntology *onto, void *primitive,
                                                CowlIterator *iter, bool imports) {
    UHash(CowlObjectTable) *table = &onto->refs[cowl_primitive_get_type(primitive)];

    cowl_vector_foreach(uhmap_get(CowlObjectTable, table, primitive, NULL), a) {
        if (!cowl_iterate(iter, *a.item)) return false;
    }

    if (imports) {
        cowl_vector_foreach(onto->imports, import) {
            if (!cowl_ontology_iterate_axioms_for_primitive(*import.item, primitive, iter, true)) {
                return false;
            }
        }
    }
    return true;
}

bool cowl_ontology_iterate_sub_classes(CowlOntology *onto, CowlClass *owl_class,
                                       CowlIterator *iter, bool imports) {
    CowlVector *axioms = uhmap_get(CowlObjectTable, &onto->refs[COWL_PT_CLASS], owl_class, NULL);

    cowl_vector_foreach(axioms, axiom) {
        if (cowl_axiom_get_type(*axiom.item) != COWL_AT_SUB_CLASS) continue;
        CowlSubClsAxiom *sub_axiom = *axiom.item;

        if (cowl_cls_exp_equals((CowlClsExp *)owl_class, cowl_sub_cls_axiom_get_super(sub_axiom))) {
            if (!cowl_iterate(iter, cowl_sub_cls_axiom_get_sub(sub_axiom))) return false;
        }
    }

    if (imports) {
        cowl_vector_foreach(onto->imports, import) {
            if (!cowl_ontology_iterate_sub_classes(*import.item, owl_class, iter, true)) {
                return false;
            }
        }
    }

    return true;
}

bool cowl_ontology_iterate_super_classes(CowlOntology *onto, CowlClass *owl_class,
                                         CowlIterator *iter, bool imports) {
    CowlVector *axioms = uhmap_get(CowlObjectTable, &onto->refs[COWL_PT_CLASS], owl_class, NULL);

    cowl_vector_foreach(axioms, axiom) {
        if (cowl_axiom_get_type(*axiom.item) != COWL_AT_SUB_CLASS) continue;
        CowlSubClsAxiom *sub_axiom = *axiom.item;

        if (cowl_cls_exp_equals((CowlClsExp *)owl_class, cowl_sub_cls_axiom_get_sub(sub_axiom))) {
            if (!cowl_iterate(iter, cowl_sub_cls_axiom_get_super(sub_axiom))) return false;
        }
    }

    if (imports) {
        cowl_vector_foreach(onto->imports, import) {
            if (!cowl_ontology_iterate_super_classes(*import.item, owl_class, iter, true)) {
                return false;
            }
        }
    }

    return true;
}

bool cowl_ontology_iterate_eq_classes(CowlOntology *onto, CowlClass *owl_class,
                                      CowlIterator *iter, bool imports) {
    CowlVector *axioms = uhmap_get(CowlObjectTable, &onto->refs[COWL_PT_CLASS], owl_class, NULL);

    cowl_vector_foreach(axioms, axiom) {
        if (cowl_axiom_get_type(*axiom.item) != COWL_AT_EQUIV_CLASSES) continue;
        CowlVector *eq_classes = cowl_nary_cls_axiom_get_classes((CowlNAryClsAxiom *)*axiom.item);

        if (uvec_contains(CowlObjectPtr, &eq_classes->data, owl_class)) {
            uvec_foreach(CowlObjectPtr, &eq_classes->data, ce) {
                void *cls_exp = *ce.item;
                if (cls_exp != owl_class && !cowl_iterate(iter, cls_exp)) return false;
            }
        }
    }

    if (imports) {
        cowl_vector_foreach(onto->imports, import) {
            if (!cowl_ontology_iterate_eq_classes(*import.item, owl_class, iter, true)) {
                return false;
            }
        }
    }

    return true;
}

bool cowl_ontology_iterate_types(CowlOntology *onto, CowlIndividual *ind, CowlIterator *iter,
                                 bool imports) {
    CowlVector *axioms;

    if (cowl_individual_is_named(ind)) {
        axioms = uhmap_get(CowlObjectTable, &onto->refs[COWL_PT_NAMED_IND], ind, NULL);
    } else {
        axioms = uhmap_get(CowlObjectTable, &onto->refs[COWL_PT_ANON_IND], ind, NULL);
    }

    cowl_vector_foreach(axioms, axiom) {
        if (cowl_axiom_get_type(*axiom.item) != COWL_AT_CLASS_ASSERT) continue;
        CowlClsAssertAxiom *assert_axiom = *axiom.item;
        if (!cowl_iterate(iter, cowl_cls_assert_axiom_get_cls_exp(assert_axiom))) return false;
    }

    if (imports) {
        cowl_vector_foreach(onto->imports, import) {
            if (!cowl_ontology_iterate_types(*import.item, ind, iter, true)) return false;
        }
    }

    return true;
}

CowlOntology* cowl_ontology(void) {
    CowlOntology *onto = ulib_alloc(onto);
    if (!onto) return NULL;

    *onto = (CowlOntology){0};
    onto->super = COWL_OBJECT_INIT(COWL_OT_ONTOLOGY);

    for (CowlPrimitiveType i = COWL_PT_FIRST; i < COWL_PT_COUNT; ++i) {
        onto->refs[i] = cowl_primitive_map();
    }

    return onto;
}

void cowl_ontology_set_iri(CowlOntology *onto, CowlIRI *iri) {
    cowl_iri_release(onto->id.iri);
    onto->id.iri = cowl_iri_retain(iri);
}

void cowl_ontology_set_version(CowlOntology *onto, CowlIRI *version) {
    cowl_iri_release(onto->id.version);
    onto->id.version = cowl_iri_retain(version);
}

static cowl_ret cowl_add_primitive_to_map(CowlObject *primitive, UHash(CowlObjectTable) *map) {
    ulib_uint idx;
    uhash_ret ret = uhash_put(CowlObjectTable, map, primitive, &idx);
    if (ret == UHASH_ERR) return COWL_ERR_MEM;

    if (ret == UHASH_INSERTED) {
        uhash_value(CowlObjectTable, map, idx) = NULL;
    }

    return COWL_OK;
}

static bool cowl_ontology_primitive_adder(void *ctx, void *obj) {
    CowlAxiomCtx *axiom_ctx = ctx;
    CowlPrimitiveType type = cowl_primitive_get_type(obj);
    cowl_ret ret = cowl_add_primitive_to_map(obj, &axiom_ctx->onto->refs[type]);
    axiom_ctx->ret = ret;
    return ret == COWL_OK;
}

cowl_ret cowl_ontology_add_annot(CowlOntology *onto, CowlAnnotation *annot) {
    if (cowl_vector_ptr_add(&onto->annotations, annot)) return COWL_ERR_MEM;
    CowlAxiomCtx ctx = { .onto = onto };
    CowlIterator iter = cowl_iterator(&ctx, cowl_ontology_primitive_adder);
    cowl_annotation_iterate_primitives(annot, COWL_PF_ALL, &iter);
    return ctx.ret;
}

void cowl_ontology_remove_annot(CowlOntology *onto, CowlAnnotation *annot) {
    if (onto->annotations) cowl_vector_remove(onto->annotations, annot);
}

cowl_ret cowl_ontology_add_import(CowlOntology *onto, CowlOntology *import) {
    return cowl_vector_ptr_add(&onto->imports, import);
}

void cowl_ontology_remove_import(CowlOntology *onto, CowlOntology *import) {
    if (onto->imports) cowl_vector_remove(onto->imports, import);
}

static cowl_ret cowl_add_axiom_to_map(CowlObject *primitive, CowlAxiom *axiom,
                                      UHash(CowlObjectTable) *map) {
    ulib_uint idx;
    uhash_ret ret = uhash_put(CowlObjectTable, map, primitive, &idx);
    if (ret == UHASH_ERR) return COWL_ERR_MEM;

    CowlVector *vec = uhash_value(CowlObjectTable, map, idx);

    if (ret == UHASH_INSERTED || !vec) {
        vec = cowl_vector_ordered_empty();
        uhash_value(CowlObjectTable, map, idx) = vec;
        if (!vec) return COWL_ERR_MEM;
    }

    if (cowl_vector_push(vec, axiom)) {
        return COWL_ERR_MEM;
    }

    return COWL_OK;
}

static void cowl_remove_axiom_from_map(CowlObject *primitive, CowlAxiom *axiom,
                                           UHash(CowlObjectTable) *map) {
    CowlVector *vec = uhmap_get(CowlObjectTable, map, primitive, NULL);
    if (vec) uvec_remove(CowlObjectPtr, &vec->data, axiom);
}

static bool cowl_ontology_primitive_axiom_adder(void *ctx, void *obj) {
    CowlAxiomCtx *axiom_ctx = ctx;
    CowlPrimitiveType type = cowl_primitive_get_type(obj);
    cowl_ret ret = cowl_add_axiom_to_map(obj, axiom_ctx->axiom, &axiom_ctx->onto->refs[type]);
    axiom_ctx->ret = ret;
    return ret == COWL_OK;
}

static bool cowl_ontology_primitive_axiom_remover(void *ctx, void *obj) {
    CowlAxiomCtx *axiom_ctx = ctx;
    CowlPrimitiveType type = cowl_primitive_get_type(obj);
    cowl_remove_axiom_from_map(obj, axiom_ctx->axiom, &axiom_ctx->onto->refs[type]);
    axiom_ctx->ret = COWL_OK;
    return true;
}

cowl_ret cowl_ontology_add_axiom(CowlOntology *onto, CowlAxiom *axiom) {
    CowlAxiomType type = cowl_axiom_get_type(axiom);
    if (cowl_vector_ptr_add(&onto->axioms_by_type[type], axiom)) return COWL_ERR_MEM;

    CowlAxiomCtx ctx = { .onto = onto, .axiom = axiom };
    CowlIterator iter = cowl_iterator(&ctx, cowl_ontology_primitive_axiom_adder);
    if (!cowl_axiom_iterate_primitives(axiom, COWL_PF_ALL, &iter) && ctx.ret) return ctx.ret;

    return COWL_OK;
}

void cowl_ontology_remove_axiom(CowlOntology *onto, CowlAxiom *axiom) {
    CowlAxiomType type = cowl_axiom_get_type(axiom);
    if (!onto->axioms_by_type[type]) return;

    UVec(CowlObjectPtr) *vec = &onto->axioms_by_type[type]->data;
    if (!uvec_remove(CowlObjectPtr, vec, axiom)) return;

    CowlAxiomCtx ctx = { .onto = onto, .axiom = axiom };
    CowlIterator iter = cowl_iterator(&ctx, cowl_ontology_primitive_axiom_remover);
    cowl_axiom_iterate_primitives(axiom, COWL_PF_ALL, &iter);

    cowl_release(axiom);
    return;
}

cowl_ret cowl_ontology_finalize(CowlOntology *onto) {
    if (cowl_vector_shrink(onto->imports)) return COWL_ERR_MEM;
    if (cowl_vector_shrink(onto->annotations)) return COWL_ERR_MEM;

    for (CowlAxiomType i = COWL_AT_FIRST; i < COWL_AT_COUNT; ++i) {
        if (cowl_vector_shrink(onto->axioms_by_type[i])) return COWL_ERR_MEM;
    }

    for (CowlPrimitiveType i = COWL_PT_FIRST; i < COWL_PT_COUNT; ++i) {
        uhash_foreach(CowlObjectTable, &onto->refs[i], item) {
            if (cowl_vector_shrink(*item.val)) return COWL_ERR_MEM;
        }
    }

    return COWL_OK;
}
