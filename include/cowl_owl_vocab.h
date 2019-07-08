/**
 * Defines CowlOWLVocab.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_OWL_VOCAB_H
#define COWL_OWL_VOCAB_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlClass);
cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlString);
/// @endcond

/// The OWL 2 vocabulary.
typedef cowl_struct(CowlOWLVocab) {

    /// OWL namespace.
    CowlString *ns;

    /// IRIs.
    struct {

        /// owl:Thing
        CowlIRI *thing;

        /// owl:Nothing
        CowlIRI *nothing;

    } iri;

    /// Classes.
    struct {

        /// owl:Thing
        CowlClass *thing;

        /// owl:Nothing
        CowlClass *nothing;

    } cls;

} const CowlOWLVocab;

/**
 * Gets the OWL 2 vocabulary.
 *
 * @return The OWL 2 vocabulary.
 *
 * @public @memberof CowlOWLVocab
 */
COWL_PUBLIC
CowlOWLVocab* cowl_owl_vocab_get(void);

COWL_END_DECLS

#endif // COWL_OWL_VOCAB_H
