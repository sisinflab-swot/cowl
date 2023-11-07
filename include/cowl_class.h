/**
 * Declares CowlClass and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_CLASS_H
#define COWL_CLASS_H

#include "cowl_entity.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlClass);
/// @endcond

/**
 * Represents a [Class] in the OWL 2 specification.
 *
 * [Class]: https://www.w3.org/TR/owl2-syntax/#Classes
 *
 * @struct CowlClass
 * @extends CowlClsExp
 * @extends CowlEntity
 */

/**
 * Returns a class.
 *
 * @param iri IRI of the class.
 * @return Class, or NULL on error.
 *
 * @public @memberof CowlClass
 */
COWL_RETAINED
COWL_INLINE
CowlClass *cowl_class(CowlIRI *iri) {
    return (CowlClass *)cowl_entity_get_impl(COWL_OT_CE_CLASS, iri);
}

/**
 * Returns a class given the string representation of its IRI.
 *
 * @param string String representation of the IRI.
 * @return Class, or NULL on error.
 *
 * @public @memberof CowlClass
 */
COWL_RETAINED
COWL_INLINE
CowlClass *cowl_class_from_string(UString string) {
    return (CowlClass *)cowl_entity_from_string_impl(COWL_OT_CE_CLASS, string);
}

/**
 * Returns a class given the static string representation of its IRI.
 *
 * @param CSTR [char const[]] Static string.
 * @return [CowlClass *] Class, or NULL on error.
 *
 * @public @related CowlClass
 */
COWL_RETAINED
#define cowl_class_from_static(CSTR) cowl_class_from_string(ustring_literal(CSTR))

/**
 * Gets the IRI of the specified class.
 *
 * @param cls The class.
 * @return IRI of the class.
 *
 * @public @memberof CowlClass
 */
COWL_PURE
COWL_INLINE
CowlIRI *cowl_class_get_iri(CowlClass *cls) {
    return cowl_entity_get_iri((CowlEntity *)cls);
}

COWL_END_DECLS

#endif // COWL_CLASS_H
