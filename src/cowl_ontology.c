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

#define cowl_ontology_foreach_import(ONTO, IMPORT, CODE) do {                                       \
    cowl_table_foreach((ONTO)->imports, p_##IMPORT##_var) {                                         \
        if (!*p_##IMPORT##_var.val) continue;                                                       \
        CowlOntology *IMPORT = *p_##IMPORT##_var.val;                                               \
        CODE;                                                                                       \
    }                                                                                               \
} while (0)

typedef struct CowlAxiomCtx {
    cowl_ret ret;
    CowlOntology *onto;
    CowlAxiom *axiom;
} CowlAxiomCtx;

static inline cowl_ret cowl_vector_ptr_add(CowlVector **vec, CowlAny *obj) {
    if (!(*vec || (*vec = cowl_vector_ordered_empty()))) return COWL_ERR_MEM;
    return cowl_vector_add(*vec, obj) ? COWL_ERR_MEM : COWL_OK;
}

CowlOntology* cowl_ontology(CowlManager *manager) {
    CowlOntology *onto = ulib_alloc(onto);
    if (!onto) return NULL;

    *onto = (CowlOntology){0};
    onto->super = COWL_OBJECT_INIT(COWL_OT_ONTOLOGY);
    onto->st = cowl_sym_table_init();
    onto->manager = cowl_manager_retain(manager);

    for (CowlPrimitiveType i = COWL_PT_FIRST; i < COWL_PT_COUNT; ++i) {
        onto->refs[i] = cowl_primitive_map();
    }

    return onto;
}

void cowl_ontology_release(CowlOntology *onto) {
    if (!onto || cowl_object_decr_ref(onto)) return;

    cowl_manager_remove_ontology(onto->manager, onto);
    cowl_manager_release(onto->manager);

    cowl_sym_table_deinit(&onto->st);
    cowl_iri_release(onto->id.iri);
    cowl_iri_release(onto->id.version);

    cowl_table_release(onto->imports);
    cowl_vector_release(onto->annotations);

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

CowlManager* cowl_ontology_get_manager(CowlOntology *onto) {
     return onto->manager;
}

CowlSymTable* cowl_ontology_get_sym_table(CowlOntology *onto) {
    return &onto->st;
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
        cowl_ontology_foreach_import(onto, import, {
            count += cowl_ontology_axiom_count(import, true);
        });
    }

    return count;
}

ulib_uint cowl_ontology_imports_count(CowlOntology *onto, bool imports) {
    ulib_uint count = cowl_table_count(onto->imports);

    if (imports) {
        cowl_ontology_foreach_import(onto, import, {
            count += cowl_ontology_imports_count(import, true);
        });
    }

    return count;
}

ulib_uint cowl_ontology_axiom_count_for_type(CowlOntology *onto, CowlAxiomType type, bool imports) {
    ulib_uint count = cowl_vector_count(onto->axioms_by_type[type]);

    if (imports) {
        cowl_ontology_foreach_import(onto, import, {
            count += cowl_ontology_axiom_count_for_type(import, type, true);
        });
    }

    return count;
}

ulib_uint cowl_ontology_axiom_count_for_primitive(CowlOntology *onto, CowlAnyPrimitive *primitive,
                                                  bool imports) {
    UHash(CowlObjectTable) *table = &onto->refs[cowl_primitive_get_type(primitive)];
    ulib_uint count = cowl_vector_count(uhmap_get(CowlObjectTable, table, primitive, NULL));

    if (imports) {
        cowl_ontology_foreach_import(onto, import, {
            count += cowl_ontology_axiom_count_for_primitive(import, primitive, true);
        });
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
        cowl_ontology_foreach_import(onto, import, {
            count += cowl_ontology_primitives_count(import, flags, true);
        });
    }

    return count;
}

bool cowl_ontology_has_primitive(CowlOntology *onto, CowlAnyPrimitive *primitive, bool imports) {
    UHash(CowlObjectTable) *refs = &onto->refs[cowl_primitive_get_type(primitive)];
    if (uhash_contains(CowlObjectTable, refs, primitive)) return true;

    if (imports) {
        cowl_ontology_foreach_import(onto, import, {
            if (cowl_ontology_has_primitive(import, primitive, true)) return true;
        });
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
        cowl_ontology_foreach_import(onto, import, {
            if (!cowl_ontology_iterate_primitives(import, flags, iter, true)) return false;
        });
    }

    return true;
}

bool cowl_ontology_iterate_imports(CowlOntology *onto, CowlIterator *iter, bool imports) {
    cowl_ontology_foreach_import(onto, import, {
        if (!cowl_iterate(iter, import)) return false;
    });

    if (imports) {
        cowl_ontology_foreach_import(onto, import, {
            if (!cowl_ontology_iterate_imports(import, iter, true)) return false;
        });
    }

    return true;
}

bool cowl_ontology_iterate_import_iris(CowlOntology *onto, CowlIterator *iter, bool imports) {
    cowl_table_foreach(onto->imports, import) {
        if (!cowl_iterate(iter, *import.key)) return false;
    }

    if (imports) {
        cowl_ontology_foreach_import(onto, import, {
            if (!cowl_ontology_iterate_import_iris(import, iter, true)) return false;
        });
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
        cowl_ontology_foreach_import(onto, import, {
            if (!cowl_ontology_iterate_axioms(import, iter, true)) return false;
        });
    }

    return true;
}

bool cowl_ontology_iterate_axioms_of_type(CowlOntology *onto, CowlAxiomType type,
                                          CowlIterator *iter, bool imports) {
    cowl_vector_foreach(onto->axioms_by_type[type], axiom) {
        if (!cowl_iterate(iter, *axiom.item)) return false;
    }

    if (imports) {
        cowl_ontology_foreach_import(onto, import, {
            if (!cowl_ontology_iterate_axioms_of_type(import, type, iter, true)) return false;
        });
    }

    return true;
}

bool cowl_ontology_iterate_axioms_for_primitive(CowlOntology *onto, CowlAnyPrimitive *primitive,
                                                CowlIterator *iter, bool imports) {
    UHash(CowlObjectTable) *table = &onto->refs[cowl_primitive_get_type(primitive)];

    cowl_vector_foreach(uhmap_get(CowlObjectTable, table, primitive, NULL), a) {
        if (!cowl_iterate(iter, *a.item)) return false;
    }

    if (imports) {
        cowl_ontology_foreach_import(onto, import, {
            if (!cowl_ontology_iterate_axioms_for_primitive(import, primitive, iter, true)) {
                return false;
            }
        });
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
        cowl_ontology_foreach_import(onto, import, {
            if (!cowl_ontology_iterate_sub_classes(import, owl_class, iter, true)) return false;
        });
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
        cowl_ontology_foreach_import(onto, import, {
            if (!cowl_ontology_iterate_super_classes(import, owl_class, iter, true)) return false;
        });
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
                CowlAnyClsExp *cls_exp = *ce.item;
                if (cls_exp != owl_class && !cowl_iterate(iter, cls_exp)) return false;
            }
        }
    }

    if (imports) {
        cowl_ontology_foreach_import(onto, import, {
            if (!cowl_ontology_iterate_eq_classes(import, owl_class, iter, true)) return false;
        });
    }

    return true;
}

bool cowl_ontology_iterate_types(CowlOntology *onto, CowlAnyIndividual *ind, CowlIterator *iter,
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
        cowl_ontology_foreach_import(onto, import, {
            if (!cowl_ontology_iterate_types(import, ind, iter, true)) return false;
        });
    }

    return true;
}

void cowl_ontology_set_iri(CowlOntology *onto, CowlIRI *iri) {
    cowl_iri_release(onto->id.iri);
    onto->id.iri = iri ? cowl_iri_retain(iri) : NULL;
}

void cowl_ontology_set_version(CowlOntology *onto, CowlIRI *version) {
    cowl_iri_release(onto->id.version);
    onto->id.version = version ? cowl_iri_retain(version) : NULL;
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

static bool cowl_ontology_primitive_adder(void *ctx, CowlAny *obj) {
    CowlAxiomCtx *axiom_ctx = ctx;
    UHash(CowlObjectTable) *map = &axiom_ctx->onto->refs[cowl_primitive_get_type(obj)];
    cowl_ret ret = cowl_add_primitive_to_map(obj, map);
    axiom_ctx->ret = ret;
    return ret == COWL_OK;
}

cowl_ret cowl_ontology_add_annot(CowlOntology *onto, CowlAnnotation *annot) {
    cowl_ret ret = COWL_ERR_MEM;
    if (!annot) goto end;

    CowlAxiomCtx ctx = { .onto = onto };
    CowlIterator iter = { &ctx, cowl_ontology_primitive_adder };
    cowl_annotation_iterate_primitives(annot, COWL_PF_ALL, &iter);
    if ((ret = ctx.ret)) goto end;

    ret = cowl_vector_ptr_add(&onto->annotations, annot);

end:
    if (ret) cowl_handle_error_code(ret, onto);
    return ret;
}

void cowl_ontology_remove_annot(CowlOntology *onto, CowlAnnotation *annot) {
    if (onto->annotations) cowl_vector_remove(onto->annotations, annot);
}

CowlOntology* cowl_ontology_get_import(CowlOntology *onto, CowlIRI *iri) {
    if (!onto->imports) return NULL;
    return cowl_table_get_value(onto->imports, iri);
}

CowlIRI* cowl_ontology_get_import_iri(CowlOntology *onto, CowlOntology *import) {
    if (!onto->imports) return NULL;
    cowl_table_foreach(onto->imports, e) {
        if (*e.val && cowl_ontology_equals(import, *e.val)) return *e.key;
    }
    return NULL;
}

static ulib_uint iri_hash(CowlAny *iri) { return uhash_ptr_hash(iri); }
static bool iri_eq(CowlAny *lhs, CowlAny *rhs) { return lhs == rhs; }

cowl_ret cowl_ontology_add_import(CowlOntology *onto, CowlIRI *iri) {
    ulib_uint idx = UHASH_INDEX_MISSING;
    if (!iri) goto err;

    UHash(CowlObjectTable) map = uhmap_pi(CowlObjectTable, iri_hash, iri_eq);
    if (!onto->imports && !(onto->imports = cowl_table(&map))) goto err;

    UHash(CowlObjectTable) *tbl = &onto->imports->data;
    uhash_ret hret = uhash_put(CowlObjectTable, tbl, iri, &idx);

    if (hret == UHASH_INSERTED) {
        cowl_iri_retain(iri);
    } else if (hret == UHASH_PRESENT) {
        return COWL_OK;
    } else {
        goto err;
    }

    CowlOntology *import = NULL;
    CowlImportLoader loader = onto->manager->loader;
    if (!loader.load_ontology) loader = cowl_get_import_loader();
    if (loader.load_ontology && !(import = loader.load_ontology(loader.ctx, iri))) goto err;
    uhash_value(CowlObjectTable, tbl, idx) = import;

    return COWL_OK;

err:
    if (onto->imports && idx < uhash_size(CowlObjectTable, &onto->imports->data)) {
        uhash_delete(CowlObjectTable, &onto->imports->data, idx);
    }
    cowl_handle_error_code(COWL_ERR_IMPORT, onto);
    return COWL_ERR_IMPORT;
}

void cowl_ontology_remove_import(CowlOntology *onto, CowlIRI *iri) {
    if (!onto->imports) return;

    UHash(CowlObjectTable) *tbl = &onto->imports->data;
    ulib_uint idx = uhash_get(CowlObjectTable, tbl, iri);
    if (idx == UHASH_INDEX_MISSING) return;

    uhash_delete(CowlObjectTable, tbl, idx);
    cowl_iri_release(iri);
    cowl_ontology_release(uhash_value(CowlObjectTable, tbl, idx));
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

static bool cowl_ontology_primitive_axiom_adder(void *ctx, CowlAny *obj) {
    CowlAxiomCtx *axiom_ctx = ctx;
    UHash(CowlObjectTable) *map = &axiom_ctx->onto->refs[cowl_primitive_get_type(obj)];
    cowl_ret ret = cowl_add_axiom_to_map(obj, axiom_ctx->axiom, map);
    axiom_ctx->ret = ret;
    return ret == COWL_OK;
}

static bool cowl_ontology_primitive_axiom_remover(void *ctx, void *obj) {
    CowlAxiomCtx *axiom_ctx = ctx;
    UHash(CowlObjectTable) *map = &axiom_ctx->onto->refs[cowl_primitive_get_type(obj)];
    cowl_remove_axiom_from_map(obj, axiom_ctx->axiom, map);
    axiom_ctx->ret = COWL_OK;
    return true;
}

cowl_ret cowl_ontology_add_axiom(CowlOntology *onto, CowlAnyAxiom *axiom) {
    cowl_ret ret = COWL_ERR_MEM;
    if (!axiom) goto end;

    CowlAxiomCtx ctx = { .onto = onto, .axiom = axiom };
    CowlIterator iter = { &ctx, cowl_ontology_primitive_axiom_adder };

    cowl_axiom_iterate_primitives(axiom, COWL_PF_ALL, &iter);
    if ((ret = ctx.ret)) goto end;

    ret = cowl_vector_ptr_add(&onto->axioms_by_type[cowl_axiom_get_type(axiom)], axiom);

end:
    if (ret) cowl_handle_error_code(ret, onto);
    return ret;
}

void cowl_ontology_remove_axiom(CowlOntology *onto, CowlAnyAxiom *axiom) {
    CowlAxiomType type = cowl_axiom_get_type(axiom);
    if (!onto->axioms_by_type[type]) return;

    UVec(CowlObjectPtr) *vec = &onto->axioms_by_type[type]->data;
    if (!uvec_remove(CowlObjectPtr, vec, axiom)) return;

    CowlAxiomCtx ctx = { .onto = onto, .axiom = axiom };
    CowlIterator iter = { &ctx, cowl_ontology_primitive_axiom_remover };
    cowl_axiom_iterate_primitives(axiom, COWL_PF_ALL, &iter);

    cowl_release(axiom);
}

cowl_ret cowl_ontology_finalize(CowlOntology *onto) {
    cowl_ret ret = COWL_ERR_MEM;
    if (cowl_vector_shrink(onto->annotations)) goto err;

    for (CowlAxiomType i = COWL_AT_FIRST; i < COWL_AT_COUNT; ++i) {
        if (cowl_vector_shrink(onto->axioms_by_type[i])) goto err;
    }

    for (CowlPrimitiveType i = COWL_PT_FIRST; i < COWL_PT_COUNT; ++i) {
        uhash_foreach(CowlObjectTable, &onto->refs[i], item) {
            if (cowl_vector_shrink(*item.val)) goto err;
        }
    }

    ret = COWL_OK;

err:
    if (ret) cowl_handle_error_code(ret, onto);
    return ret;
}
