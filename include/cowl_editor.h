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
cowl_struct_decl(CowlEditor);
cowl_struct_decl(CowlAnnotation);
cowl_struct_decl(CowlAxiom);
cowl_struct_decl(CowlOntology);
cowl_struct_decl(CowlSymTable);
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
 * Gets the symbol table of this editor.
 *
 * @param editor The editor.
 * @return Symbol table.
 *
 * @public @memberof CowlEditor
 */
COWL_PUBLIC
CowlSymTable* cowl_editor_get_sym_table(CowlEditor *editor);

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

COWL_END_DECLS

#endif // COWL_EDITOR_H
