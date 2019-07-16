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
cowl_struct_decl(CowlOntology);
cowl_struct_decl(CowlString);
cowl_struct_decl(CowlLogger);
/// @endcond

/**
 * Provides logging facilities.
 *
 * A logger instance can log either to stdout or to a file.
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
 * Logs the specified string.
 *
 * @param logger The logger.
 * @param string String to log.
 *
 * @public @memberof CowlLogger
 */
COWL_PUBLIC
void cowl_logger_log(CowlLogger *logger, CowlString *string);

/**
 * Logs and releases the specified string.
 *
 * @param logger The logger.
 * @param string String to log.
 *
 * @public @memberof CowlLogger
 */
COWL_PUBLIC
void cowl_logger_consume(CowlLogger *logger, CowlString *string);

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
