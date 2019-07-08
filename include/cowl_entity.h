/**
 * Defines CowlEntity and declares its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_ENTITY_H
#define COWL_ENTITY_H

#include "cowl_entity_type.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlAnnotProp);
cowl_struct_decl(CowlClass);
cowl_struct_decl(CowlDataProp);
cowl_struct_decl(CowlDatatype);
cowl_struct_decl(CowlObjProp);
cowl_struct_decl(CowlNamedInd);
/// @endcond

/**
 * Represents an [Entity] in the OWL 2 specification.
 *
 * [Entity]: https://www.w3.org/TR/owl2-syntax/#Entities.2C_Literals.2C_and_Anonymous_Individuals
 */
typedef cowl_struct(CowlEntity) {

    /// Type of the entity.
    CowlEntityType type;

    /// Concrete entity.
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

    };

} CowlEntity;

/**
 * Initializes an entity by wrapping the specified class.
 *
 * @param CLS [CowlClass *] Class to wrap.
 * @return [CowlEntity] Entity.
 *
 * @public @related CowlEntity
 */
#define cowl_entity_wrap_class(CLS) \
    ((CowlEntity const){ .type = COWL_ET_CLASS, .owl_class = (CLS) })

/**
 * Initializes an entity by wrapping the specified object property.
 *
 * @param PROP [CowlObjProp *] Object property to wrap.
 * @return [CowlEntity] Entity.
 *
 * @public @related CowlEntity
 */
#define cowl_entity_wrap_obj_prop(PROP) \
    ((CowlEntity const){ .type = COWL_ET_OBJ_PROP, .obj_prop = (PROP) })

/**
 * Initializes an entity by wrapping the specified data property.
 *
 * @param PROP [CowlDataProp *] Data property to wrap.
 * @return [CowlEntity] Entity.
 *
 * @public @related CowlEntity
 */
#define cowl_entity_wrap_data_prop(PROP) \
    ((CowlEntity const){ .type = COWL_ET_DATA_PROP, .data_prop = (PROP) })

/**
 * Initializes an entity by wrapping the specified named individual.
 *
 * @param IND [CowlNamedInd *] Named individual to wrap.
 * @return [CowlEntity] Entity.
 *
 * @public @related CowlEntity
 */
#define cowl_entity_wrap_named_ind(IND) \
    ((CowlEntity const){ .type = COWL_ET_NAMED_IND, .named_ind = (IND) })

/**
 * Initializes an entity by wrapping the specified datatype.
 *
 * @param DT [CowlDatatype *] Datatype to wrap.
 * @return [CowlEntity] Entity.
 *
 * @public @related CowlEntity
 */
#define cowl_entity_wrap_datatype(DT) \
    ((CowlEntity const){ .type = COWL_ET_DATATYPE, .datatype = (DT) })

/**
 * Initializes an entity by wrapping the specified annotation property.
 *
 * @param PROP [CowlAnnotProp *] Annotation property to wrap.
 * @return [CowlEntity] Entity.
 *
 * @public @related CowlEntity
 */
#define cowl_entity_wrap_annot_prop(PROP) \
    ((CowlEntity const){ .type = COWL_ET_ANNOT_PROP, .annot_prop = (PROP) })

/**
 * Initializes an entity by wrapping and retaining the specified class.
 *
 * @param CLS [CowlClass *] Class to wrap.
 * @return [CowlEntity] Retained entity.
 *
 * @public @related CowlEntity
 */
#define cowl_entity_init_class(CLS) \
    cowl_entity_wrap_class(cowl_class_retain(CLS))

/**
 * Initializes an entity by wrapping and retaining the specified object property.
 *
 * @param PROP [CowlObjProp *] Object property to wrap.
 * @return [CowlEntity] Retained entity.
 *
 * @public @related CowlEntity
 */
#define cowl_entity_init_obj_prop(PROP) \
    cowl_entity_wrap_obj_prop(cowl_obj_prop_retain(PROP))

/**
 * Initializes an entity by wrapping and retaining the specified data property.
 *
 * @param PROP [CowlDataProp *] Data property to wrap.
 * @return [CowlEntity] Retained entity.
 *
 * @public @related CowlEntity
 */
#define cowl_entity_init_data_prop(PROP) \
    cowl_entity_wrap_data_prop(cowl_data_prop_retain(PROP))

/**
 * Initializes an entity by wrapping and retaining the specified named individual.
 *
 * @param IND [CowlNamedInd *] Named individual to wrap.
 * @return [CowlEntity] Retained entity.
 *
 * @public @related CowlEntity
 */
#define cowl_entity_init_named_ind(IND) \
    cowl_entity_wrap_named_ind(cowl_named_ind_retain(IND))

/**
 * Initializes an entity by wrapping and retaining the specified datatype.
 *
 * @param DT [CowlDatatype *] Datatype to wrap.
 * @return [CowlEntity] Retained entity.
 *
 * @public @related CowlEntity
 */
#define cowl_entity_init_datatype(DT) \
    cowl_entity_wrap_datatype(cowl_datatype_retain(DT))

/**
 * Initializes an entity by wrapping the specified annotation property.
 *
 * @param PROP [CowlAnnotProp *] Annotation property to wrap.
 * @return [CowlEntity] Retained entity.
 *
 * @public @related CowlEntity
 */
#define cowl_entity_init_annot_prop(PROP) \
    cowl_entity_wrap_annot_prop(cowl_annot_prop_retain(PROP))

/**
 * Retains the underlying entity.
 *
 * @param entity The entity.
 * @return Retained entity.
 *
 * @public @memberof CowlEntity
 */
COWL_PUBLIC
CowlEntity cowl_entity_retain(CowlEntity entity);

/**
 * Releases the underlying entity.
 *
 * @param entity The entity.
 *
 * @public @memberof CowlEntity
 */
COWL_PUBLIC
void cowl_entity_release(CowlEntity entity);

/**
 * Gets the IRI of the underlying entity.
 *
 * @param entity The entity.
 * @return The IRI.
 *
 * @public @memberof CowlEntity
 */
COWL_PUBLIC
CowlIRI* cowl_entity_get_iri(CowlEntity entity);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlEntity
 */
COWL_PUBLIC
bool cowl_entity_equals(CowlEntity lhs, CowlEntity rhs);

/**
 * Hash function.
 *
 * @param entity The entity.
 * @return The hash value.
 *
 * @public @memberof CowlEntity
 */
COWL_PUBLIC
cowl_uint_t cowl_entity_hash(CowlEntity entity);

COWL_END_DECLS

#endif // COWL_ENTITY_H
