/** @file
 * Declares the logging API.
 *
 * @author Ivano Bilenchi
 */

#ifndef COWL_LOGGER_H
#define COWL_LOGGER_H

#include "cowl_annot_value.h"
#include "cowl_entity.h"
#include "cowl_error.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlAnnotation);
cowl_struct_decl(CowlAxiom);
cowl_struct_decl(CowlClsExp);
cowl_struct_decl(CowlDataPropExp);
cowl_struct_decl(CowlDataRange);
cowl_struct_decl(CowlIndividual);
cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlLiteral);
cowl_struct_decl(CowlObjPropExp);
cowl_struct_decl(CowlOntology);
cowl_struct_decl(CowlOntologyID);
cowl_struct_decl(CowlString);
/// @endcond

/**
 * Provides logging facilities.
 *
 * A logger instance can log either to stdout, to file or to a memory buffer.
 */
cowl_struct_decl(CowlLogger);

/// @name Lifecycle

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

/// @name State

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

/// @name Logging

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
 * @param onto Ontology to log.
 */
void cowl_logger_log_axioms_in_ontology(CowlLogger *logger, CowlOntology *onto);

/**
 * Logs the entities in the specified ontology.
 *
 * @param logger Logger instance.
 * @param onto Ontology to log.
 */
void cowl_logger_log_entities_in_ontology(CowlLogger *logger, CowlOntology *onto);

/**
 * Logs the specified ontology identifier.
 *
 * @param logger Logger instance.
 * @param id Ontology identifier to log.
 */
void cowl_logger_log_ontology_id(CowlLogger *logger, CowlOntologyID *id);

/**
 * Logs the specified ontology.
 *
 * @param logger Logger instance.
 * @param onto Ontology to log.
 */
void cowl_logger_log_ontology(CowlLogger *logger, CowlOntology *onto);

/**
 * Logs the specified annotation.
 *
 * @param logger Logger instance.
 * @param annotation Annotation to log.
 */
void cowl_logger_log_annotation(CowlLogger *logger, CowlAnnotation *annotation);

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
 * Logs the specified annotation value.
 *
 * @param logger Logger instance.
 * @param value Annotation value to log.
 */
void cowl_logger_log_annot_value(CowlLogger *logger, CowlAnnotValue value);

/**
 * Logs the specified annotation property.
 *
 * @param logger Logger instance.
 * @param prop Annotation property to log.
 */
void cowl_logger_log_annot_prop(CowlLogger *logger, CowlAnnotProp *prop);

/**
 * Logs the specified class expression.
 *
 * @param logger Logger instance.
 * @param exp Class expression to log.
 */
void cowl_logger_log_cls_exp(CowlLogger *logger, CowlClsExp *exp);

/**
 * Logs the specified data property expression.
 *
 * @param logger Logger instance.
 * @param exp Data property expression to log.
 */
void cowl_logger_log_data_prop_exp(CowlLogger *logger, CowlDataPropExp *exp);

/**
 * Logs the specified data range.
 *
 * @param logger Logger instance.
 * @param exp Data range to log.
 */
void cowl_logger_log_data_range(CowlLogger *logger, CowlDataRange *range);

/**
 * Logs the specified individual.
 *
 * @param logger Logger instance.
 * @param ind Individual to log.
 */
void cowl_logger_log_individual(CowlLogger *logger, CowlIndividual *ind);

/**
 * Logs the specified literal.
 *
 * @param logger Logger instance.
 * @param literal Literal to log.
 */
void cowl_logger_log_literal(CowlLogger *logger, CowlLiteral *literal);

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

/**
 * Logs the specified error.
 *
 * @param logger Logger instance.
 * @param error Error to log.
 */
 void cowl_logger_log_error(CowlLogger *logger, CowlError error);

COWL_END_DECLS

#endif // COWL_LOGGER_H
