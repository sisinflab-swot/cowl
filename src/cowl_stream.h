/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_STREAM_H
#define COWL_STREAM_H

#include "cowl_std.h"
#include "cowl_types.h"

COWL_BEGIN_DECLS

#define cowl_stream_write_static(stream, literal) uostream_write_literal(stream, literal, NULL)

ustream_ret cowl_stream_write_object(UOStream *s, void *obj);
ustream_ret cowl_stream_write_composite(UOStream *s, void *obj);
ustream_ret cowl_stream_write_composite_uint(UOStream *s, void *obj);
ustream_ret cowl_stream_write_object_debug(UOStream *s, CowlObject *obj);
ustream_ret cowl_stream_write_string(UOStream *stream, CowlString *string);
ustream_ret cowl_stream_write_ustring(UOStream *stream, UString string);
ustream_ret cowl_stream_write_iri(UOStream *s, CowlIRI *iri);
ustream_ret cowl_stream_write_iri_no_brackets(UOStream *s, CowlIRI *iri);
ustream_ret cowl_stream_write_primitive(UOStream *s, void *primitive);
ustream_ret cowl_stream_write_ontology(UOStream *s, CowlOntology *onto);
ustream_ret cowl_stream_write_ontology_id(UOStream *s, CowlOntologyId *id);
ustream_ret cowl_stream_write_literal(UOStream *s, CowlLiteral *literal);
ustream_ret cowl_stream_write_node_id(UOStream *s, CowlNodeId id);
ustream_ret cowl_stream_write_uint(UOStream *s, uint64_t uint);
ustream_ret cowl_stream_write_error(UOStream *s, CowlError const *error);
ustream_ret cowl_stream_write_set(UOStream *s, CowlSet *set);
ustream_ret cowl_stream_write_vector(UOStream *s, CowlVector *vec);

COWL_END_DECLS

#endif // COWL_STREAM_H
