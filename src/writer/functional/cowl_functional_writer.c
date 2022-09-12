/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_writer.h"
#include "cowl_annotation.h"
#include "cowl_anon_ind.h"
#include "cowl_datatype.h"
#include "cowl_decl_axiom.h"
#include "cowl_editor.h"
#include "cowl_has_key_axiom.h"
#include "cowl_iri.h"
#include "cowl_literal.h"
#include "cowl_object_private.h"
#include "cowl_ontology.h"
#include "cowl_rdf_vocab.h"
#include "cowl_string.h"
#include "cowl_sub_obj_prop_axiom.h"
#include "cowl_table.h"
#include "cowl_vector.h"

static ustream_ret cowl_func_write_obj(UOStream *s, void *obj, CowlEditor *ed);
static ustream_ret cowl_func_write_onto(UOStream *s, CowlOntology *onto, CowlEditor *ed);

static cowl_ret cowl_func_write(UOStream *stream, void *object) {
    return cowl_ret_from_ustream(cowl_func_write_obj(stream, object, NULL));
}

static cowl_ret cowl_func_write_ontology(cowl_unused void *state, UOStream *stream, CowlEditor *editor) {
    ustream_ret ret = cowl_func_write_onto(stream, cowl_editor_get_ontology(editor), editor);
    return cowl_ret_from_ustream(ret);
}

static CowlWriter const cowl_func_writer = {
    .name = "functional",
    .write_ontology = cowl_func_write_ontology,
    .write = cowl_func_write
};

CowlWriter cowl_writer_get_functional(void) {
    return cowl_func_writer;
}

static ustream_ret cowl_func_write_fields(UOStream *s, CowlObjectType type,
                                           void *obj, CowlEditor *ed) {
    ulib_byte count = composite_fields[type];
    cowl_func_write_obj(s, cowl_get_field(obj, 0), ed);
    for (ulib_byte i = 1; i < count; ++i) {
        cowl_write_static(s, " ");
        cowl_func_write_obj(s, cowl_get_field(obj, i), ed);
    }
    return s->state;
}

static ustream_ret cowl_func_write_fields_opt(UOStream *s, CowlObjectType type,
                                               void *obj, CowlEditor *ed) {
    cowl_func_write_fields(s, type, obj, ed);

    void *opt = cowl_get_opt_field(obj);
    if (opt) {
        cowl_write_static(s, " ");
        cowl_func_write_obj(s, opt, ed);
    }

    return s->state;
}

static ustream_ret cowl_func_write_opt_fields(UOStream *s, CowlObjectType type,
                                               void *obj, CowlEditor *ed) {
    void *opt = cowl_get_opt_field(obj);
    if (opt) {
        cowl_func_write_obj(s, opt, ed);
        cowl_write_static(s, " ");
    }

    cowl_func_write_fields(s, type, obj, ed);

    return s->state;
}

static ustream_ret cowl_func_write_construct(UOStream *s, void *obj, CowlEditor *ed) {
    CowlObjectType type = cowl_get_type(obj);
    cowl_write_object_type(s, type);
    cowl_write_static(s, "(");
    cowl_func_write_fields_opt(s, type, obj, ed);
    cowl_write_static(s, ")");
    return s->state;
}

static ustream_ret cowl_func_write_construct_uint(UOStream *s, void *obj, CowlEditor *ed) {
    CowlObjectType type = cowl_get_type(obj);
    cowl_write_object_type(s, type);
    cowl_write_static(s, "(");
    cowl_write_uint(s, cowl_get_uint_field(obj));
    cowl_write_static(s, " ");
    cowl_func_write_fields_opt(s, type, obj, ed);
    cowl_write_static(s, ")");
    return s->state;
}

static ustream_ret cowl_func_write_axiom(UOStream *s, void *obj, CowlEditor *ed) {
    CowlObjectType type = cowl_get_type(obj);
    cowl_write_object_type(s, type);
    cowl_write_static(s, "(");
    cowl_func_write_opt_fields(s, type, obj, ed);
    cowl_write_static(s, ")");
    return s->state;
}

static ustream_ret cowl_func_write_vector(UOStream *s, CowlVector *vec, CowlEditor *ed) {
    if (!vec) return s->state;
    ulib_uint last = cowl_vector_count(vec) - 1;

    cowl_vector_foreach(vec, obj) {
        cowl_func_write_obj(s, *obj.item, ed);
        if (obj.i < last) cowl_write_static(s, " ");
    }

    return s->state;
}

static ustream_ret cowl_func_write_table(UOStream *s, CowlTable *table, CowlEditor *ed) {
    if (!table) return s->state;
    ulib_uint current = 0, last = cowl_table_count(table) - 1;

    cowl_table_foreach(table, obj) {
        cowl_func_write_obj(s, *obj.key, ed);
        if (obj.val && *obj.val) {
            cowl_write_static(s, ":");
            cowl_func_write_obj(s, *obj.val, ed);
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

static ustream_ret cowl_func_write_iri(UOStream *stream, CowlIRI *iri, CowlEditor *ed) {
    if (!ed) return cowl_write_iri(stream, iri);

    CowlString *pfx;
    if (cowl_iri_has_rem(iri) && (pfx = cowl_editor_get_prefix(ed, cowl_iri_get_ns(iri)))) {
        return cowl_func_write_short_iri(stream, pfx, cowl_iri_get_rem(iri));
    }

    return cowl_func_write_full_iri(stream, iri);
}

static ustream_ret cowl_func_write_literal(UOStream *s, CowlLiteral *literal, CowlEditor *ed) {
    cowl_write_static(s, "\"");
    cowl_write_string(s, cowl_literal_get_value(literal));
    cowl_write_static(s, "\"");

    CowlDatatype *dt = cowl_literal_get_datatype(literal);
    if (cowl_datatype_equals(dt, cowl_rdf_vocab_get()->dt.plain_literal)) {
        CowlString *lang = cowl_literal_get_lang(literal);
        if (lang) {
            cowl_write_static(s, "@");
            cowl_write_string(s, lang);
        }
    } else {
        cowl_write_static(s, "^^");
        cowl_func_write_iri(s, cowl_datatype_get_iri(dt), ed);
    }

    return s->state;
}

static ustream_ret cowl_func_write_anon_ind(UOStream *s, CowlAnonInd *ind, CowlEditor *ed) {
    cowl_write_static(s, "_:");

    if (!ed) {
        cowl_write_uint(s, (ulib_uint)cowl_anon_ind_get_id(ind));
        return s->state;
    }

    CowlString *str = cowl_editor_get_name_for_anon_ind(ed, ind);
    if (!str) return USTREAM_ERR_MEM;

    cowl_write_string(s, str);
    return s->state;
}

static ustream_ret cowl_func_write_entity(UOStream *s, void *entity, CowlEditor *ed) {
    return cowl_func_write_iri(s, cowl_entity_get_iri(entity), ed);
}

static ustream_ret cowl_func_write_declaration(UOStream *s, CowlDeclAxiom *decl, CowlEditor *ed) {
    cowl_write_object_type(s, COWL_OT_A_DECL);
    cowl_write_static(s, "(");

    void *annot = cowl_decl_axiom_get_annot(decl);
    if (annot) {
        cowl_func_write_vector(s, annot, ed);
        cowl_write_static(s, " ");
    }

    CowlEntity *entity = cowl_decl_axiom_get_entity(decl);
    cowl_write_object_type(s, cowl_get_type(entity));
    cowl_write_static(s, "(");
    cowl_func_write_iri(s, cowl_entity_get_iri(entity), ed);
    cowl_write_static(s, ")");
    cowl_write_static(s, ")");
    return s->state;
}

static ustream_ret cowl_func_write_sub_obj_prop(UOStream *s, CowlSubObjPropAxiom *axiom,
                                                 CowlEditor *ed) {
    cowl_write_object_type(s, COWL_OT_A_SUB_OBJ_PROP);
    cowl_write_static(s, "(");

    void *temp = cowl_sub_obj_prop_axiom_get_annot(axiom);

    if (temp) {
        cowl_func_write_vector(s, temp, ed);
        cowl_write_static(s, " ");
    }

    temp = cowl_sub_obj_prop_axiom_get_sub(axiom);

    if (cowl_get_type(temp) == COWL_OT_VECTOR) {
        cowl_write_static(s, "ObjectPropertyChain");
        cowl_write_static(s, "(");
        cowl_func_write_vector(s, temp, ed);
        cowl_write_static(s, ")");
    } else {
        cowl_func_write_entity(s, temp, ed);
    }

    cowl_write_static(s, " ");
    cowl_func_write_obj(s, cowl_sub_obj_prop_axiom_get_super(axiom), ed);

    cowl_write_static(s, ")");
    return s->state;
}

static ustream_ret cowl_func_write_has_key(UOStream *s, CowlHasKeyAxiom *axiom, CowlEditor *ed) {
    cowl_write_object_type(s, COWL_OT_A_HAS_KEY);
    cowl_write_static(s, "(");

    void *temp = cowl_has_key_axiom_get_annot(axiom);
    if (temp) {
        cowl_func_write_vector(s, temp, ed);
        cowl_write_static(s, " ");
    }

    cowl_func_write_obj(s, cowl_has_key_axiom_get_cls_exp(axiom), ed);
    cowl_write_static(s, " ");

    cowl_write_static(s, "(");
    cowl_func_write_vector(s, cowl_has_key_axiom_get_obj_props(axiom), ed);
    cowl_write_static(s, ")");
    cowl_write_static(s, " ");
    cowl_write_static(s, "(");
    cowl_func_write_vector(s, cowl_has_key_axiom_get_data_props(axiom), ed);
    cowl_write_static(s, ")");

    cowl_write_static(s, ")");
    return s->state;
}

static ustream_ret cowl_func_write_facet_restr(UOStream *s, void *fr, CowlEditor *ed) {
    return cowl_func_write_fields_opt(s, COWL_OT_FACET_RESTR, fr, ed);
}

static ustream_ret cowl_func_write_import(UOStream *s, CowlIRI *iri) {
    cowl_write_static(s, "Import");
    cowl_write_static(s, "(");
    cowl_func_write_full_iri(s, iri);
    cowl_write_static(s, ")");
    return s->state;
}

static bool imports_writer(void *ctx, void *import) {
    void **array = ctx;
    UOStream *s = array[0];
    CowlEditor *ed = array[1];
    CowlIRI *iri = cowl_editor_get_import_iri(ed, import);

    if (!iri) {
        iri = cowl_ontology_get_id(import).iri;
        CowlString *iri_str = cowl_iri_to_string(iri);

        UString comp[] = {
            ustring_literal("No import IRI for ontology \""),
            *cowl_string_get_raw(iri_str),
            ustring_literal("\"")
        };

        UString desc = ustring_join(comp, ulib_array_count(comp), ustring_empty);
        cowl_editor_handle_error(ed, COWL_ERR_IMPORT, desc);

        cowl_string_release(iri_str);
        ustring_deinit(&desc);

        return false;
    }

    cowl_func_write_import(s, iri);
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
    CowlEditor *ed = array[1];
    cowl_func_write_obj(s, obj, ed);
    cowl_write_static(s, "\n");
    return s->state == USTREAM_OK;
}

static ustream_ret cowl_func_write_onto(UOStream *s, CowlOntology *onto, CowlEditor *ed) {
    CowlTable *prefixes = cowl_editor_get_prefix_ns_map(ed, false);

    cowl_table_foreach(prefixes, p) {
        cowl_func_write_prefix(s, *p.key, *p.val);
        cowl_write_static(s, "\n");
    }

    cowl_write_static(s, "Ontology");
    cowl_write_static(s, "(");

    CowlOntologyId id = cowl_ontology_get_id(onto);
    cowl_func_write_onto_id(s, &id);
    cowl_write_static(s, "\n");

    void *ctx[] = { s, ed };
    CowlIterator iter = cowl_iterator(ctx, imports_writer);
    if (!cowl_ontology_iterate_imports(onto, &iter, false)) {
        return s->state ? s->state : USTREAM_ERR;
    }

    cowl_vector_foreach(cowl_ontology_get_annot(onto), annot) {
        cowl_func_write_obj(s, *annot.item, ed);
        cowl_write_static(s, "\n");
    }

    iter = cowl_iterator(ctx, axiom_writer);
    cowl_ontology_iterate_axioms(onto, &iter, false);

    cowl_write_static(s, ")");
    cowl_write_static(s, "\n");

    return s->state;
}

static ustream_ret cowl_func_write_obj(UOStream *s, void *obj, CowlEditor *ed) {
    CowlObjectType type = cowl_get_type(obj);
    switch (type) {
        case COWL_OT_STRING: return cowl_write_string(s, obj);
        case COWL_OT_VECTOR: return cowl_func_write_vector(s, obj, ed);
        case COWL_OT_TABLE: return cowl_func_write_table(s, obj, ed);
        case COWL_OT_IRI: return cowl_func_write_iri(s, obj, ed);
        case COWL_OT_LITERAL: return cowl_func_write_literal(s, obj, ed);
        case COWL_OT_FACET_RESTR: return cowl_func_write_facet_restr(s, obj, ed);
        case COWL_OT_ONTOLOGY: return cowl_func_write_onto(s, obj, ed);
        case COWL_OT_MANAGER: return cowl_write_debug(s, obj);
        case COWL_OT_ANNOT_PROP:
        case COWL_OT_CE_CLASS:
        case COWL_OT_DPE_DATA_PROP:
        case COWL_OT_DR_DATATYPE:
        case COWL_OT_I_NAMED:
        case COWL_OT_OPE_OBJ_PROP: return cowl_func_write_entity(s, obj, ed);
        case COWL_OT_I_ANONYMOUS: return cowl_func_write_anon_ind(s, obj, ed);
        case COWL_OT_A_DECL: return cowl_func_write_declaration(s, obj, ed);
        case COWL_OT_A_SUB_OBJ_PROP: return cowl_func_write_sub_obj_prop(s, obj, ed);
        case COWL_OT_A_HAS_KEY: return cowl_func_write_has_key(s, obj, ed);
        case COWL_OT_CE_OBJ_MIN_CARD:
        case COWL_OT_CE_OBJ_MAX_CARD:
        case COWL_OT_CE_OBJ_EXACT_CARD:
        case COWL_OT_CE_DATA_MIN_CARD:
        case COWL_OT_CE_DATA_MAX_CARD:
        case COWL_OT_CE_DATA_EXACT_CARD: return cowl_func_write_construct_uint(s, obj, ed);
        default: {
            if (type >= COWL_OT_FIRST_A && type <= COWL_OT_LAST_A) {
                return cowl_func_write_axiom(s, obj, ed);
            } else {
                return cowl_func_write_construct(s, obj, ed);
            }
        }
    }
}
