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

cowl_struct(CowlLogger) {
    CowlObject super;
    CowlLoggerType const type;
    char const *path;
    FILE *file;
};

static CowlLogger* console_logger = NULL;
static CowlLogger* null_logger = NULL;

static bool cowl_logger_is_open(CowlLogger *logger) {
    return logger->type == COWL_LT_FILE && logger->file;
}

static void cowl_logger_open(CowlLogger *logger) {
    if (cowl_logger_is_open(logger)) return;
    ((cowl_struct(CowlLogger) *)logger)->file = fopen(logger->path, "a");
}

static void cowl_logger_close(CowlLogger *logger) {
    if (!cowl_logger_is_open(logger)) return;

    fclose(logger->file);
    ((cowl_struct(CowlLogger)*)logger)->file = NULL;
}

static CowlLogger* cowl_logger_alloc(CowlLoggerType type, void *context) {
    CowlLogger init = {
        .super = COWL_OBJECT_INIT,
        .type = type,
        .path = type == COWL_LT_FILE ? context : NULL
    };

    cowl_struct(CowlLogger) *logger = malloc(sizeof(*logger));
    memcpy(logger, &init, sizeof(*logger));
    cowl_logger_open(logger);

    return logger;
}

static void cowl_logger_free(CowlLogger *logger) {
    if (!logger) return;

    switch (logger->type) {
        case COWL_LT_NULL:
            null_logger = NULL;
            break;

        case COWL_LT_CONSOLE:
            console_logger = NULL;
            break;

        case COWL_LT_FILE:
            cowl_logger_close(logger);
            free((void *)logger->path);
            break;

        default:
            break;
    }

    free((void *)logger);
}

static bool imports_logger(void *ctx, CowlOntology *import) {
    CowlIRI *iri = cowl_ontology_id_get_onto_iri(cowl_ontology_get_id(import));

    cowl_logger_logf(ctx, "\n");
    cowl_logger_logf(ctx, "Imports");
    cowl_logger_logf(ctx, "(");

    if (iri) {
        cowl_logger_consume(ctx, cowl_iri_to_string(iri));
    } else {
        cowl_logger_logf(ctx, "anon(%p)", (void *)import);
    }

    cowl_logger_logf(ctx, ")");

    return true;
}

static bool entity_logger(void *ctx, CowlEntity entity) {
    cowl_logger_consume(ctx, cowl_entity_to_string(entity));
    cowl_logger_logf(ctx, "\n");
    return true;
}

static bool axiom_logger(void *ctx, CowlAxiom *axiom) {
    cowl_logger_consume(ctx, cowl_axiom_to_string(axiom));
    cowl_logger_logf(ctx, "\n");
    return true;
}

static void cowl_logger_log_ontology_header(CowlLogger *logger, CowlOntology *onto) {
    cowl_logger_logf(logger, "Ontology");
    cowl_logger_logf(logger, "(");
    cowl_logger_consume(logger, cowl_ontology_id_to_string(onto->id));

    CowlOntologyIterator iter = cowl_iterator_init(logger, imports_logger);
    cowl_ontology_iterate_imports(onto, &iter);

    CowlAnnotationVec *annotations = cowl_ontology_get_annot(onto);
    vector_foreach(CowlAnnotationPtr, annotations, annot, {
        cowl_logger_logf(logger, "\n");
        cowl_logger_consume(logger, cowl_annotation_to_string(annot));
    });

    cowl_logger_logf(logger, ")");
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

void cowl_logger_release(CowlLogger *logger) {
    if (logger && !cowl_object_release(logger)) {
        cowl_logger_free(logger);
    }
}

void cowl_logger_clear(CowlLogger *logger) {
    if (logger->type != COWL_LT_FILE) return;
    bool should_reopen = cowl_logger_is_open(logger);
    if (should_reopen) cowl_logger_close(logger);
    remove(logger->path);
    if (should_reopen) cowl_logger_open(logger);
}

void cowl_logger_logf(CowlLogger *logger, char const *format, ...) {
    va_list args;
    va_start(args, format);

    switch(logger->type) {
        case COWL_LT_CONSOLE:
            vprintf(format, args);
            break;

        case COWL_LT_FILE:
            vfprintf(logger->file, format, args);
            break;

        default:
            break;
    }

    va_end(args);
}

void cowl_logger_log(CowlLogger *logger, CowlString *string) {
    cowl_logger_logf(logger, "%s", string->raw_string.cstring);
}

void cowl_logger_consume(CowlLogger *logger, CowlString *string) {
    cowl_logger_log(logger, string);
    cowl_string_release(string);
}

void cowl_logger_log_entities_in_ontology(CowlLogger *logger, CowlOntology *onto) {
    CowlEntityIterator iter = cowl_iterator_init(logger, entity_logger);
    cowl_ontology_iterate_signature(onto, &iter);
}

void cowl_logger_log_axioms_in_ontology(CowlLogger *logger, CowlOntology *onto) {
    CowlAxiomIterator iter = cowl_iterator_init(logger, axiom_logger);
    cowl_ontology_iterate_axioms(onto, &iter);
}

void cowl_logger_log_ontology(CowlLogger *logger, CowlOntology *onto) {
    cowl_logger_log_ontology_header(logger, onto);
    cowl_logger_logf(logger, "\n");
    cowl_logger_log_entities_in_ontology(logger, onto);
    cowl_logger_log_axioms_in_ontology(logger, onto);
}

void cowl_logger_log_errors(CowlLogger *logger, Vector(CowlError) *errors) {
    vector_foreach(CowlError, errors, error, {
        cowl_logger_consume(logger, cowl_error_to_string(error));
        cowl_logger_logf(logger, "\n");
    });
}

char const* cowl_logger_get_path(CowlLogger *logger) {
    return logger->type == COWL_LT_FILE ? logger->path : NULL;
}
