/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_anon_ind.h"
#include "cowl_data_quant.h"
#include "cowl_datatype.h"
#include "cowl_decl_axiom.h"
#include "cowl_has_key_axiom.h"
#include "cowl_iri.h"
#include "cowl_literal.h"
#include "cowl_obj_quant.h"
#include "cowl_object_private.h"
#include "cowl_ontology.h"
#include "cowl_rdf_vocab.h"
#include "cowl_sub_obj_prop_axiom.h"
#include "cowl_sym_table.h"
#include "cowl_table.h"
#include "cowl_writer.h"
#include "cowl_xsd_vocab.h"

static ustream_ret cowl_func_write_obj(UOStream *s, CowlAny *obj, CowlSymTable *st);
static ustream_ret cowl_func_write_onto(UOStream *s, CowlOntology *onto);

static cowl_ret cowl_func_write(UOStream *stream, CowlAny *object) {
    return cowl_ret_from_ustream(cowl_func_write_obj(stream, object, NULL));
}

static cowl_ret
cowl_func_write_ontology(cowl_unused void *state, UOStream *stream, CowlOntology *onto) {
    return cowl_ret_from_ustream(cowl_func_write_onto(stream, onto));
}

static CowlWriter const cowl_func_writer = {
    .name = "functional",
    .write_ontology = cowl_func_write_ontology,
    .write = cowl_func_write,
};

CowlWriter cowl_writer_functional(void) {
    return cowl_func_writer;
}

static ustream_ret
cowl_func_write_fields(UOStream *s, CowlObjectType type, CowlAny *obj, CowlSymTable *st) {
    ulib_byte count = composite_fields[type];
    cowl_func_write_obj(s, cowl_get_field(obj, 0), st);
    for (ulib_byte i = 1; i < count; ++i) {
        cowl_write_static(s, " ");
        cowl_func_write_obj(s, cowl_get_field(obj, i), st);
    }
    return s->state;
}

static ustream_ret
cowl_func_write_fields_opt(UOStream *s, CowlObjectType type, CowlAny *obj, CowlSymTable *st) {
    cowl_func_write_fields(s, type, obj, st);
    CowlAny *opt = cowl_get_opt_field(obj);

    if (opt) {
        cowl_write_static(s, " ");
        cowl_func_write_obj(s, opt, st);
    }

    return s->state;
}

static ustream_ret
cowl_func_write_opt_fields(UOStream *s, CowlObjectType type, CowlAny *obj, CowlSymTable *st) {
    CowlAny *opt = cowl_get_opt_field(obj);

    if (opt) {
        cowl_func_write_obj(s, opt, st);
        cowl_write_static(s, " ");
    }

    cowl_func_write_fields(s, type, obj, st);

    return s->state;
}

static ustream_ret cowl_func_write_construct(UOStream *s, CowlAny *obj, CowlSymTable *st) {
    CowlObjectType type = cowl_get_type(obj);
    cowl_write_object_type(s, type);
    cowl_write_static(s, "(");
    cowl_func_write_fields_opt(s, type, obj, st);
    cowl_write_static(s, ")");
    return s->state;
}

static ustream_ret cowl_func_write_construct_uint(UOStream *s, CowlAny *obj, CowlSymTable *st) {
    CowlObjectType type = cowl_get_type(obj);
    cowl_write_object_type(s, type);
    cowl_write_static(s, "(");
    cowl_write_uint(s, cowl_get_uint_field(obj));
    cowl_write_static(s, " ");
    cowl_func_write_fields_opt(s, type, obj, st);
    cowl_write_static(s, ")");
    return s->state;
}

static ustream_ret cowl_func_write_annot_construct(UOStream *s, CowlAny *obj, CowlSymTable *st) {
    CowlObjectType type = cowl_get_type(obj);
    cowl_write_object_type(s, type);
    cowl_write_static(s, "(");
    cowl_func_write_opt_fields(s, type, obj, st);
    cowl_write_static(s, ")");
    return s->state;
}

static ustream_ret cowl_func_write_vector(UOStream *s, CowlVector *vec, CowlSymTable *st) {
    if (!vec) return s->state;
    ulib_uint last = cowl_vector_count(vec) - 1;

    cowl_vector_foreach (vec, obj) {
        cowl_func_write_obj(s, *obj.item, st);
        if (obj.i < last) cowl_write_static(s, " ");
    }

    return s->state;
}

static ustream_ret cowl_func_write_table(UOStream *s, CowlTable *table, CowlSymTable *st) {
    if (!table) return s->state;
    ulib_uint current = 0, last = cowl_table_count(table) - 1;

    cowl_table_foreach (table, obj) {
        cowl_func_write_obj(s, *obj.key, st);
        if (obj.val && *obj.val) {
            cowl_write_static(s, ":");
            cowl_func_write_obj(s, *obj.val, st);
        }
        if (current++ < last) cowl_write_static(s, " ");
    }

    return s->state;
}

static ustream_ret cowl_func_write_full_iri(UOStream *stream, CowlIRI *iri) {
    cowl_write_static(stream, "<");
    cowl_write_iri(stream, iri);
    cowl_write_static(stream, ">");
    return stream->state;
}

static ustream_ret cowl_func_write_short_iri(UOStream *stream, CowlString *pfx, CowlString *rem) {
    cowl_write_string(stream, pfx);
    cowl_write_static(stream, ":");
    cowl_write_string(stream, rem);
    return stream->state;
}

static ustream_ret cowl_func_write_iri(UOStream *stream, CowlIRI *iri, CowlSymTable *st) {
    if (!st) return cowl_write_iri(stream, iri);

    CowlString *pfx;
    if (cowl_iri_has_rem(iri) && (pfx = cowl_sym_table_get_prefix(st, cowl_iri_get_ns(iri)))) {
        return cowl_func_write_short_iri(stream, pfx, cowl_iri_get_rem(iri));
    }

    return cowl_func_write_full_iri(stream, iri);
}

static ustream_ret cowl_func_write_literal(UOStream *s, CowlLiteral *literal, CowlSymTable *st) {
    cowl_write_static(s, "\"");
    cowl_write_string(s, cowl_literal_get_value(literal));
    cowl_write_static(s, "\"");

    CowlDatatype *dt = cowl_literal_get_datatype(literal);
    if (cowl_datatype_equals(dt, cowl_rdf_vocab()->dt.lang_string)) {
        CowlString *lang = cowl_literal_get_lang(literal);
        cowl_write_static(s, "@");
        cowl_write_string(s, lang);
    } else if (!cowl_datatype_equals(dt, cowl_xsd_vocab()->dt.string)) {
        cowl_write_static(s, "^^");
        cowl_func_write_iri(s, cowl_datatype_get_iri(dt), st);
    }

    return s->state;
}

static ustream_ret cowl_func_write_anon_ind(UOStream *s, CowlAnonInd *ind) {
    cowl_write_static(s, "_:");
    cowl_write_string(s, cowl_anon_ind_get_id(ind));
    return s->state;
}

static ustream_ret cowl_func_write_entity(UOStream *s, CowlAnyEntity *entity, CowlSymTable *st) {
    return cowl_func_write_iri(s, cowl_entity_get_iri(entity), st);
}

static ustream_ret cowl_func_write_declaration(UOStream *s, CowlDeclAxiom *decl, CowlSymTable *st) {
    cowl_write_object_type(s, COWL_OT_A_DECL);
    cowl_write_static(s, "(");

    CowlVector *annot = cowl_decl_axiom_get_annot(decl);
    if (annot) {
        cowl_func_write_vector(s, annot, st);
        cowl_write_static(s, " ");
    }

    CowlEntity *entity = cowl_decl_axiom_get_entity(decl);
    cowl_write_object_type(s, cowl_get_type(entity));
    cowl_write_static(s, "(");
    cowl_func_write_iri(s, cowl_entity_get_iri(entity), st);
    cowl_write_static(s, ")");
    cowl_write_static(s, ")");
    return s->state;
}

static ustream_ret cowl_func_write_obj_quant(UOStream *s, CowlObjQuant *restr, CowlSymTable *st) {
    cowl_write_object_type(s, cowl_get_type(restr));
    cowl_write_static(s, "(");
    cowl_func_write_obj(s, cowl_obj_quant_get_prop(restr), st);
    cowl_write_static(s, " ");
    cowl_func_write_obj(s, cowl_obj_quant_get_filler(restr), st);
    cowl_write_static(s, ")");
    return s->state;
}

static ustream_ret cowl_func_write_data_quant(UOStream *s, CowlDataQuant *restr, CowlSymTable *st) {
    cowl_write_object_type(s, cowl_get_type(restr));
    cowl_write_static(s, "(");
    cowl_func_write_obj(s, cowl_data_quant_get_prop(restr), st);
    cowl_write_static(s, " ");
    cowl_func_write_obj(s, cowl_data_quant_get_range(restr), st);
    cowl_write_static(s, ")");
    return s->state;
}

static ustream_ret
cowl_func_write_sub_obj_prop(UOStream *s, CowlSubObjPropAxiom *axiom, CowlSymTable *st) {
    cowl_write_object_type(s, COWL_OT_A_SUB_OBJ_PROP);
    cowl_write_static(s, "(");

    void *temp = cowl_sub_obj_prop_axiom_get_annot(axiom);

    if (temp) {
        cowl_func_write_vector(s, temp, st);
        cowl_write_static(s, " ");
    }

    temp = cowl_sub_obj_prop_axiom_get_sub(axiom);

    if (cowl_get_type(temp) == COWL_OT_VECTOR) {
        cowl_write_static(s, "ObjectPropertyChain");
        cowl_write_static(s, "(");
        cowl_func_write_vector(s, temp, st);
        cowl_write_static(s, ")");
    } else {
        cowl_func_write_entity(s, temp, st);
    }

    cowl_write_static(s, " ");
    cowl_func_write_obj(s, cowl_sub_obj_prop_axiom_get_super(axiom), st);

    cowl_write_static(s, ")");
    return s->state;
}

static ustream_ret cowl_func_write_has_key(UOStream *s, CowlHasKeyAxiom *axiom, CowlSymTable *st) {
    cowl_write_object_type(s, COWL_OT_A_HAS_KEY);
    cowl_write_static(s, "(");

    void *temp = cowl_has_key_axiom_get_annot(axiom);
    if (temp) {
        cowl_func_write_vector(s, temp, st);
        cowl_write_static(s, " ");
    }

    cowl_func_write_obj(s, cowl_has_key_axiom_get_cls_exp(axiom), st);
    cowl_write_static(s, " ");

    cowl_write_static(s, "(");
    cowl_func_write_vector(s, cowl_has_key_axiom_get_obj_props(axiom), st);
    cowl_write_static(s, ")");
    cowl_write_static(s, " ");
    cowl_write_static(s, "(");
    cowl_func_write_vector(s, cowl_has_key_axiom_get_data_props(axiom), st);
    cowl_write_static(s, ")");

    cowl_write_static(s, ")");
    return s->state;
}

static ustream_ret cowl_func_write_facet_restr(UOStream *s, void *fr, CowlSymTable *st) {
    return cowl_func_write_fields_opt(s, COWL_OT_FACET_RESTR, fr, st);
}

static ustream_ret cowl_func_write_import(UOStream *s, CowlIRI *iri) {
    cowl_write_static(s, "Import");
    cowl_write_static(s, "(");
    cowl_func_write_full_iri(s, iri);
    cowl_write_static(s, ")");
    return s->state;
}

static bool imports_writer(void *ctx, void *import_iri) {
    UOStream *s = ctx;
    cowl_func_write_import(s, import_iri);
    cowl_write_static(s, "\n");
    return s->state == USTREAM_OK;
}

static ustream_ret cowl_func_write_onto_id(UOStream *s, CowlOntologyId *id) {
    if (id->iri) cowl_func_write_full_iri(s, id->iri);

    if (id->version) {
        if (id->iri) cowl_write_static(s, " ");
        cowl_func_write_full_iri(s, id->version);
    }

    return s->state;
}

static ustream_ret cowl_func_write_prefix(UOStream *s, CowlString *prefix, CowlString *ns) {
    cowl_write_static(s, "Prefix");
    cowl_write_static(s, "(");
    cowl_write_string(s, prefix);
    cowl_write_static(s, ":=<");
    cowl_write_string(s, ns);
    cowl_write_static(s, ">");
    cowl_write_static(s, ")");
    return s->state;
}

static bool axiom_writer(void *ctx, void *obj) {
    void **array = ctx;
    UOStream *s = array[0];
    CowlSymTable *st = array[1];
    cowl_func_write_obj(s, obj, st);
    cowl_write_static(s, "\n");
    return s->state == USTREAM_OK;
}

static ustream_ret cowl_func_write_onto(UOStream *s, CowlOntology *onto) {
    CowlSymTable *st = cowl_ontology_get_sym_table(onto);
    CowlTable *prefixes = cowl_sym_table_get_prefix_ns_map(st, false);

    cowl_table_foreach (prefixes, p) {
        cowl_func_write_prefix(s, *p.key, *p.val);
        cowl_write_static(s, "\n");
    }

    cowl_write_static(s, "Ontology");
    cowl_write_static(s, "(");

    CowlOntologyId id = cowl_ontology_get_id(onto);
    cowl_func_write_onto_id(s, &id);
    cowl_write_static(s, "\n");

    CowlIterator iter = { s, imports_writer };
    if (!cowl_ontology_iterate_import_iris(onto, &iter, false)) {
        return s->state ? s->state : USTREAM_ERR;
    }

    cowl_vector_foreach (cowl_ontology_get_annot(onto), annot) {
        cowl_func_write_obj(s, *annot.item, st);
        cowl_write_static(s, "\n");
    }

    void *ctx[] = { s, st };
    iter.ctx = ctx;
    iter.for_each = axiom_writer;
    cowl_ontology_iterate_axioms(onto, &iter, false);

    cowl_write_static(s, ")");
    cowl_write_static(s, "\n");

    return s->state;
}

static ustream_ret cowl_func_write_obj(UOStream *s, CowlAny *obj, CowlSymTable *st) {
    CowlObjectType type = cowl_get_type(obj);
    switch (type) {
        case COWL_OT_STRING: return cowl_write_string(s, obj);
        case COWL_OT_VECTOR: return cowl_func_write_vector(s, obj, st);
        case COWL_OT_TABLE: return cowl_func_write_table(s, obj, st);
        case COWL_OT_IRI: return cowl_func_write_iri(s, obj, st);
        case COWL_OT_LITERAL: return cowl_func_write_literal(s, obj, st);
        case COWL_OT_FACET_RESTR: return cowl_func_write_facet_restr(s, obj, st);
        case COWL_OT_ONTOLOGY: return cowl_func_write_onto(s, obj);
        case COWL_OT_MANAGER:
        case COWL_OT_STREAM: return cowl_write_debug(s, obj);
        case COWL_OT_ANNOTATION: return cowl_func_write_annot_construct(s, obj, st);
        case COWL_OT_ANNOT_PROP:
        case COWL_OT_CE_CLASS:
        case COWL_OT_DPE_DATA_PROP:
        case COWL_OT_DR_DATATYPE:
        case COWL_OT_I_NAMED:
        case COWL_OT_OPE_OBJ_PROP: return cowl_func_write_entity(s, obj, st);
        case COWL_OT_I_ANONYMOUS: return cowl_func_write_anon_ind(s, obj);
        case COWL_OT_A_DECL: return cowl_func_write_declaration(s, obj, st);
        case COWL_OT_A_SUB_OBJ_PROP: return cowl_func_write_sub_obj_prop(s, obj, st);
        case COWL_OT_A_HAS_KEY: return cowl_func_write_has_key(s, obj, st);
        case COWL_OT_CE_OBJ_SOME:
        case COWL_OT_CE_OBJ_ALL: return cowl_func_write_obj_quant(s, obj, st);
        case COWL_OT_CE_DATA_SOME:
        case COWL_OT_CE_DATA_ALL: return cowl_func_write_data_quant(s, obj, st);
        case COWL_OT_CE_OBJ_MIN_CARD:
        case COWL_OT_CE_OBJ_MAX_CARD:
        case COWL_OT_CE_OBJ_EXACT_CARD:
        case COWL_OT_CE_DATA_MIN_CARD:
        case COWL_OT_CE_DATA_MAX_CARD:
        case COWL_OT_CE_DATA_EXACT_CARD: return cowl_func_write_construct_uint(s, obj, st);
        default: {
            if (type >= COWL_OT_FIRST_A && type <= COWL_OT_LAST_A) {
                return cowl_func_write_annot_construct(s, obj, st);
            } else {
                return cowl_func_write_construct(s, obj, st);
            }
        }
    }
}
