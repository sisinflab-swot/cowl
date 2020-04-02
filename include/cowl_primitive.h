/**
 * Defines CowlPrimitive and declares its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_PRIMITIVE_H
#define COWL_PRIMITIVE_H

#include "cowl_entity.h"
#include "cowl_primitive_type.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlAnnotProp);
cowl_struct_decl(CowlAnonInd);
cowl_struct_decl(CowlClass);
cowl_struct_decl(CowlDataProp);
cowl_struct_decl(CowlDatatype);
cowl_struct_decl(CowlObjProp);
cowl_struct_decl(CowlString);
cowl_struct_decl(CowlNamedInd);
/// @endcond

/**
 * Represents primitives, e.g. entities and anonymous individuals.
 */
typedef cowl_struct(CowlPrimitive) {

    /// Type of the primitive.
    CowlPrimitiveType type;

    /// Concrete primitive.
    union {

        /// Class.
        CowlClass *owl_class;

        /// Object property.
        CowlObjProp *obj_prop;

        /// Data property.
        CowlDataProp *data_prop;

        /// Named individual.
        CowlNamedInd *named_ind;

        /// Datatype.
        CowlDatatype *datatype;

        /// Annotation property.
        CowlAnnotProp *annot_prop;

        /// Anonymous individual.
        CowlAnonInd *anon_ind;

    };

} CowlPrimitive;

/**
 * Checks whether the primitive is an entity.
 *
 * @param P [CowlPrimitive] The primitive.
 * @return [bool] True if the primitive is an entity, false otherwise.
 */
#define cowl_primitive_is_entity(P) ((P).type <= COWL_PT_MAX_ENTITY)

/**
 * Initializes a primitive by wrapping the specified class.
 *
 * @param CLS [CowlClass *] Class to wrap.
 * @return [CowlPrimitive] Primitive.
 *
 * @public @related CowlPrimitive
 */
#define cowl_primitive_wrap_class(CLS) \
    ((CowlPrimitive const){ .type = COWL_PT_CLASS, .owl_class = (CLS) })

/**
 * Initializes a primitive by wrapping the specified object property.
 *
 * @param PROP [CowlObjProp *] Object property to wrap.
 * @return [CowlPrimitive] Primitive.
 *
 * @public @related CowlPrimitive
 */
#define cowl_primitive_wrap_obj_prop(PROP) \
    ((CowlPrimitive const){ .type = COWL_PT_OBJ_PROP, .obj_prop = (PROP) })

/**
 * Initializes a primitive by wrapping the specified data property.
 *
 * @param PROP [CowlDataProp *] Data property to wrap.
 * @return [CowlPrimitive] Primitive.
 *
 * @public @related CowlPrimitive
 */
#define cowl_primitive_wrap_data_prop(PROP) \
    ((CowlPrimitive const){ .type = COWL_PT_DATA_PROP, .data_prop = (PROP) })

/**
 * Initializes a primitive by wrapping the specified named individual.
 *
 * @param IND [CowlNamedInd *] Named individual to wrap.
 * @return [CowlPrimitive] Primitive.
 *
 * @public @related CowlPrimitive
 */
#define cowl_primitive_wrap_named_ind(IND) \
    ((CowlPrimitive const){ .type = COWL_PT_NAMED_IND, .named_ind = (IND) })

/**
 * Initializes a primitive by wrapping the specified datatype.
 *
 * @param DT [CowlDatatype *] Datatype to wrap.
 * @return [CowlPrimitive] Primitive.
 *
 * @public @related CowlPrimitive
 */
#define cowl_primitive_wrap_datatype(DT) \
    ((CowlPrimitive const){ .type = COWL_PT_DATATYPE, .datatype = (DT) })

/**
 * Initializes a primitive by wrapping the specified annotation property.
 *
 * @param PROP [CowlAnnotProp *] Annotation property to wrap.
 * @return [CowlPrimitive] Primitive.
 *
 * @public @related CowlPrimitive
 */
#define cowl_primitive_wrap_annot_prop(PROP) \
    ((CowlPrimitive const){ .type = COWL_PT_ANNOT_PROP, .annot_prop = (PROP) })

/**
 * Initializes a primitive by wrapping the specified anonymous individual.
 *
 * @param IND [CowlAnonInd *] Anonymous individual to wrap.
 * @return [CowlPrimitive] Primitive.
 *
 * @public @related CowlPrimitive
 */
#define cowl_primitive_wrap_anon_ind(IND) \
    ((CowlPrimitive const){ .type = COWL_PT_ANON_IND, .anon_ind = (IND) })

/**
 * Initializes a primitive by wrapping and retaining the specified class.
 *
 * @param CLS [CowlClass *] Class to wrap.
 * @return [CowlPrimitive] Retained primitive.
 *
 * @public @related CowlPrimitive
 */
#define cowl_primitive_init_class(CLS) \
    cowl_primitive_wrap_class(cowl_class_retain(CLS))

/**
 * Initializes a primitive by wrapping and retaining the specified object property.
 *
 * @param PROP [CowlObjProp *] Object property to wrap.
 * @return [CowlPrimitive] Retained primitive.
 *
 * @public @related CowlPrimitive
 */
#define cowl_primitive_init_obj_prop(PROP) \
    cowl_primitive_wrap_obj_prop(cowl_obj_prop_retain(PROP))

/**
 * Initializes a primitive by wrapping and retaining the specified data property.
 *
 * @param PROP [CowlDataProp *] Data property to wrap.
 * @return [CowlPrimitive] Retained primitive.
 *
 * @public @related CowlPrimitive
 */
#define cowl_primitive_init_data_prop(PROP) \
    cowl_primitive_wrap_data_prop(cowl_data_prop_retain(PROP))

/**
 * Initializes a primitive by wrapping and retaining the specified named individual.
 *
 * @param IND [CowlNamedInd *] Named individual to wrap.
 * @return [CowlPrimitive] Retained primitive.
 *
 * @public @related CowlPrimitive
 */
#define cowl_primitive_init_named_ind(IND) \
    cowl_primitive_wrap_named_ind(cowl_named_ind_retain(IND))

/**
 * Initializes a primitive by wrapping and retaining the specified datatype.
 *
 * @param DT [CowlDatatype *] Datatype to wrap.
 * @return [CowlPrimitive] Retained primitive.
 *
 * @public @related CowlPrimitive
 */
#define cowl_primitive_init_datatype(DT) \
    cowl_primitive_wrap_datatype(cowl_datatype_retain(DT))

/**
 * Initializes a primitive by wrapping the specified annotation property.
 *
 * @param PROP [CowlAnnotProp *] Annotation property to wrap.
 * @return [CowlPrimitive] Retained primitive.
 *
 * @public @related CowlPrimitive
 */
#define cowl_primitive_init_annot_prop(PROP) \
    cowl_primitive_wrap_annot_prop(cowl_annot_prop_retain(PROP))

/**
 * Initializes a primitive by wrapping the specified anonymous individual.
 *
 * @param IND [CowlAnonInd *] Anonymous individual to wrap.
 * @return [CowlPrimitive] Retained primitive.
 *
 * @public @related CowlPrimitive
 */
#define cowl_primitive_init_anon_ind(IND) \
    cowl_primitive_wrap_anon_ind(cowl_anon_ind_retain(IND))

/**
 * Retains the underlying primitive.
 *
 * @param primitive The primitive.
 * @return Retained primitive.
 *
 * @public @memberof CowlPrimitive
 */
COWL_PUBLIC
CowlPrimitive cowl_primitive_retain(CowlPrimitive primitive);

/**
 * Releases the underlying primitive.
 *
 * @param primitive The primitive.
 *
 * @public @memberof CowlPrimitive
 */
COWL_PUBLIC
void cowl_primitive_release(CowlPrimitive primitive);

/**
 * Gets the underlying entity.
 *
 * @param primitive The primitive.
 * @param[out] entity The underlying entity, only assigned if the function returns True.
 * @return True if the primitive is an entity, False otherwise.
 */
COWL_PUBLIC
bool cowl_primitive_get_entity(CowlPrimitive primitive, CowlEntity *entity);

/**
 * Returns a primitive wrapping the specified entity.
 *
 * @param entity The entity.
 * @return Primitive.
 */
COWL_PUBLIC
CowlPrimitive cowl_primitive_from_entity(CowlEntity entity);

/**
 * Gets the IRI of the underlying primitive.
 *
 * @param primitive The primitive.
 * @return The IRI, or NULL if the primitive does not have one.
 *
 * @public @memberof CowlPrimitive
 */
COWL_PUBLIC
CowlIRI* cowl_primitive_get_iri(CowlPrimitive primitive);

/**
 * Returns the string representation of the specified primitive.
 *
 * @param primitive The primitive.
 * @return String representation.
 *
 * @note The returned string is retained, so you are responsible for releasing it.
 *
 * @public @memberof CowlPrimitive
 */
COWL_PUBLIC
CowlString* cowl_primitive_to_string(CowlPrimitive primitive);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlPrimitive
 */
COWL_PUBLIC
bool cowl_primitive_equals(CowlPrimitive lhs, CowlPrimitive rhs);

/**
 * Hash function.
 *
 * @param primitive The primitive.
 * @return The hash value.
 *
 * @public @memberof CowlPrimitive
 */
COWL_PUBLIC
cowl_uint_t cowl_primitive_hash(CowlPrimitive primitive);

COWL_END_DECLS

#endif // COWL_PRIMITIVE_H
