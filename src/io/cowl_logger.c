/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_logger.h"
#include "cowl_private.h"

#include <stdio.h>

typedef enum CowlLoggerType {
    COWL_LT_NULL,
    COWL_LT_CONSOLE,
    COWL_LT_FILE
} CowlLoggerType;

typedef cowl_struct(CowlLoggerCtx) {
    cowl_ret_t ret;
    CowlLogger *logger;
} CowlLoggerCtx;

#define cowl_logger_ctx_init(logger) ((CowlLoggerCtx){ .ret = COWL_OK, .logger = logger })

cowl_struct(CowlLogger) {
    CowlObject super;
    CowlLoggerType const type;
    char const *path;
    FILE *file;
};

static CowlLogger* console_logger = NULL;
static CowlLogger* null_logger = NULL;

static cowl_ret_t cowl_logger_open(CowlLogger *logger) {
    cowl_ret_t ret = COWL_OK;

    if (logger->type == COWL_LT_FILE && !logger->file) {
        FILE *file = fopen(logger->path, "a");
        if (!file) {
            ret = COWL_ERR_IO;
            goto end;
        }
        ((cowl_struct(CowlLogger) *)logger)->file = file;
    }

end:
    return ret;
}

static cowl_ret_t cowl_logger_close(CowlLogger *logger) {
    cowl_ret_t ret = COWL_OK;

    if (logger->type == COWL_LT_FILE && logger->file) {
        if (fclose(logger->file) < 0) {
            ret = COWL_ERR_IO;
            goto end;
        }
        ((cowl_struct(CowlLogger)*)logger)->file = NULL;
    }

end:
    return ret;
}

static CowlLogger* cowl_logger_alloc(CowlLoggerType type, void *context) {
    CowlLogger init = {
        .super = COWL_OBJECT_INIT,
        .type = type,
        .path = type == COWL_LT_FILE ? context : NULL,
        .file = type == COWL_LT_CONSOLE ? stdout : NULL
    };
    cowl_struct(CowlLogger) *logger = malloc(sizeof(*logger));
    memcpy(logger, &init, sizeof(*logger));
    return logger;
}

static cowl_ret_t cowl_logger_free(CowlLogger *logger) {
    cowl_ret_t ret = COWL_OK;
    if (!logger) goto end;

    switch (logger->type) {
        case COWL_LT_NULL:
            null_logger = NULL;
            break;

        case COWL_LT_CONSOLE:
            console_logger = NULL;
            break;

        case COWL_LT_FILE:
            if ((ret = cowl_logger_close(logger))) goto end;
            free((void *)logger->path);
            break;

        default:
            break;
    }

    free((void *)logger);

end:
    return ret;
}

static bool imports_logger(void *ctx, CowlOntology *import) {
    CowlLoggerCtx *lctx = ctx;
    cowl_ret_t ret = COWL_OK;

    CowlIRI *iri = cowl_ontology_id_get_onto_iri(cowl_ontology_get_id(import));

    if ((ret = cowl_logger_logs(lctx->logger, "\n"))) goto end;
    if ((ret = cowl_logger_logs(lctx->logger, "Imports"))) goto end;
    if ((ret = cowl_logger_logs(lctx->logger, "("))) goto end;

    if (iri) {
        if ((ret = cowl_logger_consume(lctx->logger, cowl_iri_to_string(iri)))) goto end;
    } else {
        if ((ret = cowl_logger_logf(lctx->logger, "anon(%p)", (void *)import))) goto end;
    }

    if ((ret = cowl_logger_logs(lctx->logger, ")"))) goto end;

end:
    lctx->ret = ret;
    return ret == COWL_OK;
}

static bool entity_logger(void *ctx, CowlEntity entity) {
    CowlLoggerCtx *lctx = ctx;
    cowl_ret_t ret = COWL_OK;

    if ((ret = cowl_logger_consume(lctx->logger, cowl_entity_to_string(entity)))) goto end;
    if ((ret = cowl_logger_logs(lctx->logger, "\n"))) goto end;

end:
    lctx->ret = ret;
    return ret == COWL_OK;
}

static bool axiom_logger(void *ctx, CowlAxiom *axiom) {
    CowlLoggerCtx *lctx = ctx;
    cowl_ret_t ret = COWL_OK;

    if ((ret = cowl_logger_consume(lctx->logger, cowl_axiom_to_string(axiom)))) goto end;
    if ((ret = cowl_logger_logs(lctx->logger, "\n"))) goto end;

end:
    lctx->ret = ret;
    return ret == COWL_OK;
}

static cowl_ret_t cowl_logger_log_ontology_header(CowlLogger *logger, CowlOntology *onto) {
    cowl_ret_t ret = COWL_OK;

    if ((ret = cowl_logger_logs(logger, "Ontology"))) goto end;
    if ((ret = cowl_logger_logs(logger, "("))) goto end;
    if ((ret = cowl_logger_consume(logger, cowl_ontology_id_to_string(onto->id)))) goto end;

    CowlLoggerCtx ctx = cowl_logger_ctx_init(logger);
    CowlOntologyIterator iter = cowl_iterator_init(&ctx, imports_logger);
    cowl_ontology_iterate_imports(onto, &iter);
    if ((ret = ctx.ret)) goto end;

    CowlAnnotationVec *annotations = cowl_ontology_get_annot(onto);
    vector_foreach(CowlAnnotationPtr, annotations, annot, {
        if ((ret = cowl_logger_logs(logger, "\n"))) goto end;
        if ((ret = cowl_logger_consume(logger, cowl_annotation_to_string(annot)))) goto end;
    });

    if ((ret = cowl_logger_logs(logger, ")"))) goto end;

end:
    return ret;
}

CowlLogger* cowl_logger_console_get(void) {
    if (console_logger) {
        cowl_logger_retain(console_logger);
    } else {
        console_logger = cowl_logger_alloc(COWL_LT_CONSOLE, NULL);
    }
    return console_logger;
}

CowlLogger* cowl_logger_file_get(char const *path) {
    return cowl_logger_alloc(COWL_LT_FILE, strdup(path));
}

CowlLogger* cowl_logger_null_get(void) {
    if (null_logger) {
        cowl_logger_retain(null_logger);
    } else {
        null_logger = cowl_logger_alloc(COWL_LT_NULL, NULL);
    }
    return null_logger;
}

CowlLogger* cowl_logger_retain(CowlLogger *logger) {
    return cowl_object_retain(logger);
}

cowl_ret_t cowl_logger_release(CowlLogger *logger) {
    cowl_ret_t ret = COWL_OK;

    if (logger && cowl_object_ref_get(logger) == 1) {
        if ((ret = cowl_logger_free(logger))) goto end;
        cowl_object_release(logger);
    }

end:
    return ret;
}

cowl_ret_t cowl_logger_clear(CowlLogger *logger) {
    cowl_ret_t ret = COWL_OK;

    if (logger->type == COWL_LT_FILE) {
        if ((ret = cowl_logger_close(logger))) {
            goto end;
        }

        if (remove(logger->path)) {
            ret = COWL_ERR_IO;
            goto end;
        }
    }

end:
    return ret;
}

cowl_ret_t cowl_logger_logs(CowlLogger *logger, char const *cstring) {
    cowl_ret_t ret = cowl_logger_open(logger);
    if (ret) goto end;

    if (logger->type == COWL_LT_CONSOLE || logger->type == COWL_LT_FILE) {
        if (fputs(cstring, logger->file) < 0) {
            ret = COWL_ERR_IO;
            goto end;
        }
    }

end:
    return ret;
}

cowl_ret_t cowl_logger_logf(CowlLogger *logger, char const *format, ...) {
    va_list args;
    va_start(args, format);

    cowl_ret_t ret = cowl_logger_open(logger);
    if (ret) goto end;

    if (logger->type == COWL_LT_CONSOLE || logger->type == COWL_LT_FILE) {
        if (vfprintf(logger->file, format, args) < 0) {
            ret = COWL_ERR_IO;
            goto end;
        }
    }

end:
    va_end(args);
    return ret;
}

cowl_ret_t cowl_logger_log(CowlLogger *logger, CowlString *string) {
    return cowl_logger_logs(logger, string->raw_string.cstring);
}

cowl_ret_t cowl_logger_consume(CowlLogger *logger, CowlString *string) {
    cowl_ret_t ret = cowl_logger_log(logger, string);
    cowl_string_release(string);
    return ret;
}

cowl_ret_t cowl_logger_log_entities_in_ontology(CowlLogger *logger, CowlOntology *onto) {
    CowlLoggerCtx ctx = cowl_logger_ctx_init(logger);
    CowlEntityIterator iter = cowl_iterator_init(&ctx, entity_logger);
    cowl_ontology_iterate_signature(onto, &iter);
    return ctx.ret;
}

cowl_ret_t cowl_logger_log_axioms_in_ontology(CowlLogger *logger, CowlOntology *onto) {
    CowlLoggerCtx ctx = cowl_logger_ctx_init(logger);
    CowlAxiomIterator iter = cowl_iterator_init(&ctx, axiom_logger);
    cowl_ontology_iterate_axioms(onto, &iter);
    return ctx.ret;
}

cowl_ret_t cowl_logger_log_ontology(CowlLogger *logger, CowlOntology *onto) {
    cowl_ret_t ret = COWL_OK;

    if ((ret = cowl_logger_log_ontology_header(logger, onto))) goto end;
    if ((ret = cowl_logger_logs(logger, "\n"))) goto end;
    if ((ret = cowl_logger_log_entities_in_ontology(logger, onto))) goto end;
    if ((ret = cowl_logger_log_axioms_in_ontology(logger, onto))) goto end;

end:
    return ret;
}

cowl_ret_t cowl_logger_log_errors(CowlLogger *logger, Vector(CowlError) *errors) {
    cowl_ret_t ret = COWL_OK;

    vector_foreach(CowlError, errors, error, {
        if ((ret = cowl_logger_consume(logger, cowl_error_to_string(error)))) goto end;
        if ((ret = cowl_logger_logs(logger, "\n"))) goto end;
    });

end:
    return ret;
}

char const* cowl_logger_get_path(CowlLogger *logger) {
    return logger->type == COWL_LT_FILE ? logger->path : NULL;
}
