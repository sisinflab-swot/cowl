/**
 * Declares CowlLogger and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
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
cowl_struct_decl(CowlLogger);
/// @endcond

/**
 * Provides logging facilities.
 *
 * A logger instance can log either to stdout, to file or to a memory buffer.
 *
 * @struct CowlLogger
 */

/// @name Lifecycle

/**
 * Returns a retained logger that logs to stdout.
 *
 * @return Retained logger.
 *
 * @public @memberof CowlLogger
 */
COWL_PUBLIC
CowlLogger* cowl_logger_console_get(void);

/**
 * Returns a retained logger that logs to the specified file.
 *
 * @param path Path of the log file.
 * @return Retained logger.
 *
 * @note The path is copied by the logger, so you are still responsible for
 *       deallocating the string passed to this allocator.
 *
 * @public @memberof CowlLogger
 */
COWL_PUBLIC
CowlLogger* cowl_logger_file_get(char const *path);

/**
 * Returns a retained logger that logs nowhere.
 *
 * @return Retained logger.
 *
 * @public @memberof CowlLogger
 */
COWL_PUBLIC
CowlLogger* cowl_logger_null_get(void);

/**
 * Retains the specified logger.
 *
 * @param logger The logger.
 * @return Retained logger.
 *
 * @public @memberof CowlLogger
 */
COWL_PUBLIC
CowlLogger* cowl_logger_retain(CowlLogger *logger);

/**
 * Releases the specified logger.
 *
 * @param logger The logger.
 *
 * @public @memberof CowlLogger
 */
COWL_PUBLIC
void cowl_logger_release(CowlLogger *logger);

/// @name State

/**
 * Initializes the logger, ensuring its destination is correctly set up.
 * The effect depends on the logger type:
 *
 * - Console/Null: no effect.
 *
 * - File: opens the file in append mode.
 *
 * @param logger The logger.
 *
 * @public @memberof CowlLogger
 */
COWL_PUBLIC
void cowl_logger_open(CowlLogger *logger);

/**
 * Deinitializes the logger, tearing down its destination.
 * The effect depends on the logger type:
 *
 * - Console/Null: no effect.
 *
 * - File: closes the file.
 *
 * @param logger The logger.
 *
 * @public @memberof CowlLogger
 */
COWL_PUBLIC
void cowl_logger_close(CowlLogger *logger);

/**
 * Clears the logger, removing anything it has logged in the past.
 * The effect depends on the logger type:
 *
 * - Console/Null: no effect.
 *
 * - File: deletes the file.
 *
 * @param logger The logger.
 *
 * @public @memberof CowlLogger
 */
COWL_PUBLIC
void cowl_logger_clear(CowlLogger *logger);

/**
 * Returns the file path of this logger.
 *
 * @param logger The logger.
 * @return File path.
 *
 * @note Must only be used on a file logger.
 * @note The returned path is not copied, so you must not free it.
 *
 * @public @memberof CowlLogger
 */
COWL_PUBLIC
char const* cowl_logger_get_path(CowlLogger *logger);

/// @name Logging

/**
 * Logs the specified formatted string.
 *
 * @param logger The logger.
 * @param format Format string.
 * @param ... Format arguments.
 *
 * @public @memberof CowlLogger
 */
COWL_PUBLIC
void cowl_logger_logf(CowlLogger *logger, char const *format, ...);

/**
 * Logs the specified counted string.
 *
 * @param logger The logger.
 * @param string String to log.
 *
 * @public @memberof CowlLogger
 */
COWL_PUBLIC
void cowl_logger_log_string(CowlLogger *logger, CowlString *string);

/**
 * Logs the axioms in the specified ontology.
 *
 * @param logger The logger.
 * @param onto Ontology to log.
 *
 * @public @memberof CowlLogger
 */
COWL_PUBLIC
void cowl_logger_log_axioms_in_ontology(CowlLogger *logger, CowlOntology *onto);

/**
 * Logs the entities in the specified ontology.
 *
 * @param logger The logger.
 * @param onto Ontology to log.
 *
 * @public @memberof CowlLogger
 */
COWL_PUBLIC
void cowl_logger_log_entities_in_ontology(CowlLogger *logger, CowlOntology *onto);

/**
 * Logs the specified ontology identifier.
 *
 * @param logger The logger.
 * @param id Ontology identifier to log.
 *
 * @public @memberof CowlLogger
 */
COWL_PUBLIC
void cowl_logger_log_ontology_id(CowlLogger *logger, CowlOntologyID *id);

/**
 * Logs the specified ontology.
 *
 * @param logger The logger.
 * @param onto Ontology to log.
 *
 * @public @memberof CowlLogger
 */
COWL_PUBLIC
void cowl_logger_log_ontology(CowlLogger *logger, CowlOntology *onto);

/**
 * Logs the specified annotation.
 *
 * @param logger The logger.
 * @param annotation Annotation to log.
 *
 * @public @memberof CowlLogger
 */
COWL_PUBLIC
void cowl_logger_log_annotation(CowlLogger *logger, CowlAnnotation *annotation);

/**
 * Logs the specified IRI.
 *
 * @param logger The logger.
 * @param iri IRI to log.
 *
 * @public @memberof CowlLogger
 */
COWL_PUBLIC
void cowl_logger_log_iri(CowlLogger *logger, CowlIRI *iri);

/**
 * Logs the specified entity.
 *
 * @param logger The logger.
 * @param entity Entity to log.
 *
 * @public @memberof CowlLogger
 */
COWL_PUBLIC
void cowl_logger_log_entity(CowlLogger *logger, CowlEntity entity);

/**
 * Logs the specified annotation value.
 *
 * @param logger The logger.
 * @param value Annotation value to log.
 *
 * @public @memberof CowlLogger
 */
COWL_PUBLIC
void cowl_logger_log_annot_value(CowlLogger *logger, CowlAnnotValue value);

/**
 * Logs the specified annotation property.
 *
 * @param logger The logger.
 * @param prop Annotation property to log.
 *
 * @public @memberof CowlLogger
 */
COWL_PUBLIC
void cowl_logger_log_annot_prop(CowlLogger *logger, CowlAnnotProp *prop);

/**
 * Logs the specified class expression.
 *
 * @param logger The logger.
 * @param exp Class expression to log.
 *
 * @public @memberof CowlLogger
 */
COWL_PUBLIC
void cowl_logger_log_cls_exp(CowlLogger *logger, CowlClsExp *exp);

/**
 * Logs the specified data property expression.
 *
 * @param logger The logger.
 * @param exp Data property expression to log.
 *
 * @public @memberof CowlLogger
 */
COWL_PUBLIC
void cowl_logger_log_data_prop_exp(CowlLogger *logger, CowlDataPropExp *exp);

/**
 * Logs the specified data range.
 *
 * @param logger The logger.
 * @param range Data range to log.
 *
 * @public @memberof CowlLogger
 */
COWL_PUBLIC
void cowl_logger_log_data_range(CowlLogger *logger, CowlDataRange *range);

/**
 * Logs the specified individual.
 *
 * @param logger The logger.
 * @param ind Individual to log.
 *
 * @public @memberof CowlLogger
 */
COWL_PUBLIC
void cowl_logger_log_individual(CowlLogger *logger, CowlIndividual *ind);

/**
 * Logs the specified literal.
 *
 * @param logger The logger.
 * @param literal Literal to log.
 *
 * @public @memberof CowlLogger
 */
COWL_PUBLIC
void cowl_logger_log_literal(CowlLogger *logger, CowlLiteral *literal);

/**
 * Logs the specified object property expression.
 *
 * @param logger The logger.
 * @param exp Object property expression to log.
 *
 * @public @memberof CowlLogger
 */
COWL_PUBLIC
void cowl_logger_log_obj_prop_exp(CowlLogger *logger, CowlObjPropExp *exp);

/**
 * Logs the specified axiom.
 *
 * @param logger The logger.
 * @param axiom Axiom to log.
 *
 * @public @memberof CowlLogger
 */
COWL_PUBLIC
void cowl_logger_log_axiom(CowlLogger *logger, CowlAxiom *axiom);

/**
 * Logs the specified error.
 *
 * @param logger The logger.
 * @param error Error to log.
 *
 * @public @memberof CowlLogger
 */
COWL_PUBLIC
void cowl_logger_log_error(CowlLogger *logger, CowlError error);

/**
 * Logs the specified errors.
 *
 * @param logger The logger.
 * @param errors Errors to log.
 *
 * @public @memberof CowlLogger
 */
COWL_PUBLIC
void cowl_logger_log_errors(CowlLogger *logger, Vector(CowlError) *errors);

COWL_END_DECLS

#endif // COWL_LOGGER_H
