# Cowl Changelog

All notable changes to Cowl will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/).
Cowl adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

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

[0.2.2]: https://github.com/sisinflab-swot/cowl/compare/v0.2.1...v0.2.2
[0.2.1]: https://github.com/sisinflab-swot/cowl/compare/v0.2.0...v0.2.1
[0.2.0]: https://github.com/sisinflab-swot/cowl/compare/v0.1.0...v0.2.0
[0.1.0]: https://github.com/sisinflab-swot/cowl/releases/tag/v0.1.0
