/// @author Ivano Bilenchi

#include "cowl_entity.h"
#include "cowl_class_private.h"
#include "cowl_named_individual_private.h"
#include "cowl_obj_prop_private.h"

CowlEntity cowl_entity_retain(CowlEntity entity) {

#define GEN_CASE_RETAIN(CET, PREFIX, FIELD) \
    case CET: PREFIX##_retain(entity.FIELD); break

    switch (entity.type) {

        GEN_CASE_RETAIN(CET_CLASS, cowl_class, owl_class);
        GEN_CASE_RETAIN(CET_OBJ_PROP, cowl_obj_prop, obj_prop);
        GEN_CASE_RETAIN(CET_NAMED_INDIVIDUAL, cowl_named_individual, named_ind);

        default:
            break;
    }

    return entity;
}

void cowl_entity_release(CowlEntity entity) {

#define GEN_CASE_RELEASE(CET, PREFIX, FIELD) \
    case CET: PREFIX##_release(entity.FIELD); break

    switch (entity.type) {

        GEN_CASE_RELEASE(CET_CLASS, cowl_class, owl_class);
        GEN_CASE_RELEASE(CET_OBJ_PROP, cowl_obj_prop, obj_prop);
        GEN_CASE_RELEASE(CET_NAMED_INDIVIDUAL, cowl_named_individual, named_ind);

        default:
            break;
    }
}

CowlIRI* cowl_entity_get_iri(CowlEntity entity) {

#define GEN_CASE_IRI(CET, FIELD) \
    case CET: return entity.FIELD->iri

    switch (entity.type) {

        GEN_CASE_IRI(CET_CLASS, owl_class);
        GEN_CASE_IRI(CET_OBJ_PROP, obj_prop);
        GEN_CASE_IRI(CET_NAMED_INDIVIDUAL, named_ind);

        default:
            return NULL;
    }
}

bool cowl_entity_equals(CowlEntity lhs, CowlEntity rhs) {
    if (lhs.type != rhs.type) return false;

#define GEN_CASE_EQUALS(CET, PREFIX, FIELD) \
    case CET: return PREFIX##_equals(lhs.FIELD, rhs.FIELD)

    switch (lhs.type) {

        GEN_CASE_EQUALS(CET_CLASS, cowl_class, owl_class);
        GEN_CASE_EQUALS(CET_OBJ_PROP, cowl_obj_prop, obj_prop);
        GEN_CASE_EQUALS(CET_NAMED_INDIVIDUAL, cowl_named_individual, named_ind);

        default:
            return false;
    }
}

uint32_t cowl_entity_hash(CowlEntity entity) {

#define GEN_CASE_HASH(CET, PREFIX, FIELD) \
    case CET: return PREFIX##_hash(entity.FIELD)

    switch (entity.type) {

        GEN_CASE_HASH(CET_CLASS, cowl_class, owl_class);
        GEN_CASE_HASH(CET_OBJ_PROP, cowl_obj_prop, obj_prop);
        GEN_CASE_HASH(CET_NAMED_INDIVIDUAL, cowl_named_individual, named_ind);

        default:
            return 0;
    }
}
