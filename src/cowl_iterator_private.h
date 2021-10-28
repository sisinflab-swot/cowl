/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ITERATOR_PRIVATE_H
#define COWL_ITERATOR_PRIVATE_H

#include "cowl_iterator.h"

COWL_BEGIN_DECLS

#define cowl_iterate(iter, elem) ((iter)->for_each((iter)->ctx, (elem)))

COWL_END_DECLS

#endif // COWL_ITERATOR_PRIVATE_H
