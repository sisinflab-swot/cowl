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

#include "cowl_table.h"

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
 * Gets the ontology managed by this editor.
 *
 * @param editor The editor.
 * @return Ontology.
 *
 * @public @memberof CowlEditor
 */
COWL_PUBLIC
CowlOntology* cowl_editor_get_ontology(CowlEditor *editor);

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
 * Removes an annotation from the ontology.
 *
 * @param editor The editor.
 * @param annot Annotation.
 * @return Return code.
 *
 * @public @memberof CowlEditor
 */
COWL_PUBLIC
cowl_ret cowl_editor_remove_annot(CowlEditor *editor, CowlAnnotation *annot);

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
 * Removes an import from the ontology.
 *
 * @param editor The editor.
 * @param iri IRI of the imported ontology.
 * @return Return code.
 *
 * @public @memberof CowlEditor
 */
COWL_PUBLIC
cowl_ret cowl_editor_remove_import(CowlEditor *editor, CowlIRI *iri);

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
 * Removes an axiom from the ontology.
 *
 * @param editor The editor.
 * @param axiom Axiom.
 * @return Return code.
 *
 * @public @memberof CowlEditor
 */
COWL_PUBLIC
cowl_ret cowl_editor_remove_axiom(CowlEditor *editor, CowlAxiom *axiom);

/**
 * Gets the map that associates prefixes to namespaces.
 *
 * @param editor The editor.
 * @param reverse If true, the reversed map (namespaces to prefixes) is returned.
 * @return Prefix to namespace map.
 *
 * @public @memberof CowlEditor
 */
COWL_PUBLIC
CowlTable* cowl_editor_get_prefix_ns_map(CowlEditor *editor, bool reverse);

/**
 * Returns the namespace associated with the specified prefix.
 *
 * @param editor The editor.
 * @param prefix The prefix.
 * @return Namespace associated with the prefix.
 *
 * @public @memberof CowlEditor
 */
COWL_PUBLIC
CowlString* cowl_editor_get_ns(CowlEditor *editor, CowlString *prefix);

/**
 * Returns the prefix associated with the specified namespace.
 *
 * @param editor The editor.
 * @param ns The namespace.
 * @return Prefix associated with the namespace.
 *
 * @public @memberof CowlEditor
 */
COWL_PUBLIC
CowlString* cowl_editor_get_prefix(CowlEditor *editor, CowlString *ns);

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
cowl_ret cowl_editor_register_prefix(CowlEditor *editor, CowlString *prefix, CowlString *ns);

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
 * Gets the map that associates ontologies to import IRIs.
 *
 * @param editor The editor.
 * @param reverse If true, the reversed map (IRIs to ontologies) is returned.
 * @return Ontologies to import IRIs map.
 *
 * @public @memberof CowlEditor
 */
COWL_PUBLIC
CowlTable* cowl_editor_get_onto_import_iri_map(CowlEditor *editor, bool reverse);

/**
 * Gets the import IRI for the specified ontology.
 *
 * @param editor The editor.
 * @param ontology The ontology.
 * @return Import IRI.
 *
 * @public @memberof CowlEditor
 */
COWL_PUBLIC
CowlIRI* cowl_editor_get_import_iri(CowlEditor *editor, CowlOntology *ontology);

/**
 * Gets the ontology associated with the specified import IRI.
 *
 * @param editor The editor.
 * @param iri The import IRI.
 * @return Ontology associated with the import IRI.
 *
 * @public @memberof CowlEditor
 */
COWL_PUBLIC
CowlOntology* cowl_editor_get_onto_for_import_iri(CowlEditor *editor, CowlIRI *iri);

/**
 * Gets the map that associates local names to anonymous individuals.
 *
 * @param editor The editor.
 * @param reverse If true, the reversed map (anonymous individuals to local names) is returned.
 * @return Local name to anonymous individual map.
 *
 * @public @memberof CowlEditor
 */
COWL_PUBLIC
CowlTable* cowl_editor_get_name_anon_ind_map(CowlEditor *editor, bool reverse);

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
 * Returns the identifier associated with the specified anonymous individual.
 *
 * @param editor The editor.
 * @param ind The anonymous individual.
 * @return Identifier, or NULL on error.
 *
 * @public @memberof CowlEditor
 */
COWL_PUBLIC
CowlString* cowl_editor_get_name_for_anon_ind(CowlEditor *editor, CowlAnonInd *ind);

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

/**
 * Handles a syntax error.
 *
 * @param editor The editor.
 * @param line Line where the error occurred.
 * @param description Error description.
 *
 * @public @memberof CowlEditor
 */
COWL_PUBLIC
void cowl_editor_handle_syntax_error(CowlEditor *editor, ulib_uint line, UString description);

COWL_END_DECLS

#endif // COWL_EDITOR_H
