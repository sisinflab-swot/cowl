/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ONTOLOGY_VEC_H
#define COWL_ONTOLOGY_VEC_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlOntology);
typedef CowlOntology* CowlOntologyPtr;

UVEC_DECL_EQUATABLE(CowlOntologyPtr)
cowl_vector_decl(CowlOntologyPtr, CowlOntologyVec);

void cowl_ontology_vec_free(UVec(CowlOntologyPtr) *vec);

COWL_END_DECLS

#endif // COWL_ONTOLOGY_VEC_H
