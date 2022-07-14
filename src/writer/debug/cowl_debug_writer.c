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
#include "cowl_anon_ind.h"
#include "cowl_datatype.h"
#include "cowl_editor.h"
#include "cowl_iri.h"
#include "cowl_literal.h"
#include "cowl_object_private.h"
#include "cowl_ontology.h"
#include "cowl_rdf_vocab.h"
#include "cowl_set.h"
#include "cowl_vector.h"

static ustream_ret cowl_debug_write_obj(UOStream *s, void *obj, CowlEditor *ed);
static ustream_ret cowl_debug_write_onto(UOStream *s, CowlOntology *onto, CowlEditor *ed);

static cowl_ret cowl_debug_write(UOStream *stream, void *object) {
    return cowl_ret_from_ustream(cowl_debug_write_obj(stream, object, NULL));
}

static cowl_ret cowl_debug_write_ontology(cowl_unused void *state, UOStream *stream, CowlEditor *editor) {
    ustream_ret ret = cowl_debug_write_onto(stream, cowl_editor_get_ontology(editor), editor);
    return cowl_ret_from_ustream(ret);
}

static CowlWriter const cowl_debug_writer = {
    .name = "debug",
    .write_ontology = cowl_debug_write_ontology,
    .write = cowl_debug_write
};

CowlWriter cowl_writer_get_debug(void) {
    return cowl_debug_writer;
}

static ustream_ret cowl_debug_write_vector(UOStream *s, CowlVector *vec, CowlEditor *ed) {
    if (!vec) return s->state;
    ulib_uint last = cowl_vector_count(vec) - 1;

    cowl_vector_foreach(vec, obj) {
        cowl_debug_write_obj(s, *obj.item, ed);
        if (obj.i < last) cowl_write_static(s, " ");
    }

    return s->state;
}

static ustream_ret cowl_debug_write_set(UOStream *s, CowlSet *set, CowlEditor *ed) {
    if (!set) return s->state;
    UHash(CowlObjectTable) const *data = cowl_set_get_data(set);
    ulib_uint current = 0, last = uhash_count(CowlObjectTable, data) - 1;

    uhash_foreach(CowlObjectTable, data, obj) {
        cowl_debug_write_obj(s, *obj.key, ed);
        if (current++ < last) cowl_write_static(s, " ");
    }

    return s->state;
}

static ustream_ret cowl_debug_write_iri(UOStream *stream, CowlIRI *iri, CowlEditor *ed) {
    if (!ed) return cowl_write_iri(stream, iri);

    CowlString *ns = cowl_editor_get_prefix(ed, cowl_iri_get_ns(iri));
    bool brackets = !ns;

    if (brackets) {
        ns = cowl_iri_get_ns(iri);
        cowl_write_static(stream, "<");
    }

    cowl_write_string(stream, ns);
    if (!brackets) cowl_write_static(stream, ":");
    cowl_write_string(stream, cowl_iri_get_rem(iri));

    if (brackets) cowl_write_static(stream, ">");

    return stream->state;
}

static ustream_ret cowl_debug_write_literal(UOStream *s, CowlLiteral *literal, CowlEditor *ed) {
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
        cowl_debug_write_iri(s, cowl_datatype_get_iri(dt), ed);
    }

    return s->state;
}

static ustream_ret cowl_debug_write_anon_ind(UOStream *s, CowlAnonInd *ind, CowlEditor *ed) {
    if (!ed) {
        cowl_write_static(s, "_:");
        cowl_write_uint(s, (ulib_uint)cowl_anon_ind_get_id(ind));
        return s->state;
    }

    CowlString *str = cowl_editor_get_id_for_anon_ind(ed, ind);
    if (!str) return USTREAM_ERR_MEM;

    cowl_write_string(s, str);
    return s->state;
}

static ustream_ret cowl_debug_write_primitive(UOStream *s, void *primitive, CowlEditor *ed) {
    CowlObjectType type = cowl_get_type(primitive);
    cowl_write_object_type(s, type);
    cowl_write_static(s, "(");
    if (type == COWL_OT_I_ANONYMOUS) {
        cowl_debug_write_anon_ind(s, primitive, ed);
    } else {
        cowl_debug_write_iri(s, cowl_entity_get_iri(primitive), ed);
    }
    cowl_write_static(s, ")");
    return s->state;
}

static ustream_ret cowl_debug_write_composite_header(UOStream *s, void *obj, CowlEditor *ed) {
    CowlObjectType type = cowl_get_type(obj);
    cowl_write_object_type(s, type);
    cowl_write_static(s, "(");

    ulib_byte count = composite_fields[type];
    cowl_debug_write_obj(s, cowl_get_field(obj, 0), ed);
    for (ulib_byte i = 1; i < count; ++i) {
        cowl_write_static(s, " ");
        cowl_debug_write_obj(s, cowl_get_field(obj, i), ed);
    }

    void *opt = cowl_get_opt_field(obj);
    if (opt) {
        cowl_write_static(s, " ");
        cowl_debug_write_obj(s, opt, ed);
    }

    return s->state;
}

static ustream_ret cowl_debug_write_composite(UOStream *s, void *obj, CowlEditor *ed) {
    cowl_debug_write_composite_header(s, obj, ed);
    cowl_write_static(s, ")");
    return s->state;
}

static ustream_ret cowl_debug_write_composite_uint(UOStream *s, void *obj, CowlEditor *ed) {
    cowl_debug_write_composite_header(s, obj, ed);
    cowl_write_static(s, " ");
    cowl_write_uint(s, cowl_get_uint_field(obj));
    cowl_write_static(s, ")");
    return s->state;
}

static bool imports_writer(void *ctx, void *import) {
    void **array = ctx;
    UOStream *s = array[0];
    CowlEditor *ed = array[1];

    CowlIRI *iri = cowl_ontology_get_id(import).ontology_iri;
    cowl_write_static(s, "\n");
    cowl_write_static(s, "Imports");
    cowl_write_static(s, "(");

    if (iri) {
        cowl_debug_write_iri(s, iri, ed);
    } else {
        uostream_writef(s, NULL, "anon(%p)", import);
    }

    cowl_write_static(s, ")");
    return s->state == USTREAM_OK;
}

static bool entity_writer(void *ctx, void *obj) {
    void **array = ctx;
    UOStream *s = array[0];
    CowlEditor *ed = array[1];
    cowl_debug_write_primitive(s, obj, ed);
    cowl_write_static(s, "\n");
    return s->state == USTREAM_OK;
}

static bool axiom_writer(void *ctx, void *obj) {
    void **array = ctx;
    UOStream *s = array[0];
    CowlEditor *ed = array[1];
    cowl_debug_write_obj(s, obj, ed);
    cowl_write_static(s, "\n");
    return s->state == USTREAM_OK;
}

static ustream_ret cowl_debug_write_onto_id(UOStream *s, CowlOntologyId *id, CowlEditor *ed) {
    if (id->ontology_iri) cowl_debug_write_iri(s, id->ontology_iri, ed);

    if (id->version_iri) {
        if (id->ontology_iri) cowl_write_static(s, " ");
        cowl_debug_write_iri(s, id->version_iri, ed);
    }

    return s->state;
}

static ustream_ret cowl_debug_write_onto(UOStream *s, CowlOntology *onto, CowlEditor *ed) {
    cowl_write_static(s, "Ontology");
    cowl_write_static(s, "(");

    CowlOntologyId id = cowl_ontology_get_id(onto);
    cowl_debug_write_onto_id(s, &id, ed);

    void *ctx[] = { s, ed };
    CowlIterator iter = cowl_iterator_init(ctx, imports_writer);
    cowl_ontology_iterate_imports(onto, &iter);
    if (s->state) return s->state;

    CowlVector *annotations = cowl_ontology_get_annot(onto);
    cowl_vector_foreach(annotations, annot) {
        cowl_write_static(s, "\n");
        cowl_debug_write_obj(s, *annot.item, ed);
    }

    cowl_write_static(s, ")");
    cowl_write_static(s, "\n");

    iter = cowl_iterator_init(ctx, entity_writer);
    cowl_ontology_iterate_primitives(onto, COWL_PF_ENTITY, &iter);

    iter = cowl_iterator_init(ctx, axiom_writer);
    cowl_ontology_iterate_axioms(onto, &iter);

    return s->state;
}

static ustream_ret cowl_debug_write_obj(UOStream *s, void *obj, CowlEditor *ed) {
    switch (cowl_get_type(obj)) {
        case COWL_OT_STRING: return cowl_write_string(s, obj);
        case COWL_OT_VECTOR: return cowl_debug_write_vector(s, obj, ed);
        case COWL_OT_SET: return cowl_debug_write_set(s, obj, ed);
        case COWL_OT_IRI: return cowl_debug_write_iri(s, obj, ed);
        case COWL_OT_LITERAL: return cowl_debug_write_literal(s, obj, ed);
        case COWL_OT_ANNOT_PROP:
        case COWL_OT_CE_CLASS:
        case COWL_OT_DPE_DATA_PROP:
        case COWL_OT_DR_DATATYPE:
        case COWL_OT_I_NAMED:
        case COWL_OT_I_ANONYMOUS:
        case COWL_OT_OPE_OBJ_PROP: return cowl_debug_write_primitive(s, obj, ed);
        case COWL_OT_CE_OBJ_MIN_CARD:
        case COWL_OT_CE_OBJ_MAX_CARD:
        case COWL_OT_CE_OBJ_EXACT_CARD:
        case COWL_OT_CE_DATA_MIN_CARD:
        case COWL_OT_CE_DATA_MAX_CARD:
        case COWL_OT_CE_DATA_EXACT_CARD: return cowl_debug_write_composite_uint(s, obj, ed);
        case COWL_OT_ONTOLOGY: return cowl_debug_write_onto(s, obj, ed);
        default: return cowl_debug_write_composite(s, obj, ed);
    }
}
