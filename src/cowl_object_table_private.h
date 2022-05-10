/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_OBJECT_TABLE_PRIVATE_H
#define COWL_OBJECT_TABLE_PRIVATE_H

#include "cowl_object_table.h"

COWL_BEGIN_DECLS

UHash(CowlObjectTable) cowl_annot_prop_map_init(void);
UHash(CowlObjectTable) cowl_anon_ind_map_init(void);
UHash(CowlObjectTable) cowl_class_map_init(void);
UHash(CowlObjectTable) cowl_data_prop_map_init(void);
UHash(CowlObjectTable) cowl_datatype_map_init(void);
UHash(CowlObjectTable) cowl_named_ind_map_init(void);
UHash(CowlObjectTable) cowl_obj_prop_map_init(void);
UHash(CowlObjectTable) cowl_string_map_init(void);

COWL_END_DECLS

#endif // COWL_OBJECT_TABLE_PRIVATE_H
