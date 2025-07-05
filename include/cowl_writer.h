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

#include "cowl_any.h"
#include "cowl_attrs.h"
#include "cowl_error.h"
#include "cowl_object_type.h"
#include "cowl_ontology_header.h"
#include "cowl_ret.h"
#include "cowl_utils.h"
#include "ulib.h"
#include <string.h>

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlLiteral);
cowl_struct_decl(CowlOntology);
cowl_struct_decl(CowlSymTable);
/// @endcond

/// State of the stream writer.
typedef struct CowlStreamState {

    /// Writer context.
    void *ctx;

    /// Symbol table.
    CowlSymTable *st;

} CowlStreamState;

/// Defines functions that must be implemented by stream writers.
typedef struct CowlStreamWriter {

    /**
     * Pointer to a function that writes an ontology header to an output stream.
     *
     * @param state Stream writer state.
     * @param stream Output stream.
     * @param header Ontology header.
     * @return Return code.
     *
     * @note This function is called only once, before any axiom is written.
     */
    cowl_ret (*write_header)(CowlStreamState state, UOStream *stream, CowlOntologyHeader header);

    /**
     * Pointer to a function that writes an axiom to an output stream.
     *
     * @param state Stream writer state.
     * @param stream Output stream.
     * @param axiom Axiom.
     * @return Return code.
     *
     * @note This function is called for each axiom in the ontology.
     */
    cowl_ret (*write_axiom)(CowlStreamState state, UOStream *stream, CowlAnyAxiom *axiom);

    /**
     * Pointer to a function that writes the ontology footer to an output stream.
     *
     * @param state Stream writer state.
     * @param stream Output stream.
     * @return Return code.
     *
     * @note This function is called only once, after all axioms have been written.
     */
    cowl_ret (*write_footer)(CowlStreamState state, UOStream *stream);

} CowlStreamWriter;

/// Defines a writer.
typedef struct CowlWriter {

    /// Name of the writer.
    char const *name;

    /// Writer context.
    void *ctx;

    /**
     * Pointer to a function that writes an ontology to an output stream.
     *
     * @param ctx Writer context.
     * @param stream Output stream.
     * @param onto Ontology.
     * @return Return code.
     *
     * @note Should only be implemented by writers that either require the ontology object
     *       as a whole, or that can more efficiently encode the ontology if they
     *       have access to it. In all other cases, it is best left unimplemented.
     */
    cowl_ret (*write_ontology)(void *ctx, UOStream *stream, CowlOntology *onto);

    /**
     * Pointer to a function that writes an object to an output stream.
     *
     * @param ctx Writer context.
     * @param stream Output stream.
     * @param object Object to write.
     * @return Return code.
     *
     * @note Should only be implemented by writers used as default writers
     *       (i.e. passed to @func{cowl_set_writer}), so that they are able to write
     *       the string representation of arbitrary objects.
     */
    cowl_ret (*write)(void *ctx, UOStream *stream, CowlAny *object);

    /**
     * Pointer to a function that frees the writer context.
     *
     * @param ctx Writer context.
     *
     * @note This member is optional. If not set, the writer context will not be freed.
     */
    void (*free)(void *ctx);

    /**
     * Contains the streaming implementation of this writer.
     *
     * @note This is the preferred implementation for writers.
     */
    CowlStreamWriter stream;

} CowlWriter;

/**
 * @defgroup CowlWriter CowlWriter API
 * @{
 */

#ifdef COWL_WRITER_FUNCTIONAL

/**
 * Returns the functional syntax writer.
 *
 * @return Functional syntax writer.
 */
COWL_API
COWL_CONST
CowlWriter cowl_writer_functional(void);

#endif // COWL_WRITER_FUNCTIONAL

/**
 * Returns the default writer.
 *
 * @return Default writer.
 *
 * @alias CowlWriter cowl_writer_default(void);
 */
#if defined(COWL_DEFAULT_WRITER)
#define cowl_writer_default ULIB_MACRO_CONCAT(cowl_writer_, COWL_DEFAULT_WRITER)
#elif defined(COWL_WRITER_FUNCTIONAL)
#define cowl_writer_default cowl_writer_functional
#else
#define cowl_writer_default p_cowl_writer_invalid
#endif

/**
 * Frees the writer context.
 *
 * @param writer The writer.
 */
COWL_API
void cowl_writer_free_ctx(CowlWriter *writer);

/**
 * Checks whether the writer supports stream writing.
 *
 * @param writer The writer.
 * @return True if the writer supports stream writing, false otherwise.
 */
COWL_PURE
COWL_INLINE
bool cowl_writer_can_write_stream(CowlWriter const *writer) {
    return writer->stream.write_header && writer->stream.write_axiom && writer->stream.write_footer;
}

/**
 * Checks whether the writer supports writing arbitrary objects.
 *
 * @param writer The writer.
 * @return True if the writer supports writing objects, false otherwise.
 */
COWL_PURE
COWL_INLINE
bool cowl_writer_can_write_object(CowlWriter const *writer) {
    return writer->write != NULL;
}

/**
 * Checks whether the writer has a specialized method to write ontologies.
 *
 * @param writer The writer.
 * @return True if the writer has a specialized method to write ontologies, false otherwise.
 */
COWL_PURE
COWL_INLINE
bool cowl_writer_can_write_ontology(CowlWriter const *writer) {
    return writer->write_ontology != NULL;
}

// High-level write functions

/**
 * Writes an object to the specified stream via the default writer.
 *
 * @param stream Output stream.
 * @param object Object.
 * @return Return code.
 *
 * @note If no default writer is set, falls back to @func{cowl_write_debug}.
 */
COWL_API
cowl_ret cowl_write(UOStream *stream, CowlAny *object);

/**
 * Writes a debug representation of an object to the specified output stream.
 *
 * @param stream Output stream.
 * @param object Object.
 * @return Return code.
 */
COWL_API
cowl_ret cowl_write_debug(UOStream *stream, CowlAny *object);

// Low-level write functions

/**
 * Writes a string to the specified output stream.
 *
 * @param stream Output stream.
 * @param string String.
 * @return Return code.
 */
COWL_API
ulib_ret cowl_write_string(UOStream *stream, CowlString *string);

/**
 * Writes an IRI to the specified output stream.
 *
 * @param stream Output stream.
 * @param iri IRI.
 * @return Return code.
 *
 * @note The IRI is written as the concatenation of the namespace and the remainder,
 *       without any additional markup (e.g. angle brackets).
 */
COWL_API
ulib_ret cowl_write_iri(UOStream *stream, CowlIRI *iri);

/**
 * Writes the object type to the specified output stream.
 *
 * @param stream Output stream.
 * @param type Object type.
 * @return Return code.
 */
COWL_API
ulib_ret cowl_write_object_type(UOStream *stream, CowlObjectType type);

/**
 * Writes an unsigned integer to the specified output stream.
 *
 * @param stream Output stream.
 * @param uint Unsigned integer.
 * @return Return code.
 */
COWL_API
ulib_ret cowl_write_uint(UOStream *stream, ulib_uint uint);

/**
 * Writes an human readable representation of an error to the specified output stream.
 *
 * @param stream Output stream.
 * @param error Error.
 * @return Return code.
 */
COWL_API
ulib_ret cowl_write_error(UOStream *stream, CowlError const *error);

/**
 * Writes a string to the specified output stream.
 *
 * @param stream Output stream.
 * @param string String.
 * @return Return code.
 */
COWL_INLINE
ulib_ret cowl_write_ustring(UOStream *stream, UString const *string) {
    return uostream_write_string(stream, string, NULL);
}

/**
 * Writes a string to the specified output stream.
 *
 * @param stream Output stream.
 * @param string String.
 * @return Return code.
 */
COWL_INLINE
ulib_ret cowl_write_cstring(UOStream *stream, char const *string) {
    return uostream_write_buf(stream, string, NULL);
}

/**
 * Writes a string literal to the specified output stream.
 *
 * @param stream @ctype{#UOStream *} Output stream.
 * @param string @ctype{char const []} String literal.
 * @return @type{ustream_ret} Return code.
 */
#define cowl_write_static(stream, string) uostream_write_literal(stream, string, NULL)

/// @}

// Private API

COWL_API
COWL_CONST
CowlWriter p_cowl_writer_invalid(void);

COWL_END_DECLS

#endif // COWL_WRITER_H
