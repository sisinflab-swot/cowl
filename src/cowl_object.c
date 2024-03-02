/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_object_private.h"
#include "cowl_private.h"

/*
 * Type flags have the following structure:
 *
 * |---|C|E|P|FC|
 *
 * FC = field count (2 bits)
 * P = is primitive (1 bit)
 * E = is entity (1 bit)
 * C = is cardinality restriction (1 bit)
 */

#define TF_FC(field_count) (field_count)
#define TF_NONE 0x0U
#define TF_PRIMITIVE 0x4U
#define TF_ENTITY 0x8U
#define TF_CARD_RESTR 0x10U

static ulib_byte type_flags[COWL_OT_COUNT] = {
    [COWL_OT_STRING] = TF_NONE,
    [COWL_OT_VECTOR] = TF_NONE,
    [COWL_OT_TABLE] = TF_NONE,
    [COWL_OT_IRI] = TF_PRIMITIVE,
    [COWL_OT_LITERAL] = TF_NONE,
    [COWL_OT_FACET_RESTR] = TF_FC(2),
    [COWL_OT_ONTOLOGY] = TF_NONE,
    [COWL_OT_MANAGER] = TF_NONE,
    [COWL_OT_SYM_TABLE] = TF_NONE,
    [COWL_OT_ISTREAM] = TF_NONE,
    [COWL_OT_OSTREAM] = TF_NONE,
    [COWL_OT_ANNOTATION] = TF_FC(2),
    [COWL_OT_ANNOT_PROP] = TF_PRIMITIVE | TF_ENTITY,
    [COWL_OT_A_DECL] = TF_FC(1),
    [COWL_OT_A_DATATYPE_DEF] = TF_FC(2),
    [COWL_OT_A_SUB_CLASS] = TF_FC(2),
    [COWL_OT_A_EQUIV_CLASSES] = TF_FC(1),
    [COWL_OT_A_DISJ_CLASSES] = TF_FC(1),
    [COWL_OT_A_DISJ_UNION] = TF_FC(2),
    [COWL_OT_A_CLASS_ASSERT] = TF_FC(2),
    [COWL_OT_A_SAME_IND] = TF_FC(1),
    [COWL_OT_A_DIFF_IND] = TF_FC(1),
    [COWL_OT_A_OBJ_PROP_ASSERT] = TF_FC(3),
    [COWL_OT_A_NEG_OBJ_PROP_ASSERT] = TF_FC(3),
    [COWL_OT_A_DATA_PROP_ASSERT] = TF_FC(3),
    [COWL_OT_A_NEG_DATA_PROP_ASSERT] = TF_FC(3),
    [COWL_OT_A_SUB_OBJ_PROP] = TF_FC(2),
    [COWL_OT_A_INV_OBJ_PROP] = TF_FC(2),
    [COWL_OT_A_EQUIV_OBJ_PROP] = TF_FC(1),
    [COWL_OT_A_DISJ_OBJ_PROP] = TF_FC(1),
    [COWL_OT_A_FUNC_OBJ_PROP] = TF_FC(1),
    [COWL_OT_A_INV_FUNC_OBJ_PROP] = TF_FC(1),
    [COWL_OT_A_SYMM_OBJ_PROP] = TF_FC(1),
    [COWL_OT_A_ASYMM_OBJ_PROP] = TF_FC(1),
    [COWL_OT_A_TRANS_OBJ_PROP] = TF_FC(1),
    [COWL_OT_A_REFL_OBJ_PROP] = TF_FC(1),
    [COWL_OT_A_IRREFL_OBJ_PROP] = TF_FC(1),
    [COWL_OT_A_OBJ_PROP_DOMAIN] = TF_FC(2),
    [COWL_OT_A_OBJ_PROP_RANGE] = TF_FC(2),
    [COWL_OT_A_SUB_DATA_PROP] = TF_FC(2),
    [COWL_OT_A_EQUIV_DATA_PROP] = TF_FC(1),
    [COWL_OT_A_DISJ_DATA_PROP] = TF_FC(1),
    [COWL_OT_A_FUNC_DATA_PROP] = TF_FC(1),
    [COWL_OT_A_DATA_PROP_DOMAIN] = TF_FC(2),
    [COWL_OT_A_DATA_PROP_RANGE] = TF_FC(2),
    [COWL_OT_A_HAS_KEY] = TF_FC(3),
    [COWL_OT_A_ANNOT_ASSERT] = TF_FC(3),
    [COWL_OT_A_SUB_ANNOT_PROP] = TF_FC(2),
    [COWL_OT_A_ANNOT_PROP_DOMAIN] = TF_FC(2),
    [COWL_OT_A_ANNOT_PROP_RANGE] = TF_FC(2),
    [COWL_OT_CE_CLASS] = TF_PRIMITIVE | TF_ENTITY,
    [COWL_OT_CE_OBJ_SOME] = TF_FC(1),
    [COWL_OT_CE_OBJ_ALL] = TF_FC(1),
    [COWL_OT_CE_OBJ_MIN_CARD] = TF_FC(1) | TF_CARD_RESTR,
    [COWL_OT_CE_OBJ_MAX_CARD] = TF_FC(1) | TF_CARD_RESTR,
    [COWL_OT_CE_OBJ_EXACT_CARD] = TF_FC(1) | TF_CARD_RESTR,
    [COWL_OT_CE_OBJ_HAS_VALUE] = TF_FC(2),
    [COWL_OT_CE_OBJ_HAS_SELF] = TF_FC(1),
    [COWL_OT_CE_DATA_SOME] = TF_FC(1),
    [COWL_OT_CE_DATA_ALL] = TF_FC(1),
    [COWL_OT_CE_DATA_MIN_CARD] = TF_FC(1) | TF_CARD_RESTR,
    [COWL_OT_CE_DATA_MAX_CARD] = TF_FC(1) | TF_CARD_RESTR,
    [COWL_OT_CE_DATA_EXACT_CARD] = TF_FC(1) | TF_CARD_RESTR,
    [COWL_OT_CE_DATA_HAS_VALUE] = TF_FC(2),
    [COWL_OT_CE_OBJ_INTERSECT] = TF_FC(1),
    [COWL_OT_CE_OBJ_UNION] = TF_FC(1),
    [COWL_OT_CE_OBJ_COMPL] = TF_FC(1),
    [COWL_OT_CE_OBJ_ONE_OF] = TF_FC(1),
    [COWL_OT_DPE_DATA_PROP] = TF_PRIMITIVE | TF_ENTITY,
    [COWL_OT_DR_DATATYPE] = TF_PRIMITIVE | TF_ENTITY,
    [COWL_OT_DR_DATATYPE_RESTR] = TF_FC(2),
    [COWL_OT_DR_DATA_INTERSECT] = TF_FC(1),
    [COWL_OT_DR_DATA_UNION] = TF_FC(1),
    [COWL_OT_DR_DATA_COMPL] = TF_FC(1),
    [COWL_OT_DR_DATA_ONE_OF] = TF_FC(1),
    [COWL_OT_I_ANONYMOUS] = TF_PRIMITIVE,
    [COWL_OT_I_NAMED] = TF_PRIMITIVE | TF_ENTITY,
    [COWL_OT_OPE_OBJ_PROP] = TF_PRIMITIVE | TF_ENTITY,
    [COWL_OT_OPE_INV_OBJ_PROP] = TF_FC(1),
};

#define type_flag_is_special(f) (!(f))
#define type_flag_is_primitive(f) ((f) & (0x4U))
#define type_flag_is_entity(f) ((f) & (0x8U))
#define type_flag_is_card_restr(f) ((f) & (0x10U))
#define type_flag_field_count(f) ((f) & (0x3U))

#define type_is_primitive(t) type_flag_is_primitive(type_flags[t])
#define type_is_entity(t) type_flag_is_entity(type_flags[t])
#define type_field_count(t) type_flag_field_count(type_flags[t])

CowlAny *cowl_retain(CowlAny *object) {
    return cowl_object_incr_ref(object);
}

static inline void release_impl(CowlObjectType type, CowlComposite *object) {
    ulib_byte n = type_field_count(type);
    if (cowl_has_opt_field(object)) ++n;
    for (ulib_byte i = 0; i < n; ++i) {
        cowl_release(object->fields[i].obj);
    }
    ulib_free(object);
}

void cowl_release(CowlAny *object) {
    if (!object || cowl_object_decr_ref(object)) return;
    CowlObjectType type = cowl_get_type(object);

    switch (type) {
        case COWL_OT_STRING: cowl_string_free(object); return;
        case COWL_OT_VECTOR: cowl_vector_free(object); return;
        case COWL_OT_TABLE: cowl_table_free(object); return;
        case COWL_OT_IRI: cowl_iri_free(object); return;
        case COWL_OT_LITERAL: cowl_literal_free(object); return;
        case COWL_OT_ONTOLOGY: cowl_ontology_free(object); return;
        case COWL_OT_MANAGER: cowl_manager_free(object); return;
        case COWL_OT_SYM_TABLE: cowl_sym_table_free(object); return;
        case COWL_OT_ISTREAM: cowl_istream_free(object); return;
        case COWL_OT_OSTREAM: cowl_ostream_free(object); return;
        case COWL_OT_I_ANONYMOUS: cowl_anon_ind_free(object); return;
        case COWL_OT_ANNOT_PROP:
        case COWL_OT_CE_CLASS:
        case COWL_OT_DPE_DATA_PROP:
        case COWL_OT_DR_DATATYPE:
        case COWL_OT_I_NAMED:
        case COWL_OT_OPE_OBJ_PROP: cowl_entity_free(object); return;
        default: release_impl(type, object); return;
    }
}

CowlObjectType cowl_get_type(CowlAny *object) {
    return cowl_object_flags_get_type(((CowlObject *)object)->flags);
}

bool cowl_is_primitive(CowlAny *object) {
    return type_is_primitive(cowl_get_type(object));
}

bool cowl_is_entity(CowlAny *object) {
    return type_is_entity(cowl_get_type(object));
}

bool cowl_is_axiom(CowlAny *object) {
    CowlObjectType type = cowl_get_type(object);
    return type >= COWL_OT_FIRST_A && type <= COWL_OT_LAST_A;
}

bool cowl_is_cls_exp(CowlAny *object) {
    CowlObjectType type = cowl_get_type(object);
    return type >= COWL_OT_FIRST_CE && type <= COWL_OT_LAST_CE;
}

bool cowl_is_obj_prop_exp(CowlAny *object) {
    CowlObjectType type = cowl_get_type(object);
    return type >= COWL_OT_FIRST_OPE && type <= COWL_OT_LAST_OPE;
}

bool cowl_is_data_prop_exp(CowlAny *object) {
    return cowl_get_type(object) == COWL_OT_DPE_DATA_PROP;
}

bool cowl_is_individual(CowlAny *object) {
    CowlObjectType type = cowl_get_type(object);
    return type >= COWL_OT_FIRST_I && type <= COWL_OT_LAST_I;
}

bool cowl_is_data_range(CowlAny *object) {
    CowlObjectType type = cowl_get_type(object);
    return type >= COWL_OT_FIRST_DR && type <= COWL_OT_LAST_DR;
}

CowlIRI *cowl_get_iri(CowlAny *object) {
    CowlObjectType type = cowl_get_type(object);
    if (type_is_entity(type)) return cowl_entity_get_iri(object);
    if (type == COWL_OT_IRI) return object;
    return type == COWL_OT_ONTOLOGY ? cowl_ontology_get_id(object).iri : NULL;
}

bool cowl_has_iri(CowlAny *object, CowlIRI *iri) {
    return cowl_primitive_equals(cowl_get_iri(object), iri);
}

bool cowl_has_iri_string(CowlAny *object, UString iri_str) {
    CowlIRI *iri = cowl_get_iri(object);
    if (!iri) return false;

    CowlString *ns = cowl_iri_get_ns(iri), *rem = cowl_iri_get_rem(iri);
    ulib_uint ns_len = cowl_string_get_length(ns), rem_len = cowl_string_get_length(rem);

    if (ustring_length(iri_str) != ns_len + rem_len) return false;
    if (!ustring_ends_with(iri_str, *cowl_string_get_raw(rem))) return false;
    return ustring_starts_with(iri_str, *cowl_string_get_raw(ns));
}

CowlString *cowl_get_ns(CowlAny *object) {
    CowlIRI *iri = cowl_get_iri(object);
    return iri ? cowl_iri_get_ns(iri) : NULL;
}

CowlString *cowl_get_rem(CowlAny *object) {
    CowlIRI *iri = cowl_get_iri(object);
    return iri ? cowl_iri_get_rem(iri) : NULL;
}

CowlVector *cowl_get_annot(CowlAny *object) {
    CowlObjectType type = cowl_get_type(object);
    if (type >= COWL_OT_FIRST_A && type <= COWL_OT_LAST_A) return cowl_axiom_get_annot(object);
    if (type == COWL_OT_ANNOTATION) return cowl_annotation_get_annot(object);
    if (type == COWL_OT_ONTOLOGY) return cowl_ontology_get_annot(object);
    return NULL;
}

static cowl_ret cowl_write_debug_impl(UOStream *stream, CowlAny *object) {
    return cowl_ret_from_ustream(cowl_write_debug(stream, object));
}

static CowlString *cowl_to_string_impl(CowlAny *object, cowl_ret (*fun)(UOStream *, CowlAny *)) {
    UOStream stream;
    UStrBuf buf = ustrbuf();
    if (uostream_to_strbuf(&stream, &buf) || fun(&stream, object)) goto err;

    CowlString *string = cowl_string(ustrbuf_to_ustring(&buf));
    uostream_deinit(&stream);
    return string;

err:
    uostream_deinit(&stream);
    ustrbuf_deinit(&buf);
    return NULL;
}

CowlString *cowl_to_string(CowlAny *object) {
    return cowl_to_string_impl(object, cowl_write);
}

CowlString *cowl_to_debug_string(CowlAny *object) {
    return cowl_to_string_impl(object, cowl_write_debug_impl);
}

bool cowl_equals(CowlAny *lhs, CowlAny *rhs) {
    CowlObjectType type = cowl_get_type(lhs);
    if (type != cowl_get_type(rhs)) return false;

    ulib_byte const flags = type_flags[type];

    if (type_flag_is_special(flags)) {
        switch (type) {
            case COWL_OT_STRING: return cowl_string_equals(lhs, rhs);
            case COWL_OT_VECTOR: return cowl_vector_equals(lhs, rhs);
            case COWL_OT_TABLE: return cowl_table_equals(lhs, rhs);
            case COWL_OT_LITERAL: return cowl_literal_equals(lhs, rhs);
            case COWL_OT_ONTOLOGY: return cowl_ontology_equals(lhs, rhs);
            default: return lhs == rhs;
        }
    }

    ulib_byte n = type_flag_field_count(flags);
    if (!n) return lhs == rhs;

    bool has_opt = cowl_has_opt_field(lhs);
    if (has_opt != cowl_has_opt_field(rhs)) return false;
    if (has_opt) ++n;

    CowlComposite *l = lhs, *r = rhs;
    for (ulib_byte i = 0; i < n; ++i) {
        if (!cowl_equals(l->fields[i].obj, r->fields[i].obj)) return false;
    }

    if (type_flag_is_card_restr(flags)) {
        return cowl_get_uint_field(lhs) == cowl_get_uint_field(rhs);
    }

    return true;
}

bool cowl_is_reserved(CowlAny *object) {
    CowlIRI *iri = cowl_get_iri(object);
    return iri && cowl_iri_is_reserved(iri);
}

ulib_uint cowl_hash(CowlAny *object) {
    CowlObjectType type = cowl_get_type(object);

    ulib_byte const flags = type_flags[type];

    if (type_flag_is_special(flags)) {
        switch (type) {
            case COWL_OT_STRING: return cowl_string_hash(object);
            case COWL_OT_VECTOR: return cowl_vector_hash(object);
            case COWL_OT_TABLE: return cowl_table_hash(object);
            case COWL_OT_LITERAL: return cowl_literal_hash(object);
            case COWL_OT_ONTOLOGY: return cowl_ontology_hash(object);
            default: return ulib_hash_alloc_ptr(object);
        }
    }

    ulib_byte n = type_flag_field_count(flags);
    if (!n) return ulib_hash_alloc_ptr(object);
    if (cowl_has_opt_field(object)) ++n;

    CowlComposite *o = object;
    ulib_uint hash = ulib_hash_combine(6151U, type);

    for (ulib_byte i = 0; i < n; ++i) {
        hash = ulib_hash_combine(hash, cowl_hash(o->fields[i].obj));
    }

    if (type_flag_is_card_restr(flags)) {
        hash = ulib_hash_combine(hash, cowl_get_uint_field(object));
    }

    return hash;
}

bool cowl_has_primitive(CowlAny *object, CowlAnyPrimitive *primitive) {
    CowlIterator iter = cowl_iterator_contains(primitive);
    CowlPrimitiveType t = cowl_primitive_get_type(primitive);
    return !cowl_iterate_primitives(object, cowl_primitive_flags_from_type(t), &iter);
}

static inline bool
iterate_pf(CowlPrimitiveFlags type, CowlAny *object, CowlPrimitiveFlags flags, CowlIterator *iter) {
    return ubit_is_set(COWL_PF, flags, type) ? cowl_iterate(iter, object) : true;
}

static inline bool
iterate_impl(CowlObjectType type, CowlAny *object, CowlPrimitiveFlags flags, CowlIterator *iter) {
    ulib_byte const n = type_field_count(type);
    if (!n) return true;
    CowlComposite *o = object;
    for (ulib_byte i = 0; i < n; ++i) {
        if (!cowl_iterate_primitives(o->fields[i].obj, flags, iter)) return false;
    }
    return cowl_has_opt_field(o) ? cowl_iterate_primitives(o->fields[n].obj, flags, iter) : true;
}

bool cowl_iterate_primitives(CowlAny *object, CowlPrimitiveFlags flags, CowlIterator *iter) {
    CowlObjectType type = cowl_get_type(object);
    switch (type) {
        case COWL_OT_VECTOR: return cowl_vector_iterate_primitives(object, flags, iter);
        case COWL_OT_TABLE: return cowl_table_iterate_primitives(object, flags, iter);
        case COWL_OT_IRI: return iterate_pf(COWL_PF_IRI, object, flags, iter);
        case COWL_OT_LITERAL: return cowl_literal_iterate_primitives(object, flags, iter);
        case COWL_OT_ANNOT_PROP: return iterate_pf(COWL_PF_ANNOT_PROP, object, flags, iter);
        case COWL_OT_CE_CLASS: return iterate_pf(COWL_PF_CLASS, object, flags, iter);
        case COWL_OT_DPE_DATA_PROP: return iterate_pf(COWL_PF_DATA_PROP, object, flags, iter);
        case COWL_OT_DR_DATATYPE: return iterate_pf(COWL_PF_DATATYPE, object, flags, iter);
        case COWL_OT_I_NAMED: return iterate_pf(COWL_PF_NAMED_IND, object, flags, iter);
        case COWL_OT_I_ANONYMOUS: return iterate_pf(COWL_PF_ANON_IND, object, flags, iter);
        case COWL_OT_OPE_OBJ_PROP: return iterate_pf(COWL_PF_OBJ_PROP, object, flags, iter);
        case COWL_OT_ONTOLOGY: return cowl_ontology_iterate_primitives(object, flags, iter, false);
        default: return iterate_impl(type, object, flags, iter);
    }
}

CowlAny *cowl_get_impl(CowlObjectType type, CowlAny *fields[], CowlAny *opt) {
    ulib_byte const n = type_field_count(type);
    CowlComposite *o = ulib_malloc(sizeof(*o) + (opt ? n + 1 : n) * sizeof(*o->fields));
    if (!o) return NULL;

    o->super = COWL_OBJECT_BIT_INIT(type, opt);
    for (ulib_byte i = 0; i < n; ++i) {
        o->fields[i].obj = cowl_retain(fields[i]);
    }
    if (opt) o->fields[n].obj = cowl_retain(opt);

    return o;
}

CowlAny *cowl_get_impl_annot(CowlObjectType type, CowlAny *fields[], CowlVector *annot) {
    if (annot && !cowl_vector_count(annot)) annot = NULL;
    return cowl_get_impl(type, fields, annot);
}

CowlAny *cowl_get_impl_uint(CowlObjectType type, CowlAny *fields[], ulib_uint val, CowlAny *opt) {
    ulib_byte const n = type_field_count(type);
    ulib_byte data_size = opt ? n + 2 : n + 1;
    CowlComposite *obj = ulib_malloc(sizeof(*obj) + data_size * sizeof(*obj->fields));
    if (!obj) return NULL;

    obj->super = COWL_OBJECT_BIT_INIT(type, opt);
    for (ulib_byte i = 0; i < n; ++i) {
        obj->fields[i].obj = cowl_retain(fields[i]);
    }

    if (opt) {
        obj->fields[n].obj = cowl_retain(opt);
        obj->fields[n + 1].uint = val;
    } else {
        obj->fields[n].uint = val;
    }

    return obj;
}

void cowl_release_all_impl(CowlAny **objects) {
    while (*objects) {
        cowl_release(*(objects++));
    }
}

CowlAny **cowl_get_fields(CowlAny *object, unsigned *count) {
    *count = cowl_get_field_count(object);
    return (CowlAny **)((CowlComposite *)object)->fields;
}

unsigned cowl_get_field_count(CowlAny *object) {
    return type_field_count(cowl_get_type(object));
}

CowlAny *cowl_get_field(CowlAny *object, unsigned index) {
    return ((CowlComposite *)object)->fields[index].obj;
}

bool cowl_has_opt_field(CowlAny *object) {
    return cowl_object_bit_get(object);
}

CowlAny *cowl_get_opt_field(CowlAny *object) {
    if (!cowl_has_opt_field(object)) return NULL;
    return cowl_get_field(object, cowl_get_field_count(object));
}

ulib_uint cowl_get_uint_field(CowlAny *object) {
    unsigned idx = cowl_get_field_count(object);
    if (cowl_has_opt_field(object)) ++idx;
    return ((CowlComposite *)object)->fields[idx].uint;
}
