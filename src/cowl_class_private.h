/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_CLASS_PRIVATE_H
#define COWL_CLASS_PRIVATE_H

#include "cowl_class.h"
#include "cowl_cls_exp_private.h"

COWL_BEGIN_DECLS

struct CowlClass {
    CowlClsExp super;
    CowlIRI *iri;
};

cowl_ret cowl_class_api_init(void);
void cowl_class_api_deinit(void);

COWL_END_DECLS

#endif // COWL_CLASS_PRIVATE_H
