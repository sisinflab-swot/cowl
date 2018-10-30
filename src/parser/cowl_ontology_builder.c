/// @author Ivano Bilenchi

#include "cowl_ontology_builder.h"
#include "cowl_iri_private.h"
#include "cowl_ontology_private.h"
#include "cowl_string_private.h"

KHASH_MAP_UTILS_IMPL(CowlPrefixNsMap, CowlString*, CowlString*,
                     cowl_string_hash, cowl_string_equals);

CowlOntoBuilder* cowl_onto_builder_alloc(void) {
    CowlOntoBuilder init = {
        .prefix_ns_map = kh_init(CowlPrefixNsMap),
        .ontology = cowl_ontology_get()
    };
    CowlOntoBuilder *builder = malloc(sizeof(*builder));
    memcpy(builder, &init, sizeof(*builder));
    return builder;
}

void cowl_onto_builder_free(CowlOntoBuilder *builder) {
    if (!builder) return;

    kh_foreach(builder->prefix_ns_map, CowlString *prefix, CowlString *ns, {
        cowl_string_release(prefix);
        cowl_string_release(ns);
    });
    kh_destroy(CowlPrefixNsMap, builder->prefix_ns_map);

    cowl_ontology_release(builder->ontology);
    free((void *)builder);
}

CowlOntology* cowl_onto_builder_build(CowlOntoBuilder *builder) {
    return cowl_ontology_retain(builder->ontology);
}

void cowl_onto_builder_set_id(CowlOntoBuilder *builder, CowlOntologyId *id) {
    cowl_ontology_set_id(builder->ontology, id);
}

void cowl_onto_builder_add_axiom(CowlOntoBuilder *builder, CowlAxiom *axiom) {
    cowl_ontology_add_axiom(builder->ontology, axiom);
}

void cowl_onto_builder_register_ns(CowlOntoBuilder *builder, CowlString *prefix, CowlString *ns) {
    if (!kh_set_val_if_missing(CowlPrefixNsMap, builder->prefix_ns_map, prefix, ns, NULL)) {
        cowl_string_retain(prefix);
        cowl_string_retain(ns);
    }
}

CowlIRI* cowl_onto_builder_get_full_iri(CowlOntoBuilder *builder,
                                        char const *cstring, uint32_t length) {
    CowlString *parts[2] = { NULL };
    cowl_string_split_two(cstring, length, ':', parts);

    CowlString *ns = kh_get_val(CowlPrefixNsMap, builder->prefix_ns_map, parts[0], NULL);
    CowlIRI *iri = ns ? cowl_iri_get(ns, parts[1]) : NULL;

    cowl_string_release(parts[0]);
    cowl_string_release(parts[1]);

    return iri;
}
