/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <https://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 */

#include "cowl_anon_ind.h"
#include "cowl_any.h"
#include "cowl_attrs.h"
#include "cowl_axiom.h"
#include "cowl_config.h"
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
#include "cowl_string.h"
#include "cowl_sub_obj_prop_axiom.h"
#include "cowl_table.h"
#include "cowl_vector.h"
#include "cowl_vocab.h"
#include "cowl_writer.h"
#include "ulib.h"
#include <stddef.h>

typedef struct FuncEncoder {
    CowlPrefixMap *pm;
    UOStream *stream;
} FuncEncoder;

static inline FuncEncoder encoder_init(void) {
    return (FuncEncoder)ulib_zero_init;
}

static inline void encoder_deinit(FuncEncoder *e) {
    cowl_release(e->pm);
}

static inline cowl_ret encoder_state(FuncEncoder *e) {
    return cowl_ret_from_ulib(e->stream->state);
}

static inline void encoder_set_prefix_map(FuncEncoder *e, CowlPrefixMap *pm) {
    if (e->pm == pm) return;
    cowl_release(e->pm);
    if (pm) e->pm = cowl_retain(pm);
}

#define write_static(e, str) cowl_write_static((e)->stream, str)

static inline void write_uint(FuncEncoder *e, ulib_uint value) {
    cowl_write_uint(e->stream, value);
}

static inline void write_object_type(FuncEncoder *e, CowlObjectType type) {
    cowl_write_object_type(e->stream, type);
}

static inline void write_string(FuncEncoder *e, CowlString *str) {
    cowl_write_string(e->stream, str);
}

static void write_obj(FuncEncoder *e, CowlAny *obj);

static void write_fields(FuncEncoder *e, CowlAny *obj) {
    unsigned n;
    CowlAny **fields = cowl_get_fields(obj, false, &n);
    write_obj(e, fields[0]);

    for (unsigned i = 1; i < n; ++i) {
        write_static(e, " ");
        write_obj(e, fields[i]);
    }
}

static void write_fields_opt(FuncEncoder *e, CowlAny *obj) {
    write_fields(e, obj);
    CowlAny *opt = cowl_get_opt_field(obj);
    if (opt) {
        write_static(e, " ");
        write_obj(e, opt);
    }
}

static void write_opt_fields(FuncEncoder *e, CowlAny *obj) {
    CowlAny *opt = cowl_get_opt_field(obj);
    if (opt) {
        write_obj(e, opt);
        write_static(e, " ");
    }
    write_fields(e, obj);
}

static void write_construct(FuncEncoder *e, CowlAny *obj) {
    write_object_type(e, cowl_get_type(obj));
    write_static(e, "(");
    write_fields_opt(e, obj);
    write_static(e, ")");
}

static void write_construct_uint(FuncEncoder *e, CowlAny *obj) {
    write_object_type(e, cowl_get_type(obj));
    write_static(e, "(");
    write_uint(e, cowl_get_uint_field(obj));
    write_static(e, " ");
    write_fields_opt(e, obj);
    write_static(e, ")");
}

static void write_annot_construct(FuncEncoder *e, CowlAny *obj) {
    write_object_type(e, cowl_get_type(obj));
    write_static(e, "(");
    write_opt_fields(e, obj);
    write_static(e, ")");
}

static void write_uvec(FuncEncoder *e, UVec(CowlObjectPtr) const *vec) {
    ulib_uint count = uvec_count(CowlObjectPtr, vec);
    if (!count) return;

    CowlAny **data = uvec_data(CowlObjectPtr, vec);
    write_obj(e, data[0]);

    for (ulib_uint i = 1; i < count; ++i) {
        write_static(e, " ");
        write_obj(e, data[i]);
    }
}

static void write_vector(FuncEncoder *e, CowlVector *vec) {
    if (vec) write_uvec(e, cowl_vector_get_data(vec));
}

static void write_table(FuncEncoder *e, CowlTable *table) {
    if (!table) return;

    ulib_uint current = 0;
    ulib_uint last = cowl_table_count(table) - 1;

    cowl_table_foreach (table, obj) {
        write_obj(e, *obj.key);
        if (obj.val && *obj.val) {
            write_static(e, ":");
            write_obj(e, *obj.val);
        }
        if (current++ < last) write_static(e, " ");
    }
}

static void write_full_iri(FuncEncoder *e, CowlIRI *iri) {
    write_static(e, "<");
    cowl_write_iri(e->stream, iri);
    write_static(e, ">");
}

static void write_short_iri(FuncEncoder *e, CowlString *pfx, CowlString *rem) {
    write_string(e, pfx);
    write_static(e, ":");
    write_string(e, rem);
}

static void write_iri(FuncEncoder *e, CowlIRI *iri) {
    CowlString *prefix;

    if (e->pm && cowl_iri_has_rem(iri) &&
        (prefix = cowl_prefix_map_get_prefix(e->pm, cowl_iri_get_ns(iri)))) {
        write_short_iri(e, prefix, cowl_iri_get_rem(iri));
        return;
    }

    write_full_iri(e, iri);
}

static void write_from_to(FuncEncoder *e, char const *from, char const *to) {
    uostream_write(e->stream, from, to - from, NULL);
}

static void write_literal_value(FuncEncoder *e, CowlLiteral *literal) {
    char const *str = cowl_string_get_cstring(cowl_literal_get_value(literal));
    char const *cur;
    for (cur = str; *cur; ++cur) {
        if (*cur == '"' || *cur == '\\') {
            write_from_to(e, str, cur);
            write_static(e, "\\");
            str = cur;
        }
    }
    write_from_to(e, str, cur);
}

static void write_literal(FuncEncoder *e, CowlLiteral *literal) {
    write_static(e, "\"");
    write_literal_value(e, literal);
    write_static(e, "\"");

    CowlDatatype *dt = cowl_literal_get_datatype(literal);
    if (cowl_primitive_equals(dt, cowl_rdf_vocab()->dt.lang_string)) {
        write_static(e, "@");
        write_string(e, cowl_literal_get_lang(literal));
    } else if (!cowl_primitive_equals(dt, cowl_xsd_vocab()->dt.string)) {
        write_static(e, "^^");
        write_iri(e, cowl_datatype_get_iri(dt));
    }
}

static void write_anon_ind(FuncEncoder *e, CowlAnonInd *ind) {
    write_static(e, "_:");
    write_string(e, cowl_anon_ind_get_id(ind));
}

static void write_entity(FuncEncoder *e, CowlAnyEntity *entity) {
    write_iri(e, cowl_entity_get_iri(entity));
}

static void write_declaration(FuncEncoder *e, CowlDeclAxiom *decl) {
    write_object_type(e, COWL_OT_A_DECL);
    write_static(e, "(");

    CowlVector *annot = cowl_axiom_get_annot(decl);
    if (annot) {
        write_vector(e, annot);
        write_static(e, " ");
    }

    CowlEntity *entity = cowl_decl_axiom_get_entity(decl);
    write_object_type(e, cowl_get_type(entity));
    write_static(e, "(");
    write_iri(e, cowl_entity_get_iri(entity));
    write_static(e, ")");
    write_static(e, ")");
}

static void write_obj_quant(FuncEncoder *e, CowlObjQuant *restr) {
    write_object_type(e, cowl_get_type(restr));
    write_static(e, "(");
    write_obj(e, cowl_obj_quant_get_prop(restr));
    write_static(e, " ");
    write_obj(e, cowl_obj_quant_get_filler(restr));
    write_static(e, ")");
}

static void write_data_quant(FuncEncoder *e, CowlDataQuant *restr) {
    write_object_type(e, cowl_get_type(restr));
    write_static(e, "(");
    write_obj(e, cowl_data_quant_get_prop(restr));
    write_static(e, " ");
    write_obj(e, cowl_data_quant_get_range(restr));
    write_static(e, ")");
}

static void write_obj_prop_chain(FuncEncoder *e, CowlVector *chain) {
    write_static(e, "ObjectPropertyChain");
    write_static(e, "(");
    write_vector(e, chain);
    write_static(e, ")");
}

static void write_sub_obj_prop(FuncEncoder *e, CowlSubObjPropAxiom *axiom) {
    write_object_type(e, COWL_OT_A_SUB_OBJ_PROP);
    write_static(e, "(");

    void *it = cowl_axiom_get_annot(axiom);

    if (it) {
        write_vector(e, it);
        write_static(e, " ");
    }

    it = cowl_sub_obj_prop_axiom_get_sub(axiom);

    if (cowl_get_type(it) == COWL_OT_VECTOR) {
        write_obj_prop_chain(e, it);
    } else {
        write_entity(e, it);
    }

    write_static(e, " ");
    write_obj(e, cowl_sub_obj_prop_axiom_get_super(axiom));

    write_static(e, ")");
}

static void write_has_key(FuncEncoder *e, CowlHasKeyAxiom *axiom) {
    write_object_type(e, COWL_OT_A_HAS_KEY);
    write_static(e, "(");

    CowlVector *annot = cowl_axiom_get_annot(axiom);
    if (annot) {
        write_vector(e, annot);
        write_static(e, " ");
    }

    write_obj(e, cowl_has_key_axiom_get_cls_exp(axiom));
    write_static(e, " ");

    write_static(e, "(");
    write_vector(e, cowl_has_key_axiom_get_obj_props(axiom));
    write_static(e, ")");
    write_static(e, " ");
    write_static(e, "(");
    write_vector(e, cowl_has_key_axiom_get_data_props(axiom));
    write_static(e, ")");

    write_static(e, ")");
}

static void write_facet_restr(FuncEncoder *e, void *fr) {
    write_fields_opt(e, fr);
}

static void write_import(FuncEncoder *e, CowlIRI *iri) {
    write_static(e, "Import");
    write_static(e, "(");
    write_full_iri(e, iri);
    write_static(e, ")");
}

static void write_onto_iri_version(FuncEncoder *e, CowlIRI *iri, CowlIRI *version) {
    if (iri) write_full_iri(e, iri);
    if (version) {
        if (iri) write_static(e, " ");
        write_full_iri(e, version);
    }
}

static void write_prefix(FuncEncoder *e, CowlString *prefix, CowlString *ns) {
    write_static(e, "Prefix");
    write_static(e, "(");
    write_string(e, prefix);
    write_static(e, ":=<");
    write_string(e, ns);
    write_static(e, ">");
    write_static(e, ")");
}

static void write_header(FuncEncoder *e, CowlOntologyHeader *header) {
    CowlTable *prefixes = cowl_prefix_map_get_table(header->pm, false);

    cowl_table_foreach (prefixes, p) {
        if (cowl_vocab_is_reserved_prefix(*p.key)) continue;
        write_prefix(e, *p.key, *p.val);
        write_static(e, "\n");
    }

    write_static(e, "Ontology");
    write_static(e, "(");

    write_onto_iri_version(e, header->iri, header->version);
    write_static(e, "\n");

    if (header->imports) {
        uvec_foreach (CowlObjectPtr, header->imports, import) {
            write_import(e, *import.item);
            write_static(e, "\n");
        }
    }

    if (header->annotations) {
        uvec_foreach (CowlObjectPtr, header->annotations, annot) {
            write_obj(e, *annot.item);
            write_static(e, "\n");
        }
    }
}

static void write_footer(FuncEncoder *e) {
    write_static(e, ")");
    write_static(e, "\n");
}

static void write_obj(FuncEncoder *e, CowlAny *obj) {
    CowlObjectType type = cowl_get_type(obj);
    switch (type) {
        case COWL_OT_STRING: write_string(e, obj); return;
        case COWL_OT_VECTOR: write_vector(e, obj); return;
        case COWL_OT_TABLE: write_table(e, obj); return;
        case COWL_OT_IRI: write_iri(e, obj); return;
        case COWL_OT_LITERAL: write_literal(e, obj); return;
        case COWL_OT_FACET_RESTR: write_facet_restr(e, obj); return;
        case COWL_OT_ONTOLOGY:
        case COWL_OT_PREFIX_MAP:
        case COWL_OT_READER:
        case COWL_OT_WRITER: cowl_write_debug(e->stream, obj); return;
        case COWL_OT_ANNOTATION: write_annot_construct(e, obj); return;
        case COWL_OT_ANNOT_PROP:
        case COWL_OT_CE_CLASS:
        case COWL_OT_DPE_DATA_PROP:
        case COWL_OT_DR_DATATYPE:
        case COWL_OT_I_NAMED:
        case COWL_OT_OPE_OBJ_PROP: write_entity(e, obj); return;
        case COWL_OT_I_ANONYMOUS: write_anon_ind(e, obj); return;
        case COWL_OT_A_DECL: write_declaration(e, obj); return;
        case COWL_OT_A_SUB_OBJ_PROP: write_sub_obj_prop(e, obj); return;
        case COWL_OT_A_HAS_KEY: write_has_key(e, obj); return;
        case COWL_OT_CE_OBJ_SOME:
        case COWL_OT_CE_OBJ_ALL: write_obj_quant(e, obj); return;
        case COWL_OT_CE_DATA_SOME:
        case COWL_OT_CE_DATA_ALL: write_data_quant(e, obj); return;
        case COWL_OT_CE_OBJ_MIN_CARD:
        case COWL_OT_CE_OBJ_MAX_CARD:
        case COWL_OT_CE_OBJ_EXACT_CARD:
        case COWL_OT_CE_DATA_MIN_CARD:
        case COWL_OT_CE_DATA_MAX_CARD:
        case COWL_OT_CE_DATA_EXACT_CARD: write_construct_uint(e, obj); return;
        default: {
            if (type >= COWL_OT_FIRST_A && type <= COWL_OT_LAST_A) {
                write_annot_construct(e, obj);
            } else {
                write_construct(e, obj);
            }
            return;
        }
    }
}

static cowl_ret func_write(cowl_unused void *ctx, UOStream *stream, CowlAny *object) {
    FuncEncoder e = encoder_init();
    e.pm = cowl_get_prefix_map();
    e.stream = stream;
    write_obj(&e, object);
    return encoder_state(&e);
}

static cowl_ret func_write_header(void *ctx, UOStream *stream, CowlOntologyHeader header) {
    if (!ctx) return COWL_ERR_MEM;
    FuncEncoder *e = ctx;
    e->stream = stream;
    encoder_set_prefix_map(e, header.pm);
    write_header(e, &header);
    return encoder_state(e);
}

static cowl_ret func_write_axiom(void *ctx, UOStream *stream, CowlAnyAxiom *axiom) {
    if (!ctx) return COWL_ERR_MEM;
    FuncEncoder *e = ctx;
    e->stream = stream;
    write_obj(e, axiom);
    cowl_write_static(stream, "\n");
    return encoder_state(e);
}

static cowl_ret func_write_footer(void *ctx, UOStream *stream) {
    if (!ctx) return COWL_ERR_MEM;
    FuncEncoder *e = ctx;
    e->stream = stream;
    write_footer(e);
    return encoder_state(e);
}

static void func_free(void *ctx) {
    encoder_deinit(ctx);
    ulib_free(ctx);
}

CowlWriter *cowl_writer_functional(void) {
    FuncEncoder *e = ulib_alloc(e);
    if (!e) return NULL;
    *e = encoder_init();
    return cowl_writer((CowlWriterImpl){
        .ctx = e,
        .name = "functional",
        .write = func_write,
        .write_header = func_write_header,
        .write_axiom = func_write_axiom,
        .write_footer = func_write_footer,
        .free = func_free,
    });
}
