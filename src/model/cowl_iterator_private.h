/// @author Ivano Bilenchi

#ifndef COWL_ITERATOR_PRIVATE_H
#define COWL_ITERATOR_PRIVATE_H

#include "cowl_iterator.h"

COWL_BEGIN_DECLS

#define cowl_iterate(iter, elem) ((iter)->for_each((iter)->ctx, elem))

COWL_END_DECLS

#endif // COWL_ITERATOR_PRIVATE_H
