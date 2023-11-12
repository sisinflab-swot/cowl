/**
 * Defines CowlWriter and declares its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_WRITER_H
#define COWL_WRITER_H

#include "cowl_error.h"
#include "cowl_object_type.h"
#include "cowl_ontology_header.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlLiteral);
cowl_struct_decl(CowlOntology);
cowl_struct_decl(CowlSymTable);
/// @endcond

/// Defines functions that must be implemented by stream writers.
typedef struct CowlStreamWriter {

    /**
     * Pointer to a function that writes an ontology header to an output stream.
     *
     * @param stream Output stream.
     * @param st Symbol table.
     * @param header Ontology header.
     * @return Return code.
     */
    cowl_ret (*write_header)(UOStream *stream, CowlSymTable *st, CowlOntologyHeader header);

    /**
     * Pointer to a function that writes an axiom to an output stream.
     *
     * @param stream Output stream.
     * @param st Symbol table.
     * @param axiom Axiom.
     * @return Return code.
     */
    cowl_ret (*write_axiom)(UOStream *stream, CowlSymTable *st, CowlAnyAxiom *axiom);

    /**
     * Pointer to a function that writes the ontology footer to an output stream.
     *
     * @param stream Output stream.
     * @param st Symbol table.
     * @return Return code.
     */
    cowl_ret (*write_footer)(UOStream *stream, CowlSymTable *st);

} CowlStreamWriter;

/// Defines a writer.
typedef struct CowlWriter {

    /// Name of the writer.
    char const *name;

    /**
     * Pointer to a function that writes an ontology to an output stream.
     *
     * @param stream Output stream.
     * @param ontology Ontology.
     * @return Return code.
     *
     * @note This member is mandatory.
     */
    cowl_ret (*write_ontology)(UOStream *stream, CowlOntology *ontology);

    /**
     * Pointer to a function that writes an object to an output stream.
     *
     * @param stream Output stream.
     * @param object Object to write.
     * @return Return code.
     *
     * @note This member is optional.
     */
    cowl_ret (*write)(UOStream *stream, CowlAny *object);

    /**
     * Contains the streaming implementation of this writer.
     *
     * @note This member is optional.
     */
    CowlStreamWriter stream;

} CowlWriter;

#ifdef COWL_WRITER_FUNCTIONAL

/**
 * Returns the functional syntax writer.
 *
 * @return Functional syntax writer.
 *
 * @public @related CowlWriter
 */
COWL_API
COWL_CONST
CowlWriter cowl_writer_functional(void);

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
COWL_API
cowl_ret cowl_write(UOStream *stream, CowlAny *object);

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
COWL_API
ustream_ret cowl_write_debug(UOStream *stream, CowlAny *object);

/**
 * Writes a string to the specified output stream.
 *
 * @param stream Output stream.
 * @param string String.
 * @return Return code.
 *
 * @public @related CowlWriter
 */
COWL_API
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
COWL_API
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
COWL_API
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
COWL_API
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
COWL_API
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
COWL_INLINE
ustream_ret cowl_write_ustring(UOStream *stream, UString const *string) {
    return uostream_write_string(stream, string, NULL);
}

/**
 * Writes a string to the specified output stream.
 *
 * @param stream [UOStream *] Output stream.
 * @param string [char const *] String.
 * @return [ustream_ret] Return code.
 *
 * @public @related CowlWriter
 */
COWL_INLINE
ustream_ret cowl_write_cstring(UOStream *stream, char const *string) {
    return uostream_write(stream, string, strlen(string), NULL);
}

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
