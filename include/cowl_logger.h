/** @file
 * Declares the logging API.
 *
 * @author Ivano Bilenchi
 */

#ifndef COWL_LOGGER_H
#define COWL_LOGGER_H

#include "cowl_std.h"
#include "cowl_entity.h"

COWL_BEGIN_DECLS

/// @cond
typedef struct CowlAxiom const CowlAxiom;
typedef struct CowlClsExp const CowlClsExp;
typedef struct CowlIndividual const CowlIndividual;
typedef struct CowlIRI const CowlIRI;
typedef struct CowlObjPropExp const CowlObjPropExp;
typedef struct CowlOntology const CowlOntology;
typedef struct CowlOntologyId const CowlOntologyId;
typedef struct CowlString const CowlString;
/// @endcond

#pragma mark - Logger

/**
 * Provides logging facilities.
 *
 * A logger instance can log either to stdout, to file or to a memory buffer.
 */
typedef struct CowlLogger CowlLogger;

#pragma mark - Lifecycle

/**
 * Allocates a new logger instance that logs to stdout.
 *
 * @return Logger instance.
 */
CowlLogger* cowl_logger_alloc_console(void);

/**
 * Allocates a new logger instance that logs to file.
 *
 * @param path Path of the log file.
 * @return Logger instance.
 *
 * @note The path is copied by the logger, so you are still responsible for
 *       deallocating the string passed to this allocator.
 */
CowlLogger* cowl_logger_alloc_file(char const *path);

/**
 * Allocates a new logger that logs nowhere.
 *
 * @return Logger instance.
 */
CowlLogger* cowl_logger_alloc_null(void);

/**
 * Deallocates the logger instance.
 *
 * @param logger Logger instance.
 */
void cowl_logger_free(CowlLogger *logger);

#pragma mark - State

/**
 * Initializes the logger, ensuring its destination is correctly set up.
 * The effect depends on the logger type:
 *
 * - Console/Null: no effect.
 *
 * - File: opens the file in append mode.
 *
 * @param logger Logger instance.
 */
void cowl_logger_open(CowlLogger *logger);

/**
 * Deinitializes the logger, tearing down its destination.
 * The effect depends on the logger type:
 *
 * - Console/Null: no effect.
 *
 * - File: closes the file.
 *
 * @param logger Logger instance.
 */
void cowl_logger_close(CowlLogger *logger);

/**
 * Clears the logger, removing anything it has logged in the past.
 * The effect depends on the logger type:
 *
 * - Console/Null: no effect.
 *
 * - File: deletes the file.
 *
 * @param logger Logger instance.
 */
void cowl_logger_clear(CowlLogger *logger);

#pragma mark - Logging

/**
 * Logs the specified formatted string.
 *
 * @param logger Logger instance.
 * @param format Format string.
 * @param ... Format arguments.
 */
void cowl_logger_logf(CowlLogger *logger, char const *format, ...);

/**
 * Logs the specified counted string.
 *
 * @param logger Logger instance.
 * @param string String to log.
 */
void cowl_logger_log_string(CowlLogger *logger, CowlString *string);

/**
 * Logs the axioms in the specified ontology.
 *
 * @param logger Logger instance.
 * @param ontology Ontology to log.
 */
void cowl_logger_log_axioms_in_ontology(CowlLogger *logger, CowlOntology *ontology);

/**
 * Logs the entities in the specified ontology.
 *
 * @param logger Logger instance.
 * @param ontology Ontology to log.
 */
void cowl_logger_log_entities_in_ontology(CowlLogger *logger, CowlOntology *ontology);

/**
 * Logs the specified ontology identifier.
 *
 * @param logger Logger instance.
 * @param id Ontology identifier to log.
 */
void cowl_logger_log_ontology_id(CowlLogger *logger, CowlOntologyId *id);

/**
 * Logs the specified ontology.
 *
 * @param logger Logger instance.
 * @param ontology Ontology to log.
 */
void cowl_logger_log_ontology(CowlLogger *logger, CowlOntology *ontology);

/**
 * Logs the specified IRI.
 *
 * @param logger Logger instance.
 * @param iri IRI to log.
 */
void cowl_logger_log_iri(CowlLogger *logger, CowlIRI *iri);

/**
 * Logs the specified entity.
 *
 * @param logger Logger instance.
 * @param entity Entity to log.
 */
void cowl_logger_log_entity(CowlLogger *logger, CowlEntity entity);

/**
 * Logs the specified class expression.
 *
 * @param logger Logger instance.
 * @param exp Class expression to log.
 */
void cowl_logger_log_cls_exp(CowlLogger *logger, CowlClsExp *exp);

/**
 * Logs the specified individual.
 *
 * @param logger Logger instance.
 * @param individual Individual to log.
 */
void cowl_logger_log_individual(CowlLogger *logger, CowlIndividual *individual);

/**
 * Logs the specified object property expression.
 *
 * @param logger Logger instance.
 * @param exp Object property expression to log.
 */
void cowl_logger_log_obj_prop_exp(CowlLogger *logger, CowlObjPropExp *exp);

/**
 * Logs the specified axiom.
 *
 * @param logger Logger instance.
 * @param axiom Axiom to log.
 */
void cowl_logger_log_axiom(CowlLogger *logger, CowlAxiom *axiom);

#pragma mark - Other

/**
 * Returns the file path of this logger.
 *
 * @param logger Logger instance.
 * @return File path.
 *
 * @note Must only be used on a file logger.
 * @note The returned path is not copied, so you must not free it.
 */
char const* cowl_logger_get_path(CowlLogger *logger);

COWL_END_DECLS

#endif // COWL_LOGGER_H
