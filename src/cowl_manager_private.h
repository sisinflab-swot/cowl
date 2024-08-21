/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_MANAGER_PRIVATE_H
#define COWL_MANAGER_PRIVATE_H

#include "cowl_attrs.h"
#include "cowl_error_handler.h"
#include "cowl_import_loader.h"
#include "cowl_manager.h" // IWYU pragma: export
#include "cowl_object_private.h"
#include "cowl_reader.h"
#include "cowl_ret.h"
#include "cowl_vector.h" // IWYU pragma: keep, needed for UVec(CowlObjectPtr)
#include "cowl_writer.h"
#include "ulib.h"

COWL_BEGIN_DECLS

struct CowlManager {
    CowlObject super;
    CowlReader reader;
    CowlWriter writer;
    CowlErrorHandler handler;
    CowlImportLoader loader;
    UVec(CowlObjectPtr) ontos;
};

void cowl_manager_free(CowlManager *manager);
cowl_ret cowl_manager_add_ontology(CowlManager *manager, CowlOntology *onto);
void cowl_manager_remove_ontology(CowlManager *manager, CowlOntology *onto);

COWL_END_DECLS

#endif // COWL_MANAGER_PRIVATE_H
