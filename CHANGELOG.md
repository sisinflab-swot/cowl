# Cowl Changelog

All notable changes to Cowl will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/), and
Cowl adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

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

[0.2.0]: https://github.com/sisinflab-swot/cowl/compare/v0.1.0...v0.2.0
[0.1.0]: https://github.com/sisinflab-swot/cowl/releases/tag/v0.1.0
