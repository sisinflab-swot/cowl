/// @author Ivano Bilenchi

#ifndef COWL_API_H
#define COWL_API_H

#include "cowl_anon_individual.h"
#include "cowl_axiom.h"
#include "cowl_axiom_type.h"
#include "cowl_class.h"
#include "cowl_cls_assert_axiom.h"
#include "cowl_cls_exp.h"
#include "cowl_cls_exp_set.h"
#include "cowl_cls_exp_type.h"
#include "cowl_compat.h"
#include "cowl_data_prop.h"
#include "cowl_data_prop_exp.h"
#include "cowl_datatype.h"
#include "cowl_decl_axiom.h"
#include "cowl_entity.h"
#include "cowl_entity_type.h"
#include "cowl_error.h"
#include "cowl_nary_cls_axiom.h"
#include "cowl_individual.h"
#include "cowl_inverse_obj_prop.h"
#include "cowl_iri.h"
#include "cowl_iterator.h"
#include "cowl_logger.h"
#include "cowl_named_individual.h"
#include "cowl_nary_bool.h"
#include "cowl_nary_cls_axiom.h"
#include "cowl_obj_card.h"
#include "cowl_obj_prop_char_axiom.h"
#include "cowl_obj_compl.h"
#include "cowl_obj_prop.h"
#include "cowl_obj_prop_assert_axiom.h"
#include "cowl_obj_prop_domain_axiom.h"
#include "cowl_obj_prop_exp.h"
#include "cowl_obj_prop_range_axiom.h"
#include "cowl_obj_quant.h"
#include "cowl_ontology.h"
#include "cowl_ontology_id.h"
#include "cowl_parser.h"
#include "cowl_std.h"
#include "cowl_string.h"
#include "cowl_sub_cls_axiom.h"
#include "cowl_vocabulary.h"

COWL_BEGIN_DECLS

void cowl_api_init(void);
void cowl_api_deinit(void);

COWL_END_DECLS

#endif // COWL_API_H
