/**
 * Declares CowlWriter and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2025 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_WRITER_H
#define COWL_WRITER_H

#include "cowl_any.h"
#include "cowl_attrs.h"
#include "cowl_object_type.h"
#include "cowl_ontology_header.h"
#include "cowl_ret.h"
#include "cowl_utils.h"
#include "ulib.h"
#include <stddef.h>

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlError);
cowl_struct_decl(CowlOntology);
/// @endcond

/**
 * A writer is an object that can write ontologies to an output stream.
 *
 * @superstruct{CowlObject}
 * @struct CowlWriter
 */
cowl_struct_decl(CowlWriter);

/// Writer implementation.
typedef struct CowlWriterImpl {

    /// Name of the writer.
    char const *name;

    /// Writer context.
    void *ctx;

    /**
     * Pointer to a function that writes an ontology header to an output stream.
     *
     * @param ctx Context.
     * @param stream Output stream.
     * @param header Ontology header.
     * @return Return code.
     *
     * @note This function is called only once, before any axiom is written.
     */
    cowl_ret (*write_header)(void *ctx, UOStream *stream, CowlOntologyHeader header);

    /**
     * Pointer to a function that writes an axiom to an output stream.
     *
     * @param ctx Context.
     * @param stream Output stream.
     * @param axiom Axiom.
     * @return Return code.
     *
     * @note This function is called for each axiom in the ontology.
     */
    cowl_ret (*write_axiom)(void *ctx, UOStream *stream, CowlAnyAxiom *axiom);

    /**
     * Pointer to a function that writes the ontology footer to an output stream.
     *
     * @param ctx Context.
     * @param stream Output stream.
     * @return Return code.
     *
     * @note This function is called only once, after all axioms have been written.
     */
    cowl_ret (*write_footer)(void *ctx, UOStream *stream);

    /**
     * Pointer to a function that writes an ontology to an output stream.
     *
     * @param ctx Context.
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
     * @param ctx Context.
     * @param stream Output stream.
     * @param object Object to write.
     * @return Return code.
     *
     * @note Should only be implemented if the writer is intended to be used as the default writer,
     *       so that it is able to write the string representation of arbitrary objects.
     */
    cowl_ret (*write)(void *ctx, UOStream *stream, CowlAny *object);

    /**
     * Pointer to a function that frees the writer context.
     *
     * @param ctx Context.
     *
     * @note This member is optional. If not set, the writer context will not be freed.
     */
    void (*free)(void *ctx);

} CowlWriterImpl;

/**
 * @defgroup CowlWriter CowlWriter API
 * @{
 */

#ifdef COWL_WRITER_FUNCTIONAL

/**
 * Returns the functional syntax writer.
 *
 * @return Functional syntax writer, or NULL on error.
 */
COWL_API
COWL_RETAINED
CowlWriter *cowl_writer_functional(void);

#endif // COWL_WRITER_FUNCTIONAL

/**
 * Returns the default writer.
 *
 * @return Default writer, or NULL on error.
 */
COWL_API
COWL_RETAINED
CowlWriter *cowl_writer_default(void);

/**
 * Returns a new writer.
 *
 * @param impl Writer implementation.
 * @return Writer, or NULL on error.
 */
COWL_API
COWL_RETAINED
CowlWriter *cowl_writer(CowlWriterImpl impl);

/**
 * Returns the name of the writer.
 *
 * @param writer The writer.
 * @return Name of the writer.
 */
COWL_API
COWL_PURE
char const *cowl_writer_get_name(CowlWriter *writer);

/**
 * Returns the implementation of the writer.
 *
 * @param writer The writer.
 * @return Writer implementation.
 */
COWL_API
COWL_PURE
CowlWriterImpl *cowl_writer_get_impl(CowlWriter *writer);

/**
 * Checks whether the writer supports stream writing.
 *
 * @param writer The writer.
 * @return True if the writer supports stream writing, false otherwise.
 */
COWL_API
COWL_PURE
bool cowl_writer_can_write_stream(CowlWriter *writer);

/**
 * Checks whether the writer supports writing arbitrary objects.
 *
 * @param writer The writer.
 * @return True if the writer supports writing objects, false otherwise.
 */
COWL_API
COWL_PURE
bool cowl_writer_can_write_object(CowlWriter *writer);

/**
 * Checks whether the writer has a specialized method to write ontologies.
 *
 * @param writer The writer.
 * @return True if the writer has a specialized method to write ontologies, false otherwise.
 */
COWL_API
COWL_PURE
bool cowl_writer_can_write_ontology(CowlWriter *writer);

/**
 * Writes an ontology to the specified output stream.
 *
 * @param writer The writer.
 * @param stream Output stream.
 * @param onto Ontology.
 * @return Return code.
 */
COWL_API
cowl_ret cowl_writer_write_ontology(CowlWriter *writer, UOStream *stream, CowlOntology *onto);

/**
 * Writes an ontology to the specified file path.
 *
 * @param writer The writer.
 * @param path File path.
 * @param onto Ontology.
 * @return Return code.
 */
COWL_API
cowl_ret cowl_writer_write_ontology_to_path(CowlWriter *writer, UString path, CowlOntology *onto);

/**
 * Writes an ontology header to the specified output stream.
 *
 * @param writer The writer.
 * @param stream Output stream.
 * @param header Ontology header.
 * @return Return code.
 */
COWL_API
cowl_ret cowl_writer_write_header(CowlWriter *writer, UOStream *stream, CowlOntologyHeader header);

/**
 * Writes an axiom to the specified output stream.
 *
 * @param writer The writer.
 * @param stream Output stream.
 * @param axiom Axiom.
 * @return Return code.
 */
COWL_API
cowl_ret cowl_writer_write_axiom(CowlWriter *writer, UOStream *stream, CowlAnyAxiom *axiom);

/**
 * Writes the ontology footer to the specified output stream.
 *
 * @param writer The writer.
 * @param stream Output stream.
 * @return Return code.
 */
COWL_API
cowl_ret cowl_writer_write_footer(CowlWriter *writer, UOStream *stream);

/**
 * Writes an object to the specified output stream.
 *
 * @param writer The writer.
 * @param stream Output stream.
 * @param object Object to write.
 * @return Return code.
 */
COWL_API
cowl_ret cowl_writer_write(CowlWriter *writer, UOStream *stream, CowlAny *object);

// High-level write functions

/**
 * Writes an object to the specified stream via the default writer.
 *
 * @param stream Output stream.
 * @param object Object.
 * @return Return code.
 *
 * @note If there is no default writer, falls back to @func{cowl_write_debug}.
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
 * Writes an error to the specified output stream.
 *
 * @param stream Output stream.
 * @param error Error information.
 * @return Return code.
 */
COWL_API
ulib_ret cowl_write_error(UOStream *stream, CowlError const *error);

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
    return uostream_write_cstring(stream, string, NULL);
}

/**
 * Writes a string literal to the specified output stream.
 *
 * @param stream Output stream.
 * @param string String literal.
 * @return Return code.
 *
 * @alias ulib_ret cowl_write_static(UOStream *stream, char const string[]);
 */
#define cowl_write_static(stream, string) uostream_write_literal(stream, string, NULL)

/// @}

COWL_END_DECLS

#endif // COWL_WRITER_H
