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
#include "cowl_any.h"
#include "cowl_attrs.h"
#include "cowl_axiom.h"
#include "cowl_data_quant.h"
#include "cowl_datatype.h"
#include "cowl_decl_axiom.h"
#include "cowl_entity.h"
#include "cowl_has_key_axiom.h"
#include "cowl_impl.h"
#include "cowl_iri.h"
#include "cowl_literal.h"
#include "cowl_obj_quant.h"
#include "cowl_object.h"
#include "cowl_object_type.h"
#include "cowl_ontology_header.h"
#include "cowl_prefix_map.h"
#include "cowl_primitive_private.h"
#include "cowl_ret.h"
#include "cowl_sub_obj_prop_axiom.h"
#include "cowl_table.h"
#include "cowl_vector.h"
#include "cowl_vocab.h"
#include "cowl_writer.h"
#include "ulib.h"
#include <stddef.h>

static ulib_ret cowl_func_write_obj(UOStream *s, CowlAny *obj, CowlPrefixMap *pm);
static ulib_ret
cowl_func_write_onto_header(UOStream *s, CowlOntologyHeader *header, CowlPrefixMap *pm);
static ulib_ret cowl_func_write_onto_footer(UOStream *s);

static cowl_ret cowl_func_write(cowl_unused void *ctx, UOStream *stream, CowlAny *object) {
    return cowl_ret_from_ulib(cowl_func_write_obj(stream, object, NULL));
}

static cowl_ret
cowl_func_write_header(CowlStreamState state, UOStream *stream, CowlOntologyHeader header) {
    return cowl_ret_from_ulib(cowl_func_write_onto_header(stream, &header, state.pm));
}

static cowl_ret
cowl_func_write_axiom(CowlStreamState state, UOStream *stream, CowlAnyAxiom *axiom) {
    cowl_func_write_obj(stream, axiom, state.pm);
    cowl_write_static(stream, "\n");
    return cowl_ret_from_ulib(stream->state);
}

static cowl_ret cowl_func_write_footer(cowl_unused CowlStreamState state, UOStream *stream) {
    return cowl_ret_from_ulib(cowl_func_write_onto_footer(stream));
}

static CowlWriter const cowl_func_writer = {
    .name = "functional",
    .write = cowl_func_write,
    .stream = {
        .write_header = cowl_func_write_header,
        .write_axiom = cowl_func_write_axiom,
        .write_footer = cowl_func_write_footer,
    },
};

CowlWriter cowl_writer_functional(void) {
    return cowl_func_writer;
}

static ulib_ret cowl_func_write_fields(UOStream *s, CowlAny *obj, CowlPrefixMap *pm) {
    unsigned n;
    CowlAny **fields = cowl_get_fields(obj, &n);
    cowl_func_write_obj(s, fields[0], pm);

    for (unsigned i = 1; i < n; ++i) {
        cowl_write_static(s, " ");
        cowl_func_write_obj(s, fields[i], pm);
    }

    return s->state;
}

static ulib_ret cowl_func_write_fields_opt(UOStream *s, CowlAny *obj, CowlPrefixMap *pm) {
    cowl_func_write_fields(s, obj, pm);
    CowlAny *opt = cowl_get_opt_field(obj);

    if (opt) {
        cowl_write_static(s, " ");
        cowl_func_write_obj(s, opt, pm);
    }

    return s->state;
}

static ulib_ret cowl_func_write_opt_fields(UOStream *s, CowlAny *obj, CowlPrefixMap *pm) {
    CowlAny *opt = cowl_get_opt_field(obj);

    if (opt) {
        cowl_func_write_obj(s, opt, pm);
        cowl_write_static(s, " ");
    }

    cowl_func_write_fields(s, obj, pm);

    return s->state;
}

static ulib_ret cowl_func_write_construct(UOStream *s, CowlAny *obj, CowlPrefixMap *pm) {
    cowl_write_object_type(s, cowl_get_type(obj));
    cowl_write_static(s, "(");
    cowl_func_write_fields_opt(s, obj, pm);
    cowl_write_static(s, ")");
    return s->state;
}

static ulib_ret cowl_func_write_construct_uint(UOStream *s, CowlAny *obj, CowlPrefixMap *pm) {
    cowl_write_object_type(s, cowl_get_type(obj));
    cowl_write_static(s, "(");
    cowl_write_uint(s, cowl_get_uint_field(obj));
    cowl_write_static(s, " ");
    cowl_func_write_fields_opt(s, obj, pm);
    cowl_write_static(s, ")");
    return s->state;
}

static ulib_ret cowl_func_write_annot_construct(UOStream *s, CowlAny *obj, CowlPrefixMap *pm) {
    cowl_write_object_type(s, cowl_get_type(obj));
    cowl_write_static(s, "(");
    cowl_func_write_opt_fields(s, obj, pm);
    cowl_write_static(s, ")");
    return s->state;
}

static ulib_ret cowl_func_write_vector(UOStream *s, CowlVector *vec, CowlPrefixMap *pm) {
    if (!vec) return s->state;
    ulib_uint last = cowl_vector_count(vec) - 1;

    cowl_vector_foreach (vec, obj) {
        cowl_func_write_obj(s, *obj.item, pm);
        if (obj.i < last) cowl_write_static(s, " ");
    }

    return s->state;
}

static ulib_ret cowl_func_write_table(UOStream *s, CowlTable *table, CowlPrefixMap *pm) {
    if (!table) return s->state;
    ulib_uint current = 0;
    ulib_uint last = cowl_table_count(table) - 1;

    cowl_table_foreach (table, obj) {
        cowl_func_write_obj(s, *obj.key, pm);
        if (obj.val && *obj.val) {
            cowl_write_static(s, ":");
            cowl_func_write_obj(s, *obj.val, pm);
        }
        if (current++ < last) cowl_write_static(s, " ");
    }

    return s->state;
}

static ulib_ret cowl_func_write_full_iri(UOStream *stream, CowlIRI *iri) {
    cowl_write_static(stream, "<");
    cowl_write_iri(stream, iri);
    cowl_write_static(stream, ">");
    return stream->state;
}

static ulib_ret cowl_func_write_short_iri(UOStream *stream, CowlString *pfx, CowlString *rem) {
    cowl_write_string(stream, pfx);
    cowl_write_static(stream, ":");
    cowl_write_string(stream, rem);
    return stream->state;
}

static ulib_ret cowl_func_write_iri(UOStream *stream, CowlIRI *iri, CowlPrefixMap *pm) {
    CowlString *prefix;

    if (pm && cowl_iri_has_rem(iri) &&
        (prefix = cowl_prefix_map_get_prefix(pm, cowl_iri_get_ns(iri)))) {
        return cowl_func_write_short_iri(stream, prefix, cowl_iri_get_rem(iri));
    }

    return cowl_func_write_full_iri(stream, iri);
}

static ulib_ret cowl_func_write_literal(UOStream *s, CowlLiteral *literal, CowlPrefixMap *pm) {
    cowl_write_static(s, "\"");
    cowl_write_string(s, cowl_literal_get_value(literal));
    cowl_write_static(s, "\"");

    CowlDatatype *dt = cowl_literal_get_datatype(literal);
    if (cowl_primitive_equals(dt, cowl_rdf_vocab()->dt.lang_string)) {
        CowlString *lang = cowl_literal_get_lang(literal);
        cowl_write_static(s, "@");
        cowl_write_string(s, lang);
    } else if (!cowl_primitive_equals(dt, cowl_xsd_vocab()->dt.string)) {
        cowl_write_static(s, "^^");
        cowl_func_write_iri(s, cowl_datatype_get_iri(dt), pm);
    }

    return s->state;
}

static ulib_ret cowl_func_write_anon_ind(UOStream *s, CowlAnonInd *ind) {
    cowl_write_static(s, "_:");
    cowl_write_string(s, cowl_anon_ind_get_id(ind));
    return s->state;
}

static ulib_ret cowl_func_write_entity(UOStream *s, CowlAnyEntity *entity, CowlPrefixMap *pm) {
    return cowl_func_write_iri(s, cowl_entity_get_iri(entity), pm);
}

static ulib_ret cowl_func_write_declaration(UOStream *s, CowlDeclAxiom *decl, CowlPrefixMap *pm) {
    cowl_write_object_type(s, COWL_OT_A_DECL);
    cowl_write_static(s, "(");

    CowlVector *annot = cowl_axiom_get_annot(decl);
    if (annot) {
        cowl_func_write_vector(s, annot, pm);
        cowl_write_static(s, " ");
    }

    CowlEntity *entity = cowl_decl_axiom_get_entity(decl);
    cowl_write_object_type(s, cowl_get_type(entity));
    cowl_write_static(s, "(");
    cowl_func_write_iri(s, cowl_entity_get_iri(entity), pm);
    cowl_write_static(s, ")");
    cowl_write_static(s, ")");
    return s->state;
}

static ulib_ret cowl_func_write_obj_quant(UOStream *s, CowlObjQuant *restr, CowlPrefixMap *pm) {
    cowl_write_object_type(s, cowl_get_type(restr));
    cowl_write_static(s, "(");
    cowl_func_write_obj(s, cowl_obj_quant_get_prop(restr), pm);
    cowl_write_static(s, " ");
    cowl_func_write_obj(s, cowl_obj_quant_get_filler(restr), pm);
    cowl_write_static(s, ")");
    return s->state;
}

static ulib_ret cowl_func_write_data_quant(UOStream *s, CowlDataQuant *restr, CowlPrefixMap *pm) {
    cowl_write_object_type(s, cowl_get_type(restr));
    cowl_write_static(s, "(");
    cowl_func_write_obj(s, cowl_data_quant_get_prop(restr), pm);
    cowl_write_static(s, " ");
    cowl_func_write_obj(s, cowl_data_quant_get_range(restr), pm);
    cowl_write_static(s, ")");
    return s->state;
}

static ulib_ret
cowl_func_write_sub_obj_prop(UOStream *s, CowlSubObjPropAxiom *axiom, CowlPrefixMap *pm) {
    cowl_write_object_type(s, COWL_OT_A_SUB_OBJ_PROP);
    cowl_write_static(s, "(");

    void *temp = cowl_axiom_get_annot(axiom);

    if (temp) {
        cowl_func_write_vector(s, temp, pm);
        cowl_write_static(s, " ");
    }

    temp = cowl_sub_obj_prop_axiom_get_sub(axiom);

    if (cowl_get_type(temp) == COWL_OT_VECTOR) {
        cowl_write_static(s, "ObjectPropertyChain");
        cowl_write_static(s, "(");
        cowl_func_write_vector(s, temp, pm);
        cowl_write_static(s, ")");
    } else {
        cowl_func_write_entity(s, temp, pm);
    }

    cowl_write_static(s, " ");
    cowl_func_write_obj(s, cowl_sub_obj_prop_axiom_get_super(axiom), pm);

    cowl_write_static(s, ")");
    return s->state;
}

static ulib_ret cowl_func_write_has_key(UOStream *s, CowlHasKeyAxiom *axiom, CowlPrefixMap *pm) {
    cowl_write_object_type(s, COWL_OT_A_HAS_KEY);
    cowl_write_static(s, "(");

    void *temp = cowl_axiom_get_annot(axiom);
    if (temp) {
        cowl_func_write_vector(s, temp, pm);
        cowl_write_static(s, " ");
    }

    cowl_func_write_obj(s, cowl_has_key_axiom_get_cls_exp(axiom), pm);
    cowl_write_static(s, " ");

    cowl_write_static(s, "(");
    cowl_func_write_vector(s, cowl_has_key_axiom_get_obj_props(axiom), pm);
    cowl_write_static(s, ")");
    cowl_write_static(s, " ");
    cowl_write_static(s, "(");
    cowl_func_write_vector(s, cowl_has_key_axiom_get_data_props(axiom), pm);
    cowl_write_static(s, ")");

    cowl_write_static(s, ")");
    return s->state;
}

static ulib_ret cowl_func_write_facet_restr(UOStream *s, void *fr, CowlPrefixMap *pm) {
    return cowl_func_write_fields_opt(s, fr, pm);
}

static ulib_ret cowl_func_write_import(UOStream *s, CowlIRI *iri) {
    cowl_write_static(s, "Import");
    cowl_write_static(s, "(");
    cowl_func_write_full_iri(s, iri);
    cowl_write_static(s, ")");
    return s->state;
}

static ulib_ret cowl_func_write_onto_iri_version(UOStream *s, CowlIRI *iri, CowlIRI *version) {
    if (iri) cowl_func_write_full_iri(s, iri);

    if (version) {
        if (iri) cowl_write_static(s, " ");
        cowl_func_write_full_iri(s, version);
    }

    return s->state;
}

static ulib_ret cowl_func_write_prefix(UOStream *s, CowlString *prefix, CowlString *ns) {
    cowl_write_static(s, "Prefix");
    cowl_write_static(s, "(");
    cowl_write_string(s, prefix);
    cowl_write_static(s, ":=<");
    cowl_write_string(s, ns);
    cowl_write_static(s, ">");
    cowl_write_static(s, ")");
    return s->state;
}

static ulib_ret
cowl_func_write_onto_header(UOStream *s, CowlOntologyHeader *header, CowlPrefixMap *pm) {
    CowlTable *prefixes = cowl_prefix_map_get_table(pm, false);

    cowl_table_foreach (prefixes, p) {
        if (cowl_vocab_is_reserved_prefix(*p.key)) continue;
        cowl_func_write_prefix(s, *p.key, *p.val);
        cowl_write_static(s, "\n");
    }

    cowl_write_static(s, "Ontology");
    cowl_write_static(s, "(");

    cowl_func_write_onto_iri_version(s, header->iri, header->version);
    cowl_write_static(s, "\n");

    if (header->imports) {
        uvec_foreach (CowlObjectPtr, header->imports, import) {
            cowl_func_write_import(s, *import.item);
            cowl_write_static(s, "\n");
        }
    }

    if (header->annotations) {
        uvec_foreach (CowlObjectPtr, header->annotations, annot) {
            cowl_func_write_obj(s, *annot.item, pm);
            cowl_write_static(s, "\n");
        }
    }

    return s->state;
}

static ulib_ret cowl_func_write_onto_footer(UOStream *s) {
    cowl_write_static(s, ")");
    cowl_write_static(s, "\n");
    return s->state;
}

static ulib_ret cowl_func_write_obj(UOStream *s, CowlAny *obj, CowlPrefixMap *pm) {
    CowlObjectType type = cowl_get_type(obj);
    switch (type) {
        case COWL_OT_STRING: return cowl_write_string(s, obj);
        case COWL_OT_VECTOR: return cowl_func_write_vector(s, obj, pm);
        case COWL_OT_TABLE: return cowl_func_write_table(s, obj, pm);
        case COWL_OT_IRI: return cowl_func_write_iri(s, obj, pm);
        case COWL_OT_LITERAL: return cowl_func_write_literal(s, obj, pm);
        case COWL_OT_FACET_RESTR: return cowl_func_write_facet_restr(s, obj, pm);
        case COWL_OT_ONTOLOGY:
        case COWL_OT_MANAGER:
        case COWL_OT_PREFIX_MAP:
        case COWL_OT_ISTREAM:
        case COWL_OT_OSTREAM: return cowl_write_debug(s, obj);
        case COWL_OT_ANNOTATION: return cowl_func_write_annot_construct(s, obj, pm);
        case COWL_OT_ANNOT_PROP:
        case COWL_OT_CE_CLASS:
        case COWL_OT_DPE_DATA_PROP:
        case COWL_OT_DR_DATATYPE:
        case COWL_OT_I_NAMED:
        case COWL_OT_OPE_OBJ_PROP: return cowl_func_write_entity(s, obj, pm);
        case COWL_OT_I_ANONYMOUS: return cowl_func_write_anon_ind(s, obj);
        case COWL_OT_A_DECL: return cowl_func_write_declaration(s, obj, pm);
        case COWL_OT_A_SUB_OBJ_PROP: return cowl_func_write_sub_obj_prop(s, obj, pm);
        case COWL_OT_A_HAS_KEY: return cowl_func_write_has_key(s, obj, pm);
        case COWL_OT_CE_OBJ_SOME:
        case COWL_OT_CE_OBJ_ALL: return cowl_func_write_obj_quant(s, obj, pm);
        case COWL_OT_CE_DATA_SOME:
        case COWL_OT_CE_DATA_ALL: return cowl_func_write_data_quant(s, obj, pm);
        case COWL_OT_CE_OBJ_MIN_CARD:
        case COWL_OT_CE_OBJ_MAX_CARD:
        case COWL_OT_CE_OBJ_EXACT_CARD:
        case COWL_OT_CE_DATA_MIN_CARD:
        case COWL_OT_CE_DATA_MAX_CARD:
        case COWL_OT_CE_DATA_EXACT_CARD: return cowl_func_write_construct_uint(s, obj, pm);
        default: {
            if (type >= COWL_OT_FIRST_A && type <= COWL_OT_LAST_A) {
                return cowl_func_write_annot_construct(s, obj, pm);
            }
            return cowl_func_write_construct(s, obj, pm);
        }
    }
}
