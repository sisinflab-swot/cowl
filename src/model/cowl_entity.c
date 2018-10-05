/// @author Ivano Bilenchi

#include "cowl_entity.h"
#include "cowl_class_private.h"
#include "cowl_named_individual_private.h"
#include "cowl_obj_prop_private.h"

CowlIRI const* cowl_entity_get_iri(CowlEntity entity) {
    switch (entity.type) {

        case CET_CLASS:
            return entity.owl_class->iri;

        case CET_OBJ_PROP:
            return entity.obj_prop->iri;

        case CET_NAMED_INDIVIDUAL:
            return entity.named_ind->iri;

        default:
            return NULL;
    }
}

bool cowl_entity_equals(CowlEntity lhs, CowlEntity rhs) {
    if (lhs.type != rhs.type) return false;

    switch (lhs.type) {

        case CET_CLASS:
            return cowl_class_equals(lhs.owl_class, rhs.owl_class);

        case CET_OBJ_PROP:
            return cowl_obj_prop_equals(lhs.obj_prop, rhs.obj_prop);

        case CET_NAMED_INDIVIDUAL:
            return cowl_named_individual_equals(lhs.named_ind, rhs.named_ind);

        default:
            return false;
    }
}

uint32_t cowl_entity_hash(CowlEntity entity) {
    switch (entity.type) {

        case CET_CLASS:
            return cowl_class_hash(entity.owl_class);

        case CET_OBJ_PROP:
            return cowl_obj_prop_hash(entity.obj_prop);

        case CET_NAMED_INDIVIDUAL:
            return cowl_named_individual_hash(entity.named_ind);

        default:
            return 0;
    }
}
