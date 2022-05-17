/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_stream.h"
#include "cowl_private.h"

#define UINT_MAX_DIGITS 20

// Misc

ustream_ret cowl_stream_write_object(UOStream *s, void *obj) {
    switch (cowl_get_type(obj)) {
        case COWL_OT_STRING: return cowl_stream_write_string(s, obj);
        case COWL_OT_VECTOR: return cowl_stream_write_vector(s, obj);
        case COWL_OT_SET: return cowl_stream_write_set(s, obj);
        case COWL_OT_IRI: return cowl_stream_write_iri(s, obj);
        case COWL_OT_LITERAL: return cowl_stream_write_literal(s, obj);
        case COWL_OT_FACET_RESTR: return cowl_stream_write_facet_restr(s, obj);
        case COWL_OT_ANNOTATION: return cowl_stream_write_annotation(s, obj);
        case COWL_OT_ANNOT_PROP: return cowl_stream_write_annot_prop(s, obj);
        case COWL_OT_A_DECL: return cowl_stream_write_decl_axiom(s, obj);
        case COWL_OT_A_DATATYPE_DEF: return cowl_stream_write_datatype_def_axiom(s, obj);
        case COWL_OT_A_SUB_CLASS: return cowl_stream_write_sub_cls_axiom(s, obj);
        case COWL_OT_A_EQUIV_CLASSES:
        case COWL_OT_A_DISJ_CLASSES: return cowl_stream_write_nary_cls_axiom(s, obj);
        case COWL_OT_A_DISJ_UNION: return cowl_stream_write_disj_union_axiom(s, obj);
        case COWL_OT_A_CLASS_ASSERT: return cowl_stream_write_cls_assert(s, obj);
        case COWL_OT_A_SAME_IND:
        case COWL_OT_A_DIFF_IND: return cowl_stream_write_nary_ind_axiom(s, obj);
        case COWL_OT_A_OBJ_PROP_ASSERT:
        case COWL_OT_A_NEG_OBJ_PROP_ASSERT: return cowl_stream_write_obj_prop_assert(s, obj);
        case COWL_OT_A_DATA_PROP_ASSERT:
        case COWL_OT_A_NEG_DATA_PROP_ASSERT: return cowl_stream_write_data_prop_assert(s, obj);
        case COWL_OT_A_SUB_OBJ_PROP: return cowl_stream_write_sub_obj_prop_axiom(s, obj);
        case COWL_OT_A_SUB_OBJ_PROP_CHAIN: return cowl_stream_write_sub_obj_prop_chain_axiom(s, obj);
        case COWL_OT_A_INV_OBJ_PROP: return cowl_stream_write_inv_obj_prop_axiom(s, obj);
        case COWL_OT_A_EQUIV_OBJ_PROP:
        case COWL_OT_A_DISJ_OBJ_PROP: return cowl_stream_write_nary_obj_prop_axiom(s, obj);
        case COWL_OT_A_FUNC_OBJ_PROP:
        case COWL_OT_A_INV_FUNC_OBJ_PROP:
        case COWL_OT_A_SYMM_OBJ_PROP:
        case COWL_OT_A_ASYMM_OBJ_PROP:
        case COWL_OT_A_REFL_OBJ_PROP:
        case COWL_OT_A_IRREFL_OBJ_PROP:
        case COWL_OT_A_TRANS_OBJ_PROP: return cowl_stream_write_obj_prop_char(s, obj);
        case COWL_OT_A_OBJ_PROP_DOMAIN: return cowl_stream_write_obj_prop_domain(s, obj);
        case COWL_OT_A_OBJ_PROP_RANGE: return cowl_stream_write_obj_prop_range(s, obj);
        case COWL_OT_A_SUB_DATA_PROP: return cowl_stream_write_sub_data_prop_axiom(s, obj);
        case COWL_OT_A_EQUIV_DATA_PROP:
        case COWL_OT_A_DISJ_DATA_PROP: return cowl_stream_write_nary_data_prop_axiom(s, obj);
        case COWL_OT_A_FUNC_DATA_PROP: return cowl_stream_write_func_data_prop_axiom(s, obj);
        case COWL_OT_A_DATA_PROP_DOMAIN: return cowl_stream_write_data_prop_domain(s, obj);
        case COWL_OT_A_DATA_PROP_RANGE: return cowl_stream_write_data_prop_range(s, obj);
        case COWL_OT_A_HAS_KEY: return cowl_stream_write_has_key_axiom(s, obj);
        case COWL_OT_A_ANNOT_ASSERT: return cowl_stream_write_annot_assert(s, obj);
        case COWL_OT_A_SUB_ANNOT_PROP: return cowl_stream_write_sub_annot_prop_axiom(s, obj);
        case COWL_OT_A_ANNOT_PROP_DOMAIN: return cowl_stream_write_annot_prop_domain_axiom(s, obj);
        case COWL_OT_A_ANNOT_PROP_RANGE: return cowl_stream_write_annot_prop_range_axiom(s, obj);
        case COWL_OT_CE_CLASS: return cowl_stream_write_class(s, obj);
        case COWL_OT_CE_OBJ_SOME:
        case COWL_OT_CE_OBJ_ALL: return cowl_stream_write_obj_quant(s, obj);
        case COWL_OT_CE_OBJ_MIN_CARD:
        case COWL_OT_CE_OBJ_MAX_CARD:
        case COWL_OT_CE_OBJ_EXACT_CARD: return cowl_stream_write_obj_card(s, obj);
        case COWL_OT_CE_OBJ_HAS_VALUE: return cowl_stream_write_obj_has_value(s, obj);
        case COWL_OT_CE_OBJ_HAS_SELF: return cowl_stream_write_obj_has_self(s, obj);
        case COWL_OT_CE_DATA_SOME:
        case COWL_OT_CE_DATA_ALL: return cowl_stream_write_data_quant(s, obj);
        case COWL_OT_CE_DATA_MIN_CARD:
        case COWL_OT_CE_DATA_MAX_CARD:
        case COWL_OT_CE_DATA_EXACT_CARD: return cowl_stream_write_data_card(s, obj);
        case COWL_OT_CE_DATA_HAS_VALUE: return cowl_stream_write_data_has_value(s, obj);
        case COWL_OT_CE_OBJ_INTERSECT:
        case COWL_OT_CE_OBJ_UNION: return cowl_stream_write_nary_bool(s, obj);
        case COWL_OT_CE_OBJ_COMPL: return cowl_stream_write_obj_compl(s, obj);
        case COWL_OT_CE_OBJ_ONE_OF: return cowl_stream_write_obj_one_of(s, obj);
        case COWL_OT_DPE_DATA_PROP: return cowl_stream_write_data_prop(s, obj);
        case COWL_OT_DR_DATATYPE: return cowl_stream_write_datatype(s, obj);
        case COWL_OT_DR_DATATYPE_RESTR: return cowl_stream_write_datatype_restr(s, obj);
        case COWL_OT_DR_DATA_INTERSECT:
        case COWL_OT_DR_DATA_UNION: return cowl_stream_write_nary_data(s, obj);
        case COWL_OT_DR_DATA_COMPL: return cowl_stream_write_data_compl(s, obj);
        case COWL_OT_DR_DATA_ONE_OF: return cowl_stream_write_data_one_of(s, obj);
        case COWL_OT_I_NAMED: return cowl_stream_write_named_ind(s, obj);
        case COWL_OT_I_ANONYMOUS: return cowl_stream_write_anon_ind(s, obj);
        case COWL_OT_OPE_OBJ_PROP: return cowl_stream_write_obj_prop(s, obj);
        case COWL_OT_OPE_INV_OBJ_PROP: return cowl_stream_write_inv_obj_prop(s, obj);
        default: return cowl_stream_write_object_debug(s, obj);
    }
}

static ustream_ret cowl_stream_write_object_type(UOStream *s, CowlObjectType type) {
    #define GEN_OT_STRING(T) case COWL_OT_##T: return cowl_stream_write_static(s, #T)

    switch (type) {
        GEN_OT_STRING(STRING);
        GEN_OT_STRING(VECTOR);
        GEN_OT_STRING(SET);
        GEN_OT_STRING(IRI);
        GEN_OT_STRING(LITERAL);
        GEN_OT_STRING(FACET_RESTR);
        GEN_OT_STRING(ONTOLOGY);
        GEN_OT_STRING(MANAGER);
        GEN_OT_STRING(ANNOTATION);
        GEN_OT_STRING(ANNOT_PROP);
        GEN_OT_STRING(A_DECL);
        GEN_OT_STRING(A_DATATYPE_DEF);
        GEN_OT_STRING(A_SUB_CLASS);
        GEN_OT_STRING(A_EQUIV_CLASSES);
        GEN_OT_STRING(A_DISJ_CLASSES);
        GEN_OT_STRING(A_DISJ_UNION);
        GEN_OT_STRING(A_CLASS_ASSERT);
        GEN_OT_STRING(A_SAME_IND);
        GEN_OT_STRING(A_DIFF_IND);
        GEN_OT_STRING(A_OBJ_PROP_ASSERT);
        GEN_OT_STRING(A_NEG_OBJ_PROP_ASSERT);
        GEN_OT_STRING(A_DATA_PROP_ASSERT);
        GEN_OT_STRING(A_NEG_DATA_PROP_ASSERT);
        GEN_OT_STRING(A_SUB_OBJ_PROP);
        GEN_OT_STRING(A_SUB_OBJ_PROP_CHAIN);
        GEN_OT_STRING(A_INV_OBJ_PROP);
        GEN_OT_STRING(A_EQUIV_OBJ_PROP);
        GEN_OT_STRING(A_DISJ_OBJ_PROP);
        GEN_OT_STRING(A_FUNC_OBJ_PROP);
        GEN_OT_STRING(A_INV_FUNC_OBJ_PROP);
        GEN_OT_STRING(A_SYMM_OBJ_PROP);
        GEN_OT_STRING(A_ASYMM_OBJ_PROP);
        GEN_OT_STRING(A_TRANS_OBJ_PROP);
        GEN_OT_STRING(A_REFL_OBJ_PROP);
        GEN_OT_STRING(A_IRREFL_OBJ_PROP);
        GEN_OT_STRING(A_OBJ_PROP_DOMAIN);
        GEN_OT_STRING(A_OBJ_PROP_RANGE);
        GEN_OT_STRING(A_SUB_DATA_PROP);
        GEN_OT_STRING(A_EQUIV_DATA_PROP);
        GEN_OT_STRING(A_DISJ_DATA_PROP);
        GEN_OT_STRING(A_FUNC_DATA_PROP);
        GEN_OT_STRING(A_DATA_PROP_DOMAIN);
        GEN_OT_STRING(A_DATA_PROP_RANGE);
        GEN_OT_STRING(A_HAS_KEY);
        GEN_OT_STRING(A_ANNOT_ASSERT);
        GEN_OT_STRING(A_SUB_ANNOT_PROP);
        GEN_OT_STRING(A_ANNOT_PROP_DOMAIN);
        GEN_OT_STRING(A_ANNOT_PROP_RANGE);
        GEN_OT_STRING(CE_CLASS);
        GEN_OT_STRING(CE_OBJ_SOME);
        GEN_OT_STRING(CE_OBJ_ALL);
        GEN_OT_STRING(CE_OBJ_MIN_CARD);
        GEN_OT_STRING(CE_OBJ_MAX_CARD);
        GEN_OT_STRING(CE_OBJ_EXACT_CARD);
        GEN_OT_STRING(CE_OBJ_HAS_VALUE);
        GEN_OT_STRING(CE_OBJ_HAS_SELF);
        GEN_OT_STRING(CE_DATA_SOME);
        GEN_OT_STRING(CE_DATA_ALL);
        GEN_OT_STRING(CE_DATA_MIN_CARD);
        GEN_OT_STRING(CE_DATA_MAX_CARD);
        GEN_OT_STRING(CE_DATA_EXACT_CARD);
        GEN_OT_STRING(CE_DATA_HAS_VALUE);
        GEN_OT_STRING(CE_OBJ_INTERSECT);
        GEN_OT_STRING(CE_OBJ_UNION);
        GEN_OT_STRING(CE_OBJ_COMPL);
        GEN_OT_STRING(CE_OBJ_ONE_OF);
        GEN_OT_STRING(DPE_DATA_PROP);
        GEN_OT_STRING(DR_DATATYPE);
        GEN_OT_STRING(DR_DATATYPE_RESTR);
        GEN_OT_STRING(DR_DATA_INTERSECT);
        GEN_OT_STRING(DR_DATA_UNION);
        GEN_OT_STRING(DR_DATA_COMPL);
        GEN_OT_STRING(DR_DATA_ONE_OF);
        GEN_OT_STRING(I_ANONYMOUS);
        GEN_OT_STRING(I_NAMED);
        GEN_OT_STRING(OPE_OBJ_PROP);
        GEN_OT_STRING(OPE_INV_OBJ_PROP);
        default: {
            cowl_stream_write_static(s, "UNKNOWN(");
            cowl_stream_write_uint(s, type);
            cowl_stream_write_static(s, ")");
            break;
        }
    }
    return s->state;
}

ustream_ret cowl_stream_write_object_debug(UOStream *s, CowlObject *obj) {
    uostream_writef(s, NULL, "<CowlObject %p, type ", obj);
    cowl_stream_write_object_type(s, cowl_get_type(obj));
    cowl_stream_write_static(s, ", ref ");
    cowl_stream_write_uint(s, cowl_object_get_ref(obj));
    cowl_stream_write_static(s, ">");
    return s->state;
}

ustream_ret cowl_stream_write_string(UOStream *s, CowlString *string) {
    return uostream_write_string(s, &string->raw_string, NULL);
}

ustream_ret cowl_stream_write_ustring(UOStream *s, UString string) {
    return uostream_write_string(s, &string, NULL);
}

ustream_ret cowl_stream_write_iri(UOStream *s, CowlIRI *iri) {
    cowl_stream_write_static(s, "<");
    cowl_stream_write_iri_no_brackets(s, iri);
    cowl_stream_write_static(s, ">");
    return s->state;
}

ustream_ret cowl_stream_write_iri_no_brackets(UOStream *s, CowlIRI *iri) {
    cowl_stream_write_string(s, cowl_iri_get_ns(iri));
    cowl_stream_write_string(s, cowl_iri_get_rem(iri));
    return s->state;
}

static bool imports_writer(void *ctx, void *import) {
    UOStream *s = ctx;
    CowlIRI *iri = cowl_ontology_get_id(import).ontology_iri;
    cowl_stream_write_static(s, "\n");
    cowl_stream_write_static(s, "Imports");
    cowl_stream_write_static(s, "(");

    if (iri) {
        cowl_stream_write_iri(s, iri);
    } else {
        uostream_writef(s, NULL, "anon(%p)", import);
    }

    cowl_stream_write_static(s, ")");
    return s->state == USTREAM_OK;
}

static bool entity_writer(void *ctx, void *obj) {
    UOStream *s = ctx;
    cowl_stream_write_entity(s, obj);
    cowl_stream_write_static(s, "\n");
    return s->state == USTREAM_OK;
}

static bool axiom_writer(void *ctx, void *obj) {
    UOStream *s = ctx;
    cowl_stream_write_axiom(s, obj);
    cowl_stream_write_static(s, "\n");
    return s->state == USTREAM_OK;
}

ustream_ret cowl_stream_write_ontology(UOStream *s, CowlOntology *onto) {
    cowl_stream_write_static(s, "Ontology");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_ontology_id(s, &onto->id);

    CowlIterator iter = cowl_iterator_init(s, imports_writer);
    cowl_ontology_iterate_imports(onto, &iter);
    if (s->state) return s->state;

    CowlVector *annotations = cowl_ontology_get_annot(onto);
    uvec_foreach(CowlObjectPtr, cowl_vector_get_data(annotations), annot) {
        cowl_stream_write_static(s, "\n");
        cowl_stream_write_annotation(s, *annot.item);
    }

    cowl_stream_write_static(s, ")");
    cowl_stream_write_static(s, "\n");

    iter = cowl_iterator_init(s, entity_writer);
    cowl_ontology_iterate_primitives(onto, COWL_PF_ENTITY, &iter);

    iter = cowl_iterator_init(s, axiom_writer);
    cowl_ontology_iterate_axioms(onto, &iter);

    return s->state;
}

ustream_ret cowl_stream_write_ontology_id(UOStream *s, CowlOntologyId *id) {
    if (id->ontology_iri) cowl_stream_write_iri(s, id->ontology_iri);

    if (id->version_iri) {
        if (id->ontology_iri) cowl_stream_write_static(s, " ");
        cowl_stream_write_iri(s, id->version_iri);
    }

    return s->state;
}

ustream_ret cowl_stream_write_literal(UOStream *s, CowlLiteral *literal) {
    cowl_stream_write_static(s, "\"");
    cowl_stream_write_string(s, literal->value);
    cowl_stream_write_static(s, "\"");

    if (cowl_string_get_length(literal->lang)) {
        cowl_stream_write_static(s, "@");
        cowl_stream_write_string(s, literal->lang);
    }

    cowl_stream_write_static(s, "^^");
    cowl_stream_write_iri_no_brackets(s, cowl_datatype_get_iri(literal->dt));

    return s->state;
}

ustream_ret cowl_stream_write_facet_restr(UOStream *s, CowlFacetRestr *restr) {
    CowlIRI *iri = cowl_facet_get_iri(restr->facet);
    cowl_stream_write_iri(s, iri);
    cowl_iri_release(iri);

    cowl_stream_write_static(s, " ");
    cowl_stream_write_literal(s, restr->value);

    return s->state;
}

ustream_ret cowl_stream_write_node_id(UOStream *s, CowlNodeId id) {
    cowl_stream_write_static(s, "_:id");
    cowl_stream_write_uint(s, id);
    return s->state;
}

ustream_ret cowl_stream_write_annotation(UOStream *s, CowlAnnotation *annotation) {
    cowl_stream_write_static(s, "Annotation");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_vector(s, annotation->annot);
    cowl_stream_write_annot_prop(s, annotation->prop);
    cowl_stream_write_static(s, " ");
    cowl_stream_write_annot_value(s, annotation->value);
    cowl_stream_write_static(s, ")");
    return s->state;
}

ustream_ret cowl_stream_write_annot_value(UOStream *s, CowlAnnotValue *value) {
    return cowl_stream_write_object(s, value);
}

ustream_ret cowl_stream_write_uint(UOStream *s, uint64_t uint) {
    char buf[UINT_MAX_DIGITS + 1];
    size_t len = cowl_str_from_uint(uint, buf);
    return uostream_write(s, buf, len, NULL);
}

ustream_ret cowl_stream_write_error(UOStream *s, CowlError const *error) {
    cowl_stream_write_static(s, "Error ");
    cowl_stream_write_uint(s, error->code);

    if (error->origin) {
        cowl_stream_write_static(s, " - triggered by ");

        if (cowl_get_type(error->origin) == COWL_OT_MANAGER) {
            CowlParser parser = ((CowlManager *)error->origin)->parser;
            char const *name = parser.name ? parser.name : "unnamed";
            uostream_write(s, name, strlen(name), NULL);
            cowl_stream_write_static(s, " parser ");
        } else {
            cowl_stream_write_object_debug(s, error->origin);
        }
    }

    CowlErrorLoc loc = error->location;

    if (loc.iri || loc.source || loc.line) {
        cowl_stream_write_static(s, " (");

        if (loc.iri) {
            cowl_stream_write_iri_no_brackets(s, loc.iri);
            cowl_stream_write_static(s, ", ");
        }

        if (loc.source) {
            cowl_stream_write_string(s, loc.source);
            cowl_stream_write_static(s, ", ");
        }

        if (loc.line) {
            cowl_stream_write_static(s, "line ");
            cowl_stream_write_uint(s, loc.line);
        }

        cowl_stream_write_static(s, ")");
    }

    cowl_stream_write_static(s, " - ");
    cowl_stream_write_ustring(s, cowl_ret_to_ustring(error->code));

    if (error->description) {
        cowl_stream_write_static(s, ": ");
        cowl_stream_write_string(s, error->description);
    }

    return s->state;
}

// Entities and Primitives

ustream_ret cowl_stream_write_entity(UOStream *s, CowlEntity *entity) {
    return cowl_stream_write_object(s, entity);
}

ustream_ret cowl_stream_write_primitive(UOStream *s, CowlPrimitive *primitive) {
    return cowl_stream_write_object(s, primitive);
}

ustream_ret cowl_stream_write_class(UOStream *s, CowlClass *cls) {
    cowl_stream_write_static(s, "Class");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_iri(s, cowl_class_get_iri(cls));
    cowl_stream_write_static(s, ")");
    return s->state;
}

ustream_ret cowl_stream_write_datatype(UOStream *s, CowlDatatype *dt) {
    cowl_stream_write_static(s, "Datatype");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_iri(s, dt->iri);
    cowl_stream_write_static(s, ")");
    return s->state;
}

ustream_ret cowl_stream_write_obj_prop(UOStream *s, CowlObjProp *prop) {
    cowl_stream_write_static(s, "Object");
    cowl_stream_write_static(s, "Property");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_iri(s, prop->iri);
    cowl_stream_write_static(s, ")");
    return s->state;
}

ustream_ret cowl_stream_write_data_prop(UOStream *s, CowlDataProp *prop) {
    cowl_stream_write_static(s, "Data");
    cowl_stream_write_static(s, "Property");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_iri(s, prop->iri);
    cowl_stream_write_static(s, ")");
    return s->state;
}

ustream_ret cowl_stream_write_annot_prop(UOStream *s, CowlAnnotProp *prop) {
    cowl_stream_write_static(s, "Annotation");
    cowl_stream_write_static(s, "Property");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_iri(s, prop->iri);
    cowl_stream_write_static(s, ")");
    return s->state;
}

ustream_ret cowl_stream_write_named_ind(UOStream *s, CowlNamedInd *ind) {
    cowl_stream_write_static(s, "Named");
    cowl_stream_write_static(s, "Individual");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_iri(s, ind->iri);
    cowl_stream_write_static(s, ")");
    return s->state;
}

ustream_ret cowl_stream_write_anon_ind(UOStream *s, CowlAnonInd *ind) {
    cowl_stream_write_static(s, "Anonymous");
    cowl_stream_write_static(s, "Individual");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_node_id(s, cowl_anon_ind_get_id(ind));
    cowl_stream_write_static(s, ")");
    return s->state;
}

ustream_ret cowl_stream_write_individual(UOStream *s, CowlIndividual *ind) {
    return cowl_stream_write_object(s, ind);
}

// Object property expressions

ustream_ret cowl_stream_write_obj_prop_exp(UOStream *s, CowlObjPropExp *exp) {
    return cowl_stream_write_object(s, exp);
}

ustream_ret cowl_stream_write_inv_obj_prop(UOStream *s, CowlInvObjProp *prop) {
    cowl_stream_write_static(s, "Object");
    cowl_stream_write_static(s, "Inverse");
    cowl_stream_write_static(s, "Of");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_obj_prop(s, prop->prop);
    cowl_stream_write_static(s, ")");
    return s->state;
}

// Data property expressions

ustream_ret cowl_stream_write_data_prop_exp(UOStream *s, CowlDataPropExp *exp) {
    return cowl_stream_write_data_prop(s, (CowlDataProp *)exp);
}

// Class expressions

ustream_ret cowl_stream_write_cls_exp(UOStream *s, CowlClsExp *exp) {
    return cowl_stream_write_object(s, exp);
}

ustream_ret cowl_stream_write_obj_quant(UOStream *s, CowlObjQuant *restr) {
    cowl_stream_write_static(s, "Object");

    if (cowl_obj_quant_get_type(restr) == COWL_QT_SOME) {
        cowl_stream_write_static(s, "Some");
    } else {
        cowl_stream_write_static(s, "All");
    }

    cowl_stream_write_static(s, "ValuesFrom");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_obj_prop_exp(s, restr->prop);
    cowl_stream_write_static(s, " ");
    cowl_stream_write_cls_exp(s, restr->filler);
    cowl_stream_write_static(s, ")");

    return s->state;
}

ustream_ret cowl_stream_write_obj_card(UOStream *s, CowlObjCard *restr) {
    cowl_stream_write_static(s, "Object");

    switch (cowl_obj_card_get_type(restr)) {
        case COWL_CT_MIN: cowl_stream_write_static(s, "Min"); break;
        case COWL_CT_MAX: cowl_stream_write_static(s, "Max"); break;
        default: cowl_stream_write_static(s, "Exact"); break;
    }

    cowl_stream_write_static(s, "Cardinality");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_uint(s, restr->cardinality);
    cowl_stream_write_static(s, " ");
    cowl_stream_write_obj_prop_exp(s, restr->prop);

    if (restr->filler) {
        cowl_stream_write_static(s, " ");
        cowl_stream_write_cls_exp(s, restr->filler);
    }

    cowl_stream_write_static(s, ")");

    return s->state;
}

ustream_ret cowl_stream_write_obj_has_value(UOStream *s, CowlObjHasValue *restr) {
    cowl_stream_write_static(s, "Object");
    cowl_stream_write_static(s, "Has");
    cowl_stream_write_static(s, "Value");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_obj_prop_exp(s, restr->prop);
    cowl_stream_write_static(s, " ");
    cowl_stream_write_individual(s, restr->ind);
    cowl_stream_write_static(s, ")");
    return s->state;
}

ustream_ret cowl_stream_write_obj_has_self(UOStream *s, CowlObjHasSelf *restr) {
    cowl_stream_write_static(s, "Object");
    cowl_stream_write_static(s, "Has");
    cowl_stream_write_static(s, "Self");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_obj_prop_exp(s, restr->prop);
    cowl_stream_write_static(s, ")");
    return s->state;
}

ustream_ret cowl_stream_write_data_quant(UOStream *s, CowlDataQuant *restr) {
    cowl_stream_write_static(s, "Data");

    if (cowl_data_quant_get_type(restr) == COWL_QT_SOME) {
        cowl_stream_write_static(s, "Some");
    } else {
        cowl_stream_write_static(s, "All");
    }

    cowl_stream_write_static(s, "ValuesFrom");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_data_prop_exp(s, restr->prop);
    cowl_stream_write_static(s, " ");
    cowl_stream_write_data_range(s, restr->range);
    cowl_stream_write_static(s, ")");

    return s->state;
}

ustream_ret cowl_stream_write_data_card(UOStream *s, CowlDataCard *restr) {
    cowl_stream_write_static(s, "Data");

    switch (cowl_data_card_get_type(restr)) {
        case COWL_CT_MIN: cowl_stream_write_static(s, "Min"); break;
        case COWL_CT_MAX: cowl_stream_write_static(s, "Max"); break;
        default: cowl_stream_write_static(s, "Exact"); break;
    }

    cowl_stream_write_static(s, "Cardinality");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_uint(s, restr->cardinality);
    cowl_stream_write_static(s, " ");
    cowl_stream_write_data_prop_exp(s, restr->prop);

    if (restr->range) {
        cowl_stream_write_static(s, " ");
        cowl_stream_write_data_range(s, restr->range);
    }

    cowl_stream_write_static(s, ")");

    return s->state;
}

ustream_ret cowl_stream_write_data_has_value(UOStream *s, CowlDataHasValue *restr) {
    cowl_stream_write_static(s, "Data");
    cowl_stream_write_static(s, "Has");
    cowl_stream_write_static(s, "Value");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_data_prop_exp(s, restr->prop);
    cowl_stream_write_static(s, " ");
    cowl_stream_write_literal(s, restr->value);
    cowl_stream_write_static(s, ")");
    return s->state;
}

ustream_ret cowl_stream_write_nary_bool(UOStream *s, CowlNAryBool *exp) {
    cowl_stream_write_static(s, "Object");

    if (cowl_nary_bool_get_type(exp) == COWL_NT_INTERSECT) {
        cowl_stream_write_static(s, "Intersection");
    } else {
        cowl_stream_write_static(s, "Union");
    }

    cowl_stream_write_static(s, "Of");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_vector(s, exp->operands);
    cowl_stream_write_static(s, ")");

    return s->state;
}

ustream_ret cowl_stream_write_obj_compl(UOStream *s, CowlObjCompl *exp) {
    cowl_stream_write_static(s, "Object");
    cowl_stream_write_static(s, "Complement");
    cowl_stream_write_static(s, "Of");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_cls_exp(s, exp->operand);
    cowl_stream_write_static(s, ")");
    return s->state;
}

ustream_ret cowl_stream_write_obj_one_of(UOStream *s, CowlObjOneOf *restr) {
    cowl_stream_write_static(s, "Object");
    cowl_stream_write_static(s, "One");
    cowl_stream_write_static(s, "Of");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_vector(s, restr->inds);
    cowl_stream_write_static(s, ")");
    return s->state;
}

// Data ranges

ustream_ret cowl_stream_write_data_range(UOStream *s, CowlDataRange *range) {
    return cowl_stream_write_object(s, range);
}

ustream_ret cowl_stream_write_datatype_restr(UOStream *s, CowlDatatypeRestr *restr) {
    cowl_stream_write_static(s, "Datatype");
    cowl_stream_write_static(s, "Restriction");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_iri(s, restr->datatype->iri);
    cowl_stream_write_static(s, " ");
    cowl_stream_write_vector(s, restr->restrictions);
    cowl_stream_write_static(s, ")");
    return s->state;
}

ustream_ret cowl_stream_write_nary_data(UOStream *s, CowlNAryData *range) {
    cowl_stream_write_static(s, "Data");

    if (cowl_nary_data_get_type(range) == COWL_NT_INTERSECT) {
        cowl_stream_write_static(s, "Intersection");
    } else {
        cowl_stream_write_static(s, "Union");
    }

    cowl_stream_write_static(s, "Of");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_vector(s, range->operands);
    cowl_stream_write_static(s, ")");

    return s->state;
}

ustream_ret cowl_stream_write_data_compl(UOStream *s, CowlDataCompl *range) {
    cowl_stream_write_static(s, "Data");
    cowl_stream_write_static(s, "Complement");
    cowl_stream_write_static(s, "Of");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_data_range(s, range->operand);
    cowl_stream_write_static(s, ")");
    return s->state;
}

ustream_ret cowl_stream_write_data_one_of(UOStream *s, CowlDataOneOf *restr) {
    cowl_stream_write_static(s, "Data");
    cowl_stream_write_static(s, "One");
    cowl_stream_write_static(s, "Of");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_vector(s, restr->values);
    cowl_stream_write_static(s, ")");
    return s->state;
}

// Axioms

ustream_ret cowl_stream_write_axiom(UOStream *s, CowlAxiom *axiom) {
    return cowl_stream_write_object(s, axiom);
}

ustream_ret cowl_stream_write_decl_axiom(UOStream *s, CowlDeclAxiom *axiom) {
    cowl_stream_write_static(s, "Declaration");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_vector(s, cowl_axiom_get_annot(axiom));
    cowl_stream_write_entity(s, axiom->entity);
    cowl_stream_write_static(s, ")");
    return s->state;
}

ustream_ret cowl_stream_write_datatype_def_axiom(UOStream *s, CowlDatatypeDefAxiom *axiom) {
    cowl_stream_write_static(s, "Datatype");
    cowl_stream_write_static(s, "Definition");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_vector(s, cowl_axiom_get_annot(axiom));
    cowl_stream_write_entity(s, (CowlEntity *)axiom->datatype);
    cowl_stream_write_static(s, " ");
    cowl_stream_write_data_range(s, axiom->range);
    cowl_stream_write_static(s, ")");
    return s->state;
}

ustream_ret cowl_stream_write_sub_cls_axiom(UOStream *s, CowlSubClsAxiom *axiom) {
    cowl_stream_write_static(s, "Sub");
    cowl_stream_write_static(s, "Class");
    cowl_stream_write_static(s, "Of");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_vector(s, cowl_axiom_get_annot(axiom));
    cowl_stream_write_cls_exp(s, axiom->sub_class);
    cowl_stream_write_static(s, " ");
    cowl_stream_write_cls_exp(s, axiom->super_class);
    cowl_stream_write_static(s, ")");
    return s->state;
}

ustream_ret cowl_stream_write_nary_cls_axiom(UOStream *s, CowlNAryClsAxiom *axiom) {
    if (cowl_nary_cls_axiom_get_type(axiom) == COWL_NAT_EQUIV) {
        cowl_stream_write_static(s, "Equivalent");
    } else {
        cowl_stream_write_static(s, "Disjoint");
    }

    cowl_stream_write_static(s, "Class");
    cowl_stream_write_static(s, "es");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_vector(s, cowl_axiom_get_annot(axiom));
    cowl_stream_write_vector(s, axiom->classes);
    cowl_stream_write_static(s, ")");

    return s->state;
}

ustream_ret cowl_stream_write_disj_union_axiom(UOStream *s, CowlDisjUnionAxiom *axiom) {
    cowl_stream_write_static(s, "Disjoint");
    cowl_stream_write_static(s, "Union");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_vector(s, cowl_axiom_get_annot(axiom));
    cowl_stream_write_cls_exp(s, (CowlClsExp *)axiom->cls);
    cowl_stream_write_static(s, " ");
    cowl_stream_write_vector(s, axiom->disjoints);
    cowl_stream_write_static(s, ")");
    return s->state;
}

ustream_ret cowl_stream_write_cls_assert(UOStream *s, CowlClsAssertAxiom *axiom) {
    cowl_stream_write_static(s, "Class");
    cowl_stream_write_static(s, "Assertion");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_vector(s, cowl_axiom_get_annot(axiom));
    cowl_stream_write_individual(s, axiom->ind);
    cowl_stream_write_static(s, " ");
    cowl_stream_write_cls_exp(s, axiom->cls_exp);
    cowl_stream_write_static(s, ")");
    return s->state;
}

ustream_ret cowl_stream_write_nary_ind_axiom(UOStream *s, CowlNAryIndAxiom *axiom) {
    if (cowl_nary_ind_axiom_get_type(axiom) == COWL_NAT_SAME) {
        cowl_stream_write_static(s, "Same");
        cowl_stream_write_static(s, "Individual");
    } else {
        cowl_stream_write_static(s, "Different");
        cowl_stream_write_static(s, "Individual");
        cowl_stream_write_static(s, "s");
    }

    cowl_stream_write_static(s, "(");
    cowl_stream_write_vector(s, cowl_axiom_get_annot(axiom));
    cowl_stream_write_vector(s, axiom->individuals);
    cowl_stream_write_static(s, ")");

    return s->state;
}

ustream_ret cowl_stream_write_obj_prop_assert(UOStream *s, CowlObjPropAssertAxiom *axiom) {
    if (cowl_obj_prop_assert_axiom_is_negative(axiom)) {
        cowl_stream_write_static(s, "Negative");
    }

    cowl_stream_write_static(s, "Object");
    cowl_stream_write_static(s, "Property");
    cowl_stream_write_static(s, "Assertion");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_vector(s, cowl_axiom_get_annot(axiom));
    cowl_stream_write_individual(s, axiom->subject);
    cowl_stream_write_static(s, " ");
    cowl_stream_write_obj_prop_exp(s, axiom->prop_exp);
    cowl_stream_write_static(s, " ");
    cowl_stream_write_individual(s, axiom->object);
    cowl_stream_write_static(s, ")");

    return s->state;
}

ustream_ret cowl_stream_write_data_prop_assert(UOStream *s, CowlDataPropAssertAxiom *axiom) {
    if (cowl_data_prop_assert_axiom_is_negative(axiom)) {
        cowl_stream_write_static(s, "Negative");
    }

    cowl_stream_write_static(s, "Data");
    cowl_stream_write_static(s, "Property");
    cowl_stream_write_static(s, "Assertion");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_vector(s, cowl_axiom_get_annot(axiom));
    cowl_stream_write_individual(s, axiom->subject);
    cowl_stream_write_static(s, " ");
    cowl_stream_write_data_prop_exp(s, axiom->prop);
    cowl_stream_write_static(s, " ");
    cowl_stream_write_literal(s, axiom->object);
    cowl_stream_write_static(s, ")");

    return s->state;
}

ustream_ret cowl_stream_write_sub_obj_prop_axiom(UOStream *s, CowlSubObjPropAxiom *axiom) {
    cowl_stream_write_static(s, "Sub");
    cowl_stream_write_static(s, "Object");
    cowl_stream_write_static(s, "Property");
    cowl_stream_write_static(s, "Of");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_vector(s, cowl_axiom_get_annot(axiom));
    cowl_stream_write_obj_prop_exp(s, axiom->sub_prop);
    cowl_stream_write_static(s, " ");
    cowl_stream_write_obj_prop_exp(s, axiom->super_prop);
    cowl_stream_write_static(s, ")");
    return s->state;
}

ustream_ret cowl_stream_write_sub_obj_prop_chain_axiom(UOStream *s, CowlSubObjPropChainAxiom *axiom) {
    cowl_stream_write_static(s, "Sub");
    cowl_stream_write_static(s, "Object");
    cowl_stream_write_static(s, "Property");
    cowl_stream_write_static(s, "Of");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_static(s, "Object");
    cowl_stream_write_static(s, "Property");
    cowl_stream_write_static(s, "Chain");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_vector(s, cowl_axiom_get_annot(axiom));
    cowl_stream_write_vector(s, axiom->sub_props);
    cowl_stream_write_static(s, ") ");
    cowl_stream_write_obj_prop_exp(s, axiom->super_prop);
    cowl_stream_write_static(s, ")");
    return s->state;
}

ustream_ret cowl_stream_write_inv_obj_prop_axiom(UOStream *s, CowlInvObjPropAxiom *axiom) {
    cowl_stream_write_static(s, "Inverse");
    cowl_stream_write_static(s, "Object");
    cowl_stream_write_static(s, "Properties");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_vector(s, cowl_axiom_get_annot(axiom));
    cowl_stream_write_obj_prop_exp(s, axiom->first);
    cowl_stream_write_static(s, " ");
    cowl_stream_write_obj_prop_exp(s, axiom->second);
    cowl_stream_write_static(s, ")");
    return s->state;
}

ustream_ret cowl_stream_write_nary_obj_prop_axiom(UOStream *s, CowlNAryObjPropAxiom *axiom) {
    if (cowl_nary_obj_prop_axiom_get_type(axiom) == COWL_NAT_EQUIV) {
        cowl_stream_write_static(s, "Equivalent");
    } else {
        cowl_stream_write_static(s, "Disjoint");
    }

    cowl_stream_write_static(s, "Object");
    cowl_stream_write_static(s, "Properties");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_vector(s, cowl_axiom_get_annot(axiom));
    cowl_stream_write_vector(s, axiom->props);
    cowl_stream_write_static(s, ")");

    return s->state;
}

ustream_ret cowl_stream_write_obj_prop_char(UOStream *s, CowlObjPropCharAxiom *axiom) {
    CowlCharAxiomType const type = cowl_obj_prop_char_axiom_get_type(axiom);

    switch (type) {
        case COWL_CAT_FUNC:
            cowl_stream_write_static(s, "Functional");
            break;

        case COWL_CAT_INV_FUNC:
            cowl_stream_write_static(s, "Inverse");
            cowl_stream_write_static(s, "Functional");
            break;

        case COWL_CAT_SYMM:
            cowl_stream_write_static(s, "Symmetric");
            break;

        case COWL_CAT_ASYMM:
            cowl_stream_write_static(s, "Asymmetric");
            break;

        case COWL_CAT_REFL:
            cowl_stream_write_static(s, "Reflexive");
            break;

        case COWL_CAT_IRREFL:
            cowl_stream_write_static(s, "Irreflexive");
            break;

        default:
            cowl_stream_write_static(s, "Transitive");
            break;
    }

    cowl_stream_write_static(s, "Object");
    cowl_stream_write_static(s, "Property");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_vector(s, cowl_axiom_get_annot(axiom));
    cowl_stream_write_obj_prop_exp(s, axiom->prop_exp);
    cowl_stream_write_static(s, ")");

    return s->state;
}

ustream_ret cowl_stream_write_obj_prop_domain(UOStream *s, CowlObjPropDomainAxiom *axiom) {
    cowl_stream_write_static(s, "Object");
    cowl_stream_write_static(s, "Property");
    cowl_stream_write_static(s, "Domain");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_vector(s, cowl_axiom_get_annot(axiom));
    cowl_stream_write_obj_prop_exp(s, axiom->prop_exp);
    cowl_stream_write_static(s, " ");
    cowl_stream_write_cls_exp(s, axiom->domain);
    cowl_stream_write_static(s, ")");
    return s->state;
}

ustream_ret cowl_stream_write_obj_prop_range(UOStream *s, CowlObjPropRangeAxiom *axiom) {
    cowl_stream_write_static(s, "Object");
    cowl_stream_write_static(s, "Property");
    cowl_stream_write_static(s, "Range");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_vector(s, cowl_axiom_get_annot(axiom));
    cowl_stream_write_obj_prop_exp(s, axiom->prop_exp);
    cowl_stream_write_static(s, " ");
    cowl_stream_write_cls_exp(s, axiom->range);
    cowl_stream_write_static(s, ")");
    return s->state;
}

ustream_ret cowl_stream_write_sub_data_prop_axiom(UOStream *s, CowlSubDataPropAxiom *axiom) {
    cowl_stream_write_static(s, "Sub");
    cowl_stream_write_static(s, "Data");
    cowl_stream_write_static(s, "Property");
    cowl_stream_write_static(s, "Of");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_vector(s, cowl_axiom_get_annot(axiom));
    cowl_stream_write_data_prop_exp(s, axiom->sub_prop);
    cowl_stream_write_static(s, " ");
    cowl_stream_write_data_prop_exp(s, axiom->super_prop);
    cowl_stream_write_static(s, ")");
    return s->state;
}

ustream_ret cowl_stream_write_nary_data_prop_axiom(UOStream *s, CowlNAryDataPropAxiom *axiom) {
    if (cowl_nary_data_prop_axiom_get_type(axiom) == COWL_NAT_EQUIV) {
        cowl_stream_write_static(s, "Equivalent");
    } else {
        cowl_stream_write_static(s, "Disjoint");
    }

    cowl_stream_write_static(s, "Data");
    cowl_stream_write_static(s, "Properties");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_vector(s, cowl_axiom_get_annot(axiom));
    cowl_stream_write_vector(s, axiom->props);
    cowl_stream_write_static(s, ")");

    return s->state;
}

ustream_ret cowl_stream_write_func_data_prop_axiom(UOStream *s, CowlFuncDataPropAxiom *axiom) {
    cowl_stream_write_static(s, "Functional");
    cowl_stream_write_static(s, "Data");
    cowl_stream_write_static(s, "Property");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_vector(s, cowl_axiom_get_annot(axiom));
    cowl_stream_write_data_prop_exp(s, axiom->prop);
    cowl_stream_write_static(s, ")");
    return s->state;
}

ustream_ret cowl_stream_write_data_prop_domain(UOStream *s, CowlDataPropDomainAxiom *axiom) {
    cowl_stream_write_static(s, "Data");
    cowl_stream_write_static(s, "Property");
    cowl_stream_write_static(s, "Domain");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_vector(s, cowl_axiom_get_annot(axiom));
    cowl_stream_write_data_prop_exp(s, axiom->prop_exp);
    cowl_stream_write_static(s, " ");
    cowl_stream_write_cls_exp(s, axiom->domain);
    cowl_stream_write_static(s, ")");
    return s->state;
}

ustream_ret cowl_stream_write_data_prop_range(UOStream *s, CowlDataPropRangeAxiom *axiom) {
    cowl_stream_write_static(s, "Data");
    cowl_stream_write_static(s, "Property");
    cowl_stream_write_static(s, "Range");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_vector(s, cowl_axiom_get_annot(axiom));
    cowl_stream_write_data_prop_exp(s, axiom->prop_exp);
    cowl_stream_write_static(s, " ");
    cowl_stream_write_data_range(s, axiom->range);
    cowl_stream_write_static(s, ")");
    return s->state;
}

ustream_ret cowl_stream_write_has_key_axiom(UOStream *s, CowlHasKeyAxiom *axiom) {
    cowl_stream_write_static(s, "Has");
    cowl_stream_write_static(s, "Key");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_vector(s, cowl_axiom_get_annot(axiom));
    cowl_stream_write_cls_exp(s, axiom->cls_exp);
    cowl_stream_write_static(s, " ");
    cowl_stream_write_vector(s, axiom->obj_props);
    cowl_stream_write_static(s, " ");
    cowl_stream_write_vector(s, axiom->data_props);
    cowl_stream_write_static(s, ")");
    return s->state;
}

ustream_ret cowl_stream_write_annot_assert(UOStream *s, CowlAnnotAssertAxiom *axiom) {
    cowl_stream_write_static(s, "Annotation");
    cowl_stream_write_static(s, "Assertion");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_vector(s, cowl_axiom_get_annot(axiom));
    cowl_stream_write_annot_value(s, axiom->subject);
    cowl_stream_write_static(s, " ");
    cowl_stream_write_annot_prop(s, axiom->prop);
    cowl_stream_write_static(s, " ");
    cowl_stream_write_annot_value(s, axiom->value);
    cowl_stream_write_static(s, ")");
    return s->state;
}

ustream_ret cowl_stream_write_sub_annot_prop_axiom(UOStream *s, CowlSubAnnotPropAxiom *axiom) {
    cowl_stream_write_static(s, "Sub");
    cowl_stream_write_static(s, "Annotation");
    cowl_stream_write_static(s, "Property");
    cowl_stream_write_static(s, "Of");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_vector(s, cowl_axiom_get_annot(axiom));
    cowl_stream_write_annot_prop(s, axiom->sub_prop);
    cowl_stream_write_static(s, " ");
    cowl_stream_write_annot_prop(s, axiom->super_prop);
    cowl_stream_write_static(s, ")");
    return s->state;
}

ustream_ret cowl_stream_write_annot_prop_domain_axiom(UOStream *s, CowlAnnotPropDomainAxiom *axiom) {
    cowl_stream_write_static(s, "Annotation");
    cowl_stream_write_static(s, "Property");
    cowl_stream_write_static(s, "Domain");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_vector(s, cowl_axiom_get_annot(axiom));
    cowl_stream_write_annot_prop(s, axiom->prop);
    cowl_stream_write_static(s, " ");
    cowl_stream_write_iri(s, axiom->domain);
    cowl_stream_write_static(s, ")");
    return s->state;
}

ustream_ret cowl_stream_write_annot_prop_range_axiom(UOStream *s, CowlAnnotPropRangeAxiom *axiom) {
    cowl_stream_write_static(s, "Annotation");
    cowl_stream_write_static(s, "Property");
    cowl_stream_write_static(s, "Range");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_vector(s, cowl_axiom_get_annot(axiom));
    cowl_stream_write_annot_prop(s, axiom->prop);
    cowl_stream_write_static(s, " ");
    cowl_stream_write_iri(s, axiom->range);
    cowl_stream_write_static(s, ")");
    return s->state;
}

// Collections

ustream_ret cowl_stream_write_set(UOStream *s, CowlSet *set) {
    if (!set) return s->state;
    UHash(CowlObjectTable) const *data = cowl_set_get_data(set);
    ulib_uint current = 0, last = uhash_count(CowlObjectTable, data) - 1;

    uhash_foreach(CowlObjectTable, data, obj) {
        cowl_stream_write_object(s, *obj.key);
        if (current++ < last) cowl_stream_write_static(s, " ");
    }

    return s->state;
}

ustream_ret cowl_stream_write_vector(UOStream *s, CowlVector *vector) {
    if (!vector) return s->state;
    UVec(CowlObjectPtr) const *vec = cowl_vector_get_data(vector);
    ulib_uint last = uvec_count(CowlObjectPtr, vec);

    uvec_foreach(CowlObjectPtr, vec, obj) {
        cowl_stream_write_object(s, *obj.item);
        if (obj.i < last) cowl_stream_write_static(s, " ");
    }

    return s->state;
}
