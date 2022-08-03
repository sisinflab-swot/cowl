/**
 * Defines CowlWriter and declares its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_WRITER_H
#define COWL_WRITER_H

#include "cowl_std.h"
#include "cowl_error.h"
#include "cowl_node_id.h"
#include "cowl_object_type.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlEditor);
cowl_struct_decl(CowlLiteral);
/// @endcond

/// Defines a writer.
typedef struct CowlWriter {

    /// Name of the writer.
    char const *name;

    /**
     * Pointer to a function that allocates the writer's state
     * and reserves any needed resource.
     *
     * @return Writer state.
     *
     * @note This member is optional.
     */
    void* (*alloc)(void);

    /**
     * Pointer to a function that deallocates the writer's state
     * and releases reserved resources.
     *
     * @param state Writer state.
     *
     * @note This member is optional.
     */
    void (*free)(void *state);

    /**
     * Pointer to a function that writes an ontology to an output stream.
     *
     * @param state Writer state.
     * @param stream Output stream.
     * @param editor Ontology editor.
     * @return Return code.
     *
     * @note This member is mandatory.
     */
    cowl_ret (*write_ontology)(void *state, UOStream *stream, CowlEditor *editor);

    /**
     * Pointer to a function that writes an object to an output stream.
     *
     * @param stream Output stream.
     * @param object Object to write.
     * @return Return code.
     *
     * @note This member is optional.
     * @note As denoted by the lack of the state parameter, the writer must be stateless
     *       in order to implement this function.
     */
    cowl_ret (*write)(UOStream *stream, void *object);

} CowlWriter;

#ifdef COWL_WRITER_FUNCTIONAL

/**
 * Returns the functional syntax writer.
 *
 * @return Functional syntax writer.
 *
 * @public @related CowlWriter
 */
COWL_PUBLIC
CowlWriter cowl_writer_get_functional(void);

#endif // COWL_WRITER_FUNCTIONAL

// High-level write functions

/**
 * Writes an object to the specified stream via the default writer.
 *
 * @param stream Output stream.
 * @param object Object.
 * @return Return code.
 *
 * @note If no default writer is set, falls back to `cowl_write_debug`.
 *
 * @public @related CowlWriter
 */
COWL_PUBLIC
cowl_ret cowl_write(UOStream *stream, void *object);

// Low-level write functions

/**
 * Writes a debug representation of an object to the specified output stream.
 *
 * @param stream Output stream.
 * @param object Object.
 * @return Return code.
 *
 * @public @related CowlWriter
 */
COWL_PUBLIC
ustream_ret cowl_write_debug(UOStream *stream, void *object);

/**
 * Writes a string to the specified output stream.
 *
 * @param stream Output stream.
 * @param string String.
 * @return Return code.
 *
 * @public @related CowlWriter
 */
COWL_PUBLIC
ustream_ret cowl_write_string(UOStream *stream, CowlString *string);

/**
 * Writes an IRI to the specified output stream.
 *
 * @param stream Output stream.
 * @param iri IRI.
 * @return Return code.
 *
 * @public @related CowlWriter
 */
COWL_PUBLIC
ustream_ret cowl_write_iri(UOStream *stream, CowlIRI *iri);

/**
 * Writes the object type to the specified output stream.
 *
 * @param stream Output stream.
 * @param type Object type.
 * @return Return code.
 *
 * @public @related CowlWriter
 */
COWL_PUBLIC
ustream_ret cowl_write_object_type(UOStream *stream, CowlObjectType type);

/**
 * Writes an unsigned integer to the specified output stream.
 *
 * @param stream Output stream.
 * @param uint Unsigned integer.
 * @return Return code.
 *
 * @public @related CowlWriter
 */
COWL_PUBLIC
ustream_ret cowl_write_uint(UOStream *stream, ulib_uint uint);

/**
 * Writes an human readable representation of an error to the specified output stream.
 *
 * @param stream Output stream.
 * @param error Error.
 * @return Return code.
 *
 * @public @related CowlWriter
 */
COWL_PUBLIC
ustream_ret cowl_write_error(UOStream *stream, CowlError const *error);

/**
 * Writes a string to the specified output stream.
 *
 * @param stream [UOStream *] Output stream.
 * @param string [UString const *] String.
 * @return [ustream_ret] Return code.
 *
 * @public @related CowlWriter
 */
#define cowl_write_ustring(stream, string) uostream_write_string(stream, string, NULL)

/**
 * Writes a string literal to the specified output stream.
 *
 * @param stream [UOStream *] Output stream.
 * @param string [char const[]] String.
 * @return [ustream_ret] Return code.
 *
 * @public @related CowlWriter
 */
#define cowl_write_static(stream, string) uostream_write_literal(stream, string, NULL)

COWL_END_DECLS

#endif // COWL_WRITER_H
