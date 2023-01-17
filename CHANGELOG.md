# Cowl Changelog

All notable changes to Cowl will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/).
Cowl adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [0.6.2] - 2023-01-17
### Added
- String interning: `cowl_string_opt`, `cowl_string_intern`, `CowlStringOpts`.

### Changed
- `cowl_ontology_get_annot` returns an empty vector rather than NULL.
- `cowl_obj_card_get_filler` returns *owl:Thing* rather than NULL.
- `cowl_data_card_get_range` returns *rdfs:Literal* rather than NULL.

### Fixed
- NULL pointer dereference in `cowl_equals_impl`.
- Serialization of unqualified object quantifiers.
- Serialization of *SubAnnotationPropertyOf* axioms.
- Serialization of nested annotations.
- Serialization of inverse object properties.
- Improved handling of out-of-memory conditions.

## [0.6.1] - 2022-12-07
### Added
- `cowl_get_iri`, `cowl_equals_iri_string`.
- `cowl_manager_stream_ontology`.
- `cowl_anon_ind_from_static`.
- `cowl_literal_from_string`, `cowl_literal_from_static`.
- `cowl_sym_table_register_prefix_raw`.

### Changed
- Updated to RDF 1.1 literals.
- Slightly optimized `CowlIRI` constructor.
- Signature of `handle_axiom` field of `CowlStreamConfig`.

### Fixed
- Serialization of ontology import IRIs.

## [0.6.0] - 2022-11-06
### Added
- Ontology stream parsing (`CowlStream`, `CowlStreamConfig`).
- Ontology serialization (`CowlWriter`, `CowlSymTable`).
- Ontology editing (`cowl_ontology_add_*`, `cowl_ontology_remove_*` functions).
- Support for Arduino boards.
- `CowlVector` and `CowlTable`.
- Placeholder types (`CowlAny` and similar).
- `cowl_ontology_primitives_count`, `cowl_ontology_axiom_count_for_primitive`,
  `cowl_ontology_has_primitive`, `cowl_ontology_iterate_axioms_for_primitive`.
- `cowl_primitive_flags_from_type`, `cowl_primitive_flags_has_type`.
- `cowl_iterator_count`.
- `COWL_LIBRARY_TYPE` CMake variable.

### Changed
- Renamed `CowlParser` to `CowlReader`.
- Renamed `cowl_object_get_type` to `cowl_get_type`.
- Renamed `CowlOntologyId` struct fields.
- Signature of `CowlOntology` querying functions by adding an `imports` parameter.
- Dropped `*_init` and `*_get` suffixes from most of the API.
- Renamed `cowl_api_*` functions.
- Significantly reduced code size.

### Removed
- `CowlFacet`.
- `cowl_ontology_axiom_count_for_annot_prop`, `cowl_ontology_axiom_count_for_class`,
  `cowl_ontology_axiom_count_for_data_prop`, `cowl_ontology_axiom_count_for_datatype`,
  `cowl_ontology_axiom_count_for_obj_prop`, `cowl_ontology_axiom_count_for_named_ind`.
- `cowl_ontology_classes_count`, `cowl_ontology_datatypes_count`,
  `cowl_ontology_obj_props_count`, `cowl_ontology_data_props_count`,
  `cowl_ontology_annot_props_count`, `cowl_ontology_named_inds_count`.
- `cowl_ontology_iterate_classes`, `cowl_ontology_iterate_datatypes`,
  `cowl_ontology_iterate_data_props`, `cowl_ontology_iterate_obj_props`,
  `cowl_ontology_iterate_annot_props`, `cowl_ontology_iterate_named_inds`,
  `cowl_ontology_iterate_anon_inds`.
- `cowl_ontology_iterate_axioms_for_annot_prop`, `cowl_ontology_iterate_axioms_for_class`,
  `cowl_ontology_iterate_axioms_for_data_prop`, `cowl_ontology_iterate_axioms_for_datatype`,
  `cowl_ontology_iterate_axioms_for_obj_prop`, `cowl_ontology_iterate_axioms_for_named_ind`,
  `cowl_ontology_iterate_axioms_for_anon_ind`.
- `cowl_ontology_has_entity`.
- `get_line` field from `CowlParser`.
- `COWL_STATIC`, `COWL_SHARED` and `COWL_OBJECT` CMake variables.

### Fixed
- Compilation in C++ projects.
- NULL pointer dereference in `CowlOntology` when entities have no associated axioms.
- HasKey axiom not accepting empty vectors.

## [0.5.3] - 2022-04-27
### Added
- `cowl_string_get_raw`.
- `cowl_ret_to_string`.
- `cowl_annot_prop_from_string`, `cowl_class_from_string`, `cowl_data_prop_from_string`,
  `cowl_datatype_from_string`, `cowl_iri_from_string`, `cowl_named_ind_from_string`,
  `cowl_obj_prop_from_string`.

### Changed
- Signature of `cowl_string_get`, `cowl_manager_read_path`, `cowl_manager_read_string`,
  `cowl_parser_ctx_handle_error`.
- Replaced most `CowlObjectTable` objects in the API to `CowlObjectVec`.
- Updated `uLib` to the latest version.

### Removed
- `cowl_ret_to_cstring`.
- `cowl_annot_prop_from_cstring`, `cowl_class_from_cstring`, `cowl_data_prop_from_cstring`,
  `cowl_datatype_from_cstring`, `cowl_iri_from_cstring`, `cowl_named_ind_from_cstring`,
  `cowl_obj_prop_from_cstring`.
- `cowl_struct` and `cowl_enum`.

### Fixed
- `COWL_LTO` and `COWL_EMBEDDED` CMake options are now correctly propagated to uLib.
- DataExactCardinality incorrectly parsed as DataMaxCardinality.
- Error location not reported when using the default parser.

## [0.5.2] - 2021-12-17
### Added
- `cowl_ontology_has_entity`.
- Missing XSD datatypes in `CowlXSDVocab`.
- Object library target.

### Changed
- Updated `uLib` to the latest version.
- Replaced base types with `uLib` types.
- Replaced `CowlVersion` with `UVersion`.
- Renamed `CowlReader` to `CowlManager`.
- Signature of `CowlParser`'s `parse` function.

### Removed
- `CowlLogger`, `CowlStrBuf`, `CowlVersion` (superseded by `uLib`).
- `cowl_parser_ctx_get_stream`.

## [0.5.1] - 2021-10-14
### Added
- `cowl_ontology_has_entity`.
- `cowl_iterator_vec_init` and `cowl_iterator_set_init`.

### Changed
- Renamed `CowlOntologyID` to `CowlOntologyId`.
- Changed argument order of `*_iterate_primitives` functions to match convention.
- Reworked parser build logic.

### Removed
- `cowl_cls_exp_set_alloc`, `cowl_data_prop_exp_set_alloc`, `cowl_data_range_set_alloc`,
  `cowl_facet_restr_set_alloc`, `cowl_individual_set_alloc`, `cowl_literal_set_alloc`,
  `cowl_obj_prop_exp_set_alloc` (use plain `uhset_alloc(CowlObjectTable)` instead).

### Fixed
- UaF in `cowl_logger_release`.
- Return of incomplete `CowlOntologyID` type.
- Compilation via MSVC.
- Warnings when compiling via GCC.
- Warnings due to macros expanding to empty statements.

## [0.5.0] - 2021-03-28
### Added
- Support for multiple parsers via `CowlReader` and `CowlParser` API.
- Parsing from arbitrary streams via `CowlInputStream` API.
- Support for global handlers via `cowl_api_set_import_loader`,
  `cowl_api_set_import_handler` and `cowl_api_set_parser`.
- `cowl_object_set_insert`, `cowl_object_vec_push`.
- `cowl_object_to_debug_string`.

### Changed
- Replaced typed collection with `CowlObject`-based ones to reduce code size.
- Reworked handling of errors via `CowlErrorHandler` API.
- Renamed `CowlImportsLoader` to `CowlImportLoader`.
- Renamed `CowlNodeID` to `CowlNodeId`.
- Changed `CowlNodeId` type from `cowl_uint` to `uintptr_t`.
- Renamed `CowlParser` to `CowlReader`.
- Improved performance of string interning and object hashing.
- `CowlLogger` is flushed after each write.
- Bumped minimum CMake version to 3.18.

### Removed
- `cowl_error_init`, `cowl_error_init_cstring`, `cowl_error_retain`, `cowl_error_release`.

### Fixed
- Access to uninitialized memory while iterating equivalent classes.
- Memory leaks in error handling logic.
- Memory leak when parsing lists with duplicated elements.
- `cowl_logger_file_get` not using `cowl_malloc` for memory allocation.
- Compilation of benchmark target.

## [0.4.1] - 2020-11-22
### Added
- `COWL_MALLOC`, `COWL_REALLOC` and `COWL_FREE` CMake variables to specify
  custom allocators.
- `COWL_USER_HEADERS` and `COWL_USER_SOURCES` CMake variables to specify
  custom header and source files.

### Changed
- Depend on `ULib` rather than on `Vector` and `UHash`.
- Replaced `Vector` with `UVec`.
- Replaced `CowlFlags` with `UFlags`.
- Renamed `cowl_uint_t` to `cowl_uint` for POSIX compatibility.
- Renamed `cowl_ret_t` to `cowl_ret` for POSIX compatibility.

### Removed
- `COWL_ALLOC_HEADERS` and `COWL_ALLOC_SOURCES` CMake variables.

## [0.4.0] - 2020-11-05
### Added
- `CowlObject` and related API.
- `CowlVersion` and related API.
- Automated memory leak tests.

### Changed
- Most public Cowl types now inherit from `CowlObject`, which acts as the root type.
- `CowlIterator` is now an actual type, and iteration APIs have been reworked.
- `CowlEntity`, `CowlPrimitive` and `CowlAnnotValue` are not tagged unions anymore,
  but are exposed as opaque types which inherit from `CowlObject`.
- Custom allocators can now be specified via the `COWL_ALLOC_HEADERS`
  and `COWL_ALLOC_SOURCES` CMake variables.
- Bumped minimum CMake version to 3.16.

### Fixed
- `cowl_strdup` not using `cowl_malloc` for memory allocation.
- Memory leaks caused by incorrect string interning.

## [0.3.0] - 2020-06-09
### Added
- Error handling via `cowl_ret_t` return values.
- Support for custom allocators via `cowl_malloc`, `cowl_realloc` and `cowl_free`.
- `CowlPrimitive` and related iteration API.
- `cowl_logger_logs`.

### Changed
- Memory exhaustion errors are explicitly handled.
- Headers are copied when building each library target.

### Fixed
- UaF in `cowl_string_api_deinit`.
- Incorrect hash computation for `CowlOntologyID`.
- Compilation via MSVC.

## [0.2.2] - 2020-02-27
### Added
- `from_cstring` and `from_static` constructors for all entities.
- Control over the size of the `cowl_uint_t` type through the `COWL_TINY`
  and `COWL_HUGE` preprocessor definitions.
- Tests for `CowlIRI`.

### Changed
- Modernized build configuration, which now requires CMake 3.12 or later.
- Instance tables for OWL entities are now initialized in `cowl_api_init`
  and deinitialized in `cowl_api_deinit`.

### Fixed
- Docs for `CowlErrorCode`.
- `cowl_api_init` and `cowl_api_deinit` symbols not exported.
- Errors in lexer generation by bumping the minimum required Flex version to 2.6.4.
- UaF when releasing interned strings with `cowl_string_release`.
- `cowl_iri_get` sometimes not returning equal IRIs for prefix-suffix pairs
  resulting in identical string representations.

## [0.2.1] - 2019-11-19
### Added
- `cowl_iri_to_string_no_brackets`.
- `cowl_string_to_string`.
- Tests for `CowlString`.

### Changed
- Reduced memory usage via improved `CowlString` interning and reworked `CowlOntology` internals.
- Minor documentation updates.

### Fixed
- Handling of language tags in literals with an explicit datatype.
- Potential clashes in user code by renaming `Vector(char)` to `Vector(CowlChar)`.
- Const-ness of OWL vocabulary fields.

## [0.2.0] - 2019-07-23
### Added
- String representation API (`to_string` functions).
- Anonymous individual iteration API (`iterate_anon_inds` functions).
- Count API for entities and anonymous individuals in `CowlOntology`.
- `cowl_ontology_get_axiom_count_for_type`.
- `cowl_ontology_get_annot`.
- `cowl_iri_get`.
- `cowl_logger_consume`, convenient to use with `to_string` functions.
- Preliminary test suite.
- Benchmark target.

### Changed
- Improved recognition of IRI remainders.
- `cowl_logger_log_ontology` also logs imported ontologies.
- Optimized embedded build for code size.
- Use faster but larget lexer tables in desktop builds.
- Reduced heap memory usage.
- Minor documentation updates.

### Removed
- Most of `CowlLogger`'s logging API, in favor of `to_string` functions.
- `cowl_logger_open` and `cowl_logger_close`.

### Fixed
- Type confusion in `CowlDataCard`.
- Incorrect parsing of `CowlHasKey`.
- Deserialization of negative `CowlObjPropAssertAxiom`.

## [0.1.0] - 2019-07-12
### Added
- OWL 2 data model.
- Functional syntax ontology parser.
- Ontology querying API.
- Logging API.

[0.6.2]: https://github.com/sisinflab-swot/cowl/compare/v0.6.1...v0.6.2
[0.6.1]: https://github.com/sisinflab-swot/cowl/compare/v0.6.0...v0.6.1
[0.6.0]: https://github.com/sisinflab-swot/cowl/compare/v0.5.3...v0.6.0
[0.5.3]: https://github.com/sisinflab-swot/cowl/compare/v0.5.2...v0.5.3
[0.5.2]: https://github.com/sisinflab-swot/cowl/compare/v0.5.1...v0.5.2
[0.5.1]: https://github.com/sisinflab-swot/cowl/compare/v0.5.0...v0.5.1
[0.5.0]: https://github.com/sisinflab-swot/cowl/compare/v0.4.1...v0.5.0
[0.4.1]: https://github.com/sisinflab-swot/cowl/compare/v0.4.0...v0.4.1
[0.4.0]: https://github.com/sisinflab-swot/cowl/compare/v0.3.0...v0.4.0
[0.3.0]: https://github.com/sisinflab-swot/cowl/compare/v0.2.2...v0.3.0
[0.2.2]: https://github.com/sisinflab-swot/cowl/compare/v0.2.1...v0.2.2
[0.2.1]: https://github.com/sisinflab-swot/cowl/compare/v0.2.0...v0.2.1
[0.2.0]: https://github.com/sisinflab-swot/cowl/compare/v0.1.0...v0.2.0
[0.1.0]: https://github.com/sisinflab-swot/cowl/releases/tag/v0.1.0
