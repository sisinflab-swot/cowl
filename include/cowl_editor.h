/**
 * Declares CowlEditor and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_EDITOR_H
#define COWL_EDITOR_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlAnnotation);
cowl_struct_decl(CowlAnonInd);
cowl_struct_decl(CowlAxiom);
cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlOntology);
cowl_struct_decl(CowlEditor);
/// @endcond

/**
 * Provides ontology editing primitives.
 *
 * @struct CowlEditor
 */

/**
 * Sets the IRI of the ontology.
 *
 * @param editor The editor.
 * @param iri Ontology IRI.
 *
 * @public @memberof CowlEditor
 */
COWL_PUBLIC
void cowl_editor_set_iri(CowlEditor *editor, CowlIRI *iri);

/**
 * Sets the version IRI of the ontology.
 *
 * @param editor The editor.
 * @param version Version IRI.
 *
 * @public @memberof CowlEditor
 */
COWL_PUBLIC
void cowl_editor_set_version(CowlEditor *editor, CowlIRI *version);

/**
 * Adds an annotation to the ontology.
 *
 * @param editor The editor.
 * @param annot Annotation.
 * @return Return code.
 *
 * @public @memberof CowlEditor
 */
COWL_PUBLIC
cowl_ret cowl_editor_add_annot(CowlEditor *editor, CowlAnnotation *annot);

/**
 * Adds an import to the ontology.
 *
 * @param editor The editor.
 * @param iri IRI of the imported ontology.
 * @return Return code.
 *
 * @public @memberof CowlEditor
 */
COWL_PUBLIC
cowl_ret cowl_editor_add_import(CowlEditor *editor, CowlIRI *iri);

/**
 * Adds an axiom to the ontology.
 *
 * @param editor The editor.
 * @param axiom Axiom.
 * @return Return code.
 *
 * @public @memberof CowlEditor
 */
COWL_PUBLIC
cowl_ret cowl_editor_add_axiom(CowlEditor *editor, CowlAxiom *axiom);

/**
 * Registers the specified prefix-namespace mapping.
 * 
 * @param editor The editor. 
 * @param prefix The prefix.
 * @param ns The namespace.
 * @return Return code.
 *
 * @public @memberof CowlEditor
 */
COWL_PUBLIC
cowl_ret cowl_editor_register_ns(CowlEditor *editor, CowlString *prefix, CowlString *ns);

/**
 * Retrieves the full IRI associated with the specified short IRI.
 *
 * @param editor The editor.
 * @param ns The short namespace.
 * @param rem The remainder.
 * @return IRI instance, or NULL on error.
 *
 * @public @memberof CowlEditor
 */
COWL_PUBLIC
CowlIRI* cowl_editor_get_full_iri(CowlEditor *editor, UString ns, UString rem);

/**
 * Retrieves the full IRI associated with the specified short IRI.
 *
 * @param editor The editor.
 * @param short_iri The short IRI.
 * @return IRI instance, or NULL on error.
 *
 * @public @memberof CowlEditor
 */
COWL_PUBLIC
CowlIRI* cowl_editor_parse_full_iri(CowlEditor *editor, UString short_iri);

/**
 * Returns the anonymous individual associated with the specified identifier.
 *
 * @param editor The editor.
 * @param id The identifier.
 * @return Anonymous individual instance, or NULL on error.
 *
 * @public @memberof CowlEditor
 */
COWL_PUBLIC
CowlAnonInd* cowl_editor_get_anon_ind(CowlEditor *editor, UString id);

/**
 * Handles the specified error through the user-provided error handler.
 *
 * @param editor The editor.
 * @param code Error code.
 * @param description Error description.
 *
 * @public @memberof CowlEditor
 */
COWL_PUBLIC
void cowl_editor_handle_error(CowlEditor *editor, cowl_ret code, UString description);

/**
 * Handles a generic error with the specified code through the user-provided error handler.
 *
 * @param editor The editor.
 * @param code Error code.
 *
 * @public @memberof CowlEditor
 */
COWL_PUBLIC
void cowl_editor_handle_error_type(CowlEditor *editor, cowl_ret code);

COWL_END_DECLS

#endif // COWL_EDITOR_H
