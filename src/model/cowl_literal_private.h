/// @author Ivano Bilenchi

#ifndef COWL_LITERAL_PRIVATE_H
#define COWL_LITERAL_PRIVATE_H

#include "cowl_literal.h"
#include "cowl_object.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlDatatype);
cowl_struct_decl(CowlString);

cowl_struct(CowlLiteral) {
    CowlObject super;
    CowlDatatype *dt;
    CowlString *value;
    CowlString *lang;
};

COWL_END_DECLS

#endif // COWL_LITERAL_PRIVATE_H
