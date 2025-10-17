/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_ontology.h"
#include "cowl_any.h"
#include "cowl_axiom.h"
#include "cowl_axiom_filter_private.h"
#include "cowl_axiom_flags.h"
#include "cowl_axiom_type.h"
#include "cowl_change.h"
#include "cowl_config.h"
#include "cowl_entity.h"
#include "cowl_iterator.h"
#include "cowl_object_private.h"
#include "cowl_object_type.h"
#include "cowl_ontology_private.h"
#include "cowl_position.h"
#include "cowl_prefix_map_private.h"
#include "cowl_primitive_flags.h"
#include "cowl_primitive_private.h"
#include "cowl_primitive_type.h"
#include "cowl_reader.h"
#include "cowl_ret.h"
#include "cowl_table_private.h"
#include "cowl_vector_private.h"
#include "cowl_writer.h"
#include "ulib.h"
#include <assert.h>
#include <stddef.h>

CowlOntology *cowl_ontology(void) {
    CowlOntology *onto = ulib_alloc(onto);
    if (!onto) goto err;

    *onto = (CowlOntology){
        .super = COWL_OBJECT_INIT(COWL_OT_ONTOLOGY),
        .pm = cowl_prefix_map(),
        .annot = cowl_vector_ordered_empty(),
    };

    if (!(onto->pm && onto->annot)) goto err;

    for (CowlPrimitiveType i = COWL_PT_FIRST; i < COWL_PT_COUNT; ++i) {
        onto->refs[i] = cowl_primitive_map();
    }

    return onto;

err:
    if (onto) cowl_ontology_free(onto);
    return NULL;
}

void cowl_ontology_free(CowlOntology *onto) {
    cowl_release(onto->pm);
    cowl_release(onto->iri);
    cowl_release(onto->version);
    cowl_release(onto->imports);
    cowl_release(onto->annot);

    for (CowlAxiomType type = COWL_AT_FIRST; type < COWL_AT_COUNT; type++) {
        cowl_release(onto->axioms_by_type[type]);
    }

    for (ulib_uint i = 0; i < ulib_array_count(onto->refs); ++i) {
        uhash_foreach (CowlObjectPtr, &onto->refs[i], vec) {
            cowl_vector_release_ex(*vec.val, false);
        }
        uhash_deinit(CowlObjectPtr, &onto->refs[i]);
    }

    ulib_free(onto);
}

CowlOntology *cowl_ontology_at_path(UString path) {
    return cowl_reader_read_ontology_at_path(cowl_get_reader(), path);
}

CowlOntology *cowl_ontology_from_stream(UIStream *stream) {
    return cowl_reader_read_ontology(cowl_get_reader(), stream);
}

cowl_ret cowl_ontology_to_path(CowlOntology *onto, UString path) {
    return cowl_writer_write_ontology_to_path(cowl_get_writer(), path, onto);
}

cowl_ret cowl_ontology_to_stream(CowlOntology *onto, UOStream *stream) {
    return cowl_writer_write_ontology(cowl_get_writer(), stream, onto);
}

CowlPrefixMap *cowl_ontology_get_prefix_map(CowlOntology *onto) {
    return onto->pm;
}

CowlIRI *cowl_ontology_get_iri(CowlOntology *onto) {
    return onto->iri;
}

CowlIRI *cowl_ontology_get_version(CowlOntology *onto) {
    return onto->version;
}

CowlVector *cowl_ontology_get_annot(CowlOntology *onto) {
    return onto->annot;
}

ulib_uint cowl_ontology_axiom_count(CowlOntology *onto) {
    ulib_uint count = 0;

    for (CowlAxiomType type = COWL_AT_FIRST; type < COWL_AT_COUNT; ++type) {
        count += cowl_vector_count(onto->axioms_by_type[type]);
    }

    return count;
}

ulib_uint cowl_ontology_imports_count(CowlOntology *onto) {
    return cowl_vector_count(onto->imports);
}

ulib_uint cowl_ontology_axiom_count_for_type(CowlOntology *onto, CowlAxiomType type) {
    return cowl_vector_count(onto->axioms_by_type[type]);
}

ulib_uint cowl_ontology_axiom_count_for_types(CowlOntology *onto, CowlAxiomFlags types) {
    ulib_uint count = 0;
    cowl_axiom_flags_foreach_type (types, type) {
        count += cowl_ontology_axiom_count_for_type(onto, type);
    }
    return count;
}

ulib_uint cowl_ontology_axiom_count_for_primitive(CowlOntology *onto, CowlAnyPrimitive *primitive) {
    CowlPrimitiveType type = cowl_primitive_get_type(primitive);
    UHash(CowlObjectPtr) *table = &onto->refs[type];
    ulib_uint count = cowl_vector_count(uhmap_get(CowlObjectPtr, table, primitive, NULL));

    if (cowl_primitive_type_is_entity(type)) {
        CowlIRI *iri = cowl_entity_get_iri(primitive);
        count += cowl_vector_count(uhmap_get(CowlObjectPtr, &onto->refs[COWL_PT_IRI], iri, NULL));
    }

    return count;
}

ulib_uint cowl_ontology_primitives_count(CowlOntology *onto, CowlPrimitiveFlags flags) {
    ulib_uint count = 0;

    for (CowlPrimitiveType i = COWL_PT_FIRST; i < COWL_PT_COUNT; ++i) {
        if (cowl_primitive_flags_has_type(flags, i)) {
            count += uhash_count(CowlObjectPtr, &onto->refs[i]);
        }
    }

    return count;
}

bool cowl_ontology_has_primitive(CowlOntology *onto, CowlAnyPrimitive *primitive) {
    CowlPrimitiveType type = cowl_primitive_get_type(primitive);
    if (uhash_contains(CowlObjectPtr, &onto->refs[type], primitive)) return true;

    if (cowl_primitive_type_is_entity(type)) {
        CowlIRI *iri = cowl_entity_get_iri(primitive);
        if (uhash_contains(CowlObjectPtr, &onto->refs[COWL_PT_IRI], iri)) return true;
    }

    return false;
}

bool cowl_ontology_has_axiom(CowlOntology *onto, CowlAnyAxiom *axiom) {
    CowlVector *vec = onto->axioms_by_type[cowl_axiom_get_type(axiom)];
    if (vec && cowl_vector_contains(vec, axiom)) return true;
    return false;
}

bool cowl_ontology_iterate_annot(CowlOntology *onto, CowlIterator *iter) {
    cowl_vector_foreach (onto->annot, annot) {
        if (!cowl_iterator_call(iter, *annot.item)) return false;
    }
    return true;
}

bool cowl_ontology_iterate_imports(CowlOntology *onto, CowlIterator *iter) {
    cowl_vector_foreach (onto->imports, import) {
        if (!cowl_iterator_call(iter, *import.item)) return false;
    }
    return true;
}

bool cowl_ontology_iterate_primitives(CowlOntology *onto, CowlPrimitiveFlags flags,
                                      CowlIterator *iter) {
    for (CowlPrimitiveType i = COWL_PT_FIRST; i < COWL_PT_COUNT; ++i) {
        if (!cowl_primitive_flags_has_type(flags, i)) continue;
        uhash_foreach (CowlObjectPtr, &onto->refs[i], p) {
            if (!cowl_iterate_primitives(*p.key, flags, iter)) return false;
        }
    }
    return true;
}

bool cowl_ontology_iterate_axioms(CowlOntology *onto, CowlIterator *iter) {
    for (CowlAxiomType type = COWL_AT_FIRST; type < COWL_AT_COUNT; ++type) {
        cowl_vector_foreach (onto->axioms_by_type[type], axiom) {
            if (!cowl_iterator_call(iter, *axiom.item)) return false;
        }
    }
    return true;
}

bool cowl_ontology_iterate_axioms_of_type(CowlOntology *onto, CowlAxiomType type,
                                          CowlIterator *iter) {
    cowl_vector_foreach (onto->axioms_by_type[type], axiom) {
        if (!cowl_iterator_call(iter, *axiom.item)) return false;
    }
    return true;
}

bool cowl_ontology_iterate_axioms_of_types(CowlOntology *onto, CowlAxiomFlags types,
                                           CowlIterator *iter) {
    cowl_axiom_flags_foreach_type (types, type) {
        if (!cowl_ontology_iterate_axioms_of_type(onto, type, iter)) return false;
    }
    return true;
}

bool cowl_ontology_iterate_axioms_for_primitive(CowlOntology *onto, CowlAnyPrimitive *primitive,
                                                CowlIterator *iter) {
    CowlPrimitiveType type = cowl_primitive_get_type(primitive);
    UHash(CowlObjectPtr) *table = &onto->refs[type];

    cowl_vector_foreach (uhmap_get(CowlObjectPtr, table, primitive, NULL), a) {
        if (!cowl_iterator_call(iter, *a.item)) return false;
    }

    if (cowl_primitive_type_is_entity(type)) {
        CowlIRI *iri = cowl_entity_get_iri(primitive);
        cowl_vector_foreach (uhmap_get(CowlObjectPtr, &onto->refs[COWL_PT_IRI], iri, NULL), a) {
            if (!cowl_iterator_call(iter, *a.item)) return false;
        }
    }

    return true;
}

static CowlAnyPrimitive *
cowl_ontology_best_primitive_for_filter(CowlOntology *onto, CowlAxiomFilter *filter) {
    if (cowl_axiom_flags_has_no_types(filter->types)) {
        // No types specified in the filter.
        filter->types = COWL_AF_NONE;
        return NULL;
    }

    CowlAnyPrimitive *best = NULL;
    ulib_uint count = ULIB_UINT_MAX;

    uvec_foreach (CowlObjectPtr, &filter->primitives, p) {
        ulib_uint c = cowl_ontology_axiom_count_for_primitive(onto, *p.item);
        if (c < count) {
            best = *p.item;
            count = c;
        }
    }

    if (cowl_axiom_flags_has_all_types(filter->types)) {
        filter->types = COWL_AF_ALL;
    } else {
        ulib_uint c = cowl_ontology_axiom_count_for_types(onto, filter->types);
        if (c < count) best = NULL;
    }

    if (!count) {
        // Index matches an empty set of axioms.
        filter->types = COWL_AF_NONE;
        return NULL;
    }

    return best;
}

struct MatchingCtx {
    CowlAxiomFilter *filter;
    CowlIterator *iter;
};

static bool for_each_filter(void *ctx, CowlAnyAxiom *axiom) {
    struct MatchingCtx *mctx = ctx;
    if (!cowl_axiom_filter_matches(mctx->filter, axiom)) return true;
    return cowl_iterator_call(mctx->iter, axiom);
}

bool cowl_ontology_iterate_axioms_matching(CowlOntology *onto, CowlAxiomFilter *filter,
                                           CowlIterator *iter) {
    bool ret = true;
    CowlAxiomFilter f = cowl_axiom_filter_move(filter);

    struct MatchingCtx ctx = {
        .filter = &f,
        .iter = iter,
    };

    CowlAnyPrimitive *best = cowl_ontology_best_primitive_for_filter(onto, &f);
    if (f.types == COWL_AF_NONE) goto end;

    UBit(8) const NONE = ubit_none(8);
    UBit(8) const TYPES = ubit_bit(8, 0);
    UBit(8) const PRIMITIVES = ubit_bit(8, 1);
    UBit(8) const FILTER = ubit_bit(8, 2);
    UBit(8) check = NONE;

    if (f.types != COWL_AF_ALL) check = ubit_set(8, check, TYPES);
    if (uvec_count(CowlObjectPtr, &f.primitives)) check = ubit_set(8, check, PRIMITIVES);
    if (f.closure.filter) check = ubit_set(8, check, FILTER);

    if (best) {
        // We will be iterating only over axioms that reference this primitive.
        cowl_axiom_filter_remove_primitive(filter, best);
        if (check) {
            CowlIterator l_iter = { .ctx = &ctx, .for_each = for_each_filter };
            ret = cowl_ontology_iterate_axioms_for_primitive(onto, best, &l_iter);
        } else {
            ret = cowl_ontology_iterate_axioms_for_primitive(onto, best, iter);
        }
    } else {
        // We will be iterating only over axioms of the specified types.
        CowlAxiomFlags types = f.types;
        f.types = COWL_AF_ALL;
        if (check == NONE) {
            ret = cowl_ontology_iterate_axioms(onto, iter);
        } else if (check == TYPES) {
            ret = cowl_ontology_iterate_axioms_of_types(onto, types, iter);
        } else if (ubit_is_set(8, check, TYPES)) {
            CowlIterator l_iter = { .ctx = &ctx, .for_each = for_each_filter };
            ret = cowl_ontology_iterate_axioms_of_types(onto, types, &l_iter);
        } else {
            CowlIterator l_iter = { .ctx = &ctx, .for_each = for_each_filter };
            ret = cowl_ontology_iterate_axioms(onto, &l_iter);
        }
    }

end:
    cowl_axiom_filter_deinit(&f);
    return ret;
}

struct RelatedCtx {
    CowlAxiomType type;
    CowlPosition position;
    CowlAnyPrimitive *primitive;
    CowlIterator *iter;
};

static bool for_each_related_operand(void *ctx, CowlAny *op) {
    struct RelatedCtx *c = ctx;
    return c->primitive == op || cowl_iterator_call(c->iter, op);
}

static bool for_each_related(void *ctx, CowlAny *axiom) {
    struct RelatedCtx *c = ctx;
    if (cowl_axiom_get_type(axiom) != c->type) return true;
    if (!cowl_axiom_has_operand(axiom, c->primitive, COWL_PS_ANY)) return true;
    CowlIterator iter = { .ctx = ctx, .for_each = for_each_related_operand };
    return cowl_axiom_iterate_operands(axiom, c->position, &iter);
}

bool cowl_ontology_iterate_related(CowlOntology *onto, CowlAnyPrimitive *primitive,
                                   CowlAxiomType type, CowlPosition position, CowlIterator *iter) {
    struct RelatedCtx ctx = {
        .type = type,
        .position = position,
        .primitive = primitive,
        .iter = iter,
    };
    CowlIterator l_iter = { .ctx = &ctx, .for_each = for_each_related };

    // Iterate over the smallest possible set of axioms.
    CowlPrimitiveType pt = cowl_primitive_get_type(primitive);
    CowlVector *ar = uhmap_get(CowlObjectPtr, &onto->refs[pt], primitive, NULL);
    CowlVector *at = onto->axioms_by_type[type];

    if (cowl_vector_count(at) < cowl_vector_count(ar)) {
        return cowl_ontology_iterate_axioms_of_type(onto, type, iter);
    }
    return cowl_ontology_iterate_axioms_for_primitive(onto, primitive, &l_iter);
}

cowl_ret cowl_ontology_set_iri(CowlOntology *onto, CowlIRI *iri) {
    cowl_release(onto->iri);
    onto->iri = iri ? cowl_retain(iri) : NULL;
    return COWL_OK;
}

cowl_ret cowl_ontology_set_version(CowlOntology *onto, CowlIRI *version) {
    cowl_release(onto->version);
    onto->version = version ? cowl_retain(version) : NULL;
    return COWL_OK;
}

typedef struct CowlAxiomCtx {
    cowl_ret ret;
    CowlOntology *onto;
    CowlAxiom *axiom;
} CowlAxiomCtx;

static cowl_ret cowl_add_primitive_to_map(CowlObject *primitive, UHash(CowlObjectPtr) *map) {
    ulib_uint idx;
    ulib_ret const ret = uhash_put(CowlObjectPtr, map, primitive, &idx);
    if (ulib_is_err(ret)) return cowl_ret_from_ulib(ret);
    if (ret == ULIB_OK) uhmap_set_val(CowlObjectPtr, map, idx, NULL);
    return COWL_OK;
}

static bool cowl_ontology_primitive_adder(void *ctx, CowlAny *obj) {
    CowlAxiomCtx *axiom_ctx = ctx;
    UHash(CowlObjectPtr) *map = &axiom_ctx->onto->refs[cowl_primitive_get_type(obj)];
    cowl_ret const ret = cowl_add_primitive_to_map(obj, map);
    axiom_ctx->ret = ret;
    return ret == COWL_OK;
}

static inline cowl_ret cowl_vector_ptr_add(CowlVector **vec, CowlAny *obj) {
    if (!(*vec || (*vec = cowl_vector_ordered_empty()))) return COWL_ERR_MEM;
    return cowl_vector_add(*vec, obj) ? COWL_ERR_MEM : COWL_OK;
}

cowl_ret cowl_ontology_add_annot(CowlOntology *onto, CowlAnnotation *annot) {
    cowl_ret ret;
    CowlAxiomCtx ctx = { .onto = onto };
    CowlIterator iter = { &ctx, cowl_ontology_primitive_adder };
    cowl_iterate_primitives(annot, COWL_PF_ALL, &iter);
    if (!(ret = ctx.ret)) ret = cowl_vector_ptr_add(&onto->annot, annot);
    return ret;
}

bool cowl_ontology_remove_annot(CowlOntology *onto, CowlAnnotation *annot) {
    return cowl_vector_remove(onto->annot, annot);
}

bool cowl_ontology_has_import(CowlOntology *onto, CowlIRI *import) {
    return onto->imports ? cowl_vector_contains(onto->imports, import) : false;
}

cowl_ret cowl_ontology_add_import(CowlOntology *onto, CowlIRI *import) {
    if (!onto->imports && !(onto->imports = cowl_vector_empty())) return COWL_ERR_MEM;
    return cowl_vector_add(onto->imports, import);
}

bool cowl_ontology_remove_import(CowlOntology *onto, CowlIRI *iri) {
    if (!onto->imports) return false;
    bool removed = cowl_vector_remove(onto->imports, iri);
    if (removed && cowl_vector_count(onto->imports) == 0) {
        cowl_release(onto->imports);
        onto->imports = NULL;
    }
    return removed;
}

static inline cowl_ret
cowl_add_axiom_to_map(CowlObject *primitive, CowlAxiom *axiom, UHash(CowlObjectPtr) *map) {
    ulib_uint idx;
    ulib_ret const ret = uhash_put(CowlObjectPtr, map, primitive, &idx);
    if (ulib_is_err(ret)) return cowl_ret_from_ulib(ret);

    CowlVector *vec = uhmap_val(CowlObjectPtr, map, idx);

    if (ret == ULIB_OK || !vec) {
        vec = cowl_vector_ordered_empty();
        uhmap_set_val(CowlObjectPtr, map, idx, vec);
        if (!vec) return COWL_ERR_MEM;
    }

    if (cowl_vector_push(vec, axiom)) {
        return COWL_ERR_MEM;
    }

    return COWL_OK;
}

static bool cowl_ontology_primitive_axiom_adder(void *ctx, CowlAny *obj) {
    CowlAxiomCtx *axiom_ctx = ctx;
    UHash(CowlObjectPtr) *map = &axiom_ctx->onto->refs[cowl_primitive_get_type(obj)];
    cowl_ret ret = cowl_add_axiom_to_map(obj, axiom_ctx->axiom, map);
    axiom_ctx->ret = ret;
    return ret == COWL_OK;
}

cowl_ret cowl_ontology_add_axiom(CowlOntology *onto, CowlAnyAxiom *axiom) {
    cowl_ret ret;
    CowlAxiomCtx ctx = { .onto = onto, .axiom = axiom };
    CowlIterator iter = { &ctx, cowl_ontology_primitive_axiom_adder };

    cowl_iterate_primitives(axiom, COWL_PF_ALL, &iter);
    if ((ret = ctx.ret)) return ret;
    return cowl_vector_ptr_add(&onto->axioms_by_type[cowl_axiom_get_type(axiom)], axiom);
}

static inline void
cowl_remove_axiom_from_map(CowlObject *primitive, CowlAxiom *axiom, UHash(CowlObjectPtr) *map) {
    CowlVector *vec = uhmap_get(CowlObjectPtr, map, primitive, NULL);
    if (!vec) return;
    uvec_foreach_reverse (CowlObjectPtr, &vec->data, a) {
        if (*a.item == axiom) {
            uvec_unordered_remove_at(CowlObjectPtr, &vec->data, a.i);
            break;
        }
    }
}

static bool cowl_ontology_primitive_axiom_remover(void *ctx, void *obj) {
    CowlAxiomCtx *axiom_ctx = ctx;
    UHash(CowlObjectPtr) *map = &axiom_ctx->onto->refs[cowl_primitive_get_type(obj)];
    cowl_remove_axiom_from_map(obj, axiom_ctx->axiom, map);
    axiom_ctx->ret = COWL_OK;
    return true;
}

static void cowl_ontology_remove_axiom_ptr(CowlOntology *onto, CowlAnyAxiom *axiom) {
    // We could just use uvec_unordered_remove, though looking for axioms to remove in reverse
    // is desirable as recently added axioms are likely to be at the top of the vector.
    UVec(CowlObjectPtr) *vec = &onto->axioms_by_type[cowl_axiom_get_type(axiom)]->data;
    uvec_foreach_reverse (CowlObjectPtr, vec, a) {
        if (*a.item == axiom) {
            uvec_unordered_remove_at(CowlObjectPtr, vec, a.i);
            break;
        }
    }

    CowlAxiomCtx ctx = { .onto = onto, .axiom = axiom };
    CowlIterator iter = { &ctx, cowl_ontology_primitive_axiom_remover };
    cowl_iterate_primitives(axiom, COWL_PF_ALL, &iter);
    cowl_release(axiom);
}

bool cowl_ontology_remove_axiom(CowlOntology *onto, CowlAnyAxiom *axiom) {
    CowlAxiomType type = cowl_axiom_get_type(axiom);
    if (!onto->axioms_by_type[type]) return false;

    // Iterate in reverse to match the element removed by cowl_ontology_remove_axiom_ptr.
    // TODO: this can be optimized by finding the best index for the axiom.
    UVec(CowlObjectPtr) *vec = &onto->axioms_by_type[type]->data;
    uvec_foreach_reverse (CowlObjectPtr, vec, a) {
        if (cowl_equals(axiom, *a.item)) {
            cowl_ontology_remove_axiom_ptr(onto, axiom);
            return true;
        }
    }

    return false;
}

ulib_uint cowl_ontology_remove_axioms_matching(CowlOntology *onto, CowlAxiomFilter *filter) {
    ulib_uint count = 0;
    CowlAxiomFilter f = cowl_axiom_filter_move(filter);
    if (f.types == COWL_AF_NONE) goto end;

    CowlAnyPrimitive *best = cowl_ontology_best_primitive_for_filter(onto, &f);
    if (best) {
        // Iterate over axioms referencing the primitive.
        cowl_axiom_filter_remove_primitive(filter, best);
        UHash(CowlObjectPtr) *table = &onto->refs[cowl_primitive_get_type(best)];
        CowlVector *vec = uhmap_get(CowlObjectPtr, table, best, NULL);
        uvec_foreach_reverse (CowlObjectPtr, &vec->data, axiom) {
            CowlAnyAxiom *a = *axiom.item;
            if (!cowl_axiom_filter_matches(&f, a)) continue;
            cowl_ontology_remove_axiom_ptr(onto, a);
            count++;
        }
    } else {
        // Iterate over axioms of the specified types.
        CowlAxiomFlags types = f.types;
        f.types = COWL_AF_ALL;
        cowl_axiom_flags_foreach_type (types, type) {
            CowlVector *vec = onto->axioms_by_type[type];
            if (!vec) continue;
            uvec_foreach_reverse (CowlObjectPtr, &vec->data, axiom) {
                CowlAnyAxiom *a = *axiom.item;
                if (!cowl_axiom_filter_matches(&f, a)) continue;
                cowl_ontology_remove_axiom_ptr(onto, a);
                count++;
            }
        }
    }

end:
    cowl_axiom_filter_deinit(&f);
    return count;
}

cowl_ret cowl_ontology_finalize(CowlOntology *onto) {
    if (cowl_vector_shrink(onto->annot)) return COWL_ERR_MEM;

    for (CowlAxiomType t = COWL_AT_FIRST; t < COWL_AT_COUNT; ++t) {
        CowlVector *axioms = onto->axioms_by_type[t];
        if (axioms && cowl_vector_shrink(axioms)) return COWL_ERR_MEM;
    }

    for (CowlPrimitiveType i = COWL_PT_FIRST; i < COWL_PT_COUNT; ++i) {
        uhash_foreach (CowlObjectPtr, &onto->refs[i], item) {
            CowlVector *primitives = *item.val;
            if (primitives && cowl_vector_shrink(primitives)) return COWL_ERR_MEM;
        }
    }

    return COWL_OK;
}
