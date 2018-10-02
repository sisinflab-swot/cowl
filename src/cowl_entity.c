/// @author Ivano Bilenchi

#include "cowl_entity_private.h"
#include "cowl_class_private.h"
#include "cowl_hash_utils.h"
#include "cowl_iri.h"
#include "cowl_named_individual_private.h"
#include "cowl_obj_prop_private.h"

#include <assert.h>

CowlEntityType cowl_entity_get_type(CowlEntity const *entity) {
    return entity->type;
}

CowlIRI const* cowl_entity_get_iri(CowlEntity const *entity) {
    switch (entity->type) {

        case CET_CLASS:
            return entity->owl_class->iri;

        case CET_OBJECT_PROPERTY:
            return entity->obj_prop->iri;

        case CET_NAMED_INDIVIDUAL:
            return entity->named_ind->iri;

        default:
            return NULL;
    }
}

CowlClass const* cowl_entity_as_class(CowlEntity const *entity) {
    assert(entity->type == CET_CLASS);
    return entity->owl_class;
}

CowlObjProp const* cowl_entity_as_prop(CowlEntity const *entity) {
    assert(entity->type == CET_OBJECT_PROPERTY);
    return entity->obj_prop;
}

CowlNamedIndividual const* cowl_entity_as_individual(CowlEntity const *entity) {
    assert(entity->type == CET_NAMED_INDIVIDUAL);
    return entity->named_ind;

}

bool cowl_entity_equals(CowlEntity const *lhs, CowlEntity const *rhs) {
    if (lhs->type != rhs->type) return false;

    switch (lhs->type) {
        case CET_CLASS:
            return cowl_class_equals(lhs->owl_class, rhs->owl_class);

        case CET_OBJECT_PROPERTY:
            return cowl_obj_prop_equals(lhs->obj_prop, rhs->obj_prop);

        case CET_NAMED_INDIVIDUAL:
            return cowl_named_individual_equals(lhs->named_ind, rhs->named_ind);

        default:
            return false;
    }
}

uint32_t cowl_entity_hash(CowlEntity const *entity) {
    switch (entity->type) {
        case CET_CLASS:
            return cowl_class_hash(entity->owl_class);

        case CET_OBJECT_PROPERTY:
            return cowl_obj_prop_hash(entity->obj_prop);

        case CET_NAMED_INDIVIDUAL:
            return cowl_named_individual_hash(entity->named_ind);

        default:
            return 0;
    }
}
