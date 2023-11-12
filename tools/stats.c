/**
 * Outputs ontology statistics.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2023 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl.h"

static inline void log_error(char const *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
}

typedef struct Stat {
    UString name;
    ulib_uint value;
} Stat;

UVEC_INIT(Stat);

typedef struct Format {
    char const *name;
    ustream_ret (*write)(UOStream *, UVec(Stat) const *);
} Format;

static ustream_ret write_human(UOStream *stream, UVec(Stat) const *stats) {
    uvec_foreach (Stat, stats, stat) {
        cowl_write_ustring(stream, &stat.item->name);
        cowl_write_static(stream, ": ");
        cowl_write_uint(stream, stat.item->value);
        cowl_write_static(stream, "\n");
    }
    return stream->state;
}

static ustream_ret write_csv_header(UOStream *stream, UVec(Stat) const *stats) {
    cowl_write_ustring(stream, &uvec_get(Stat, stats, 0).name);
    UVec(Stat) remaining = uvec_view_from(Stat, stats, 1);
    uvec_foreach (Stat, &remaining, stat) {
        cowl_write_static(stream, ",");
        cowl_write_ustring(stream, &stat.item->name);
    }
    cowl_write_static(stream, "\n");
    return stream->state;
}

static ustream_ret write_csv_no_header(UOStream *stream, UVec(Stat) const *stats) {
    cowl_write_uint(stream, uvec_get(Stat, stats, 0).value);
    UVec(Stat) remaining = uvec_view_from(Stat, stats, 1);
    uvec_foreach (Stat, &remaining, stat) {
        cowl_write_static(stream, ",");
        cowl_write_uint(stream, stat.item->value);
    }
    cowl_write_static(stream, "\n");
    return stream->state;
}

static ustream_ret write_csv(UOStream *stream, UVec(Stat) const *stats) {
    write_csv_header(stream, stats);
    write_csv_no_header(stream, stats);
    return stream->state;
}

static Format const formats[] = {
    { "human", write_human },
    { "csv", write_csv },
    { "csv_header", write_csv_header },
    { "csv_no_header", write_csv_no_header },
};

static bool select_format(char const *format_str, Format *format) {
    if (strlen(format_str) == 0) {
        *format = formats[0];
        return true;
    }

    for (unsigned i = 0; i < ulib_array_count(formats); ++i) {
        if (strcmp(format_str, formats[i].name) == 0) {
            *format = formats[i];
            return true;
        }
    }

    log_error("Invalid format\"%s\".\n", format_str);
    return false;
}

static void write_usage(char const *cmd) {
    log_error("Usage: %s ontology_file [format]\nformats: ", cmd);
    for (ulib_uint i = 0; i < ulib_array_count(formats) - 1; ++i) {
        log_error("%s, ", formats[i].name);
    }
    log_error("%s\n", formats[ulib_array_count(formats) - 1].name);
}

static bool parse_args(int argc, char *argv[], Format *format, UString *path) {
    if (argc < 2) {
        write_usage(argv[0]);
        return false;
    }

    *path = ustring_wrap_buf(argv[1]);
    return select_format(argc >= 3 ? argv[2] : "", format);
}

static void handle_error(void *stream, CowlError const *error) {
    cowl_write_error(stream, error);
    cowl_write_static(stream, "\n");
}

static bool load_ontology(UString path, CowlOntology **onto) {
    if (cowl_init()) {
        log_error("Failed to initialize Cowl.\n");
        return false;
    }

    CowlErrorHandler handler = { .ctx = uostream_stderr(), .handle_error = handle_error };
    cowl_set_error_handler(handler);

    CowlManager *manager = cowl_manager();
    CowlOntology *l_onto = NULL;

    if (manager) {
        l_onto = cowl_manager_read_path(manager, path);
        cowl_release(manager);
    }

    if (!l_onto) {
        log_error("Could not load the ontology.\n");
        return false;
    }

    *onto = l_onto;
    return true;
}

static bool compute_global_stats(CowlOntology *onto, UVec(Stat) *dst) {
    Stat const global_stats[] = {
        {
            ustring_copy_literal("Axioms"),
            cowl_ontology_axiom_count(onto, false),
        },
        {
            ustring_copy_literal("Classes"),
            cowl_ontology_primitives_count(onto, COWL_PF_CLASS, false),
        },
        {
            ustring_copy_literal("Datatypes"),
            cowl_ontology_primitives_count(onto, COWL_PF_DATATYPE, false),
        },
        {
            ustring_copy_literal("Named individuals"),
            cowl_ontology_primitives_count(onto, COWL_PF_NAMED_IND, false),
        },
        {
            ustring_copy_literal("Anonymous individuals"),
            cowl_ontology_primitives_count(onto, COWL_PF_ANON_IND, false),
        },
        {
            ustring_copy_literal("Object properties"),
            cowl_ontology_primitives_count(onto, COWL_PF_OBJ_PROP, false),
        },
        {
            ustring_copy_literal("Data properties"),
            cowl_ontology_primitives_count(onto, COWL_PF_DATA_PROP, false),
        },
        {
            ustring_copy_literal("Annotation properties"),
            cowl_ontology_primitives_count(onto, COWL_PF_ANNOT_PROP, false),
        },
    };

    for (unsigned i = 0; i < ulib_array_count(global_stats); ++i) {
        if (uvec_push(Stat, dst, global_stats[i])) return false;
    }

    return true;
}

static bool compute_axiom_stats(CowlOntology *onto, UVec(Stat) *stats) {
    UString axioms_str = ustring_literal(" axioms");

    for (CowlAxiomType t = COWL_AT_FIRST; t < COWL_AT_COUNT; ++t) {
        CowlObjectType type = (CowlObjectType)(t + COWL_OT_FIRST_A);

        UString components[] = { cowl_object_type_to_ustring(type), axioms_str };
        UString stat_str = ustring_concat(components, ulib_array_count(components));
        if (ustring_is_null(stat_str)) return false;

        Stat stat = { stat_str, cowl_ontology_axiom_count_for_type(onto, t, false) };
        if (uvec_push(Stat, stats, stat)) return false;
    }

    return true;
}

static bool write_stats(CowlOntology *onto, Format format) {
    bool success = false;
    UVec(Stat) stats = uvec(Stat);

    if (!compute_global_stats(onto, &stats)) goto end;
    if (!compute_axiom_stats(onto, &stats)) goto end;
    if (format.write(uostream_std(), &stats)) goto end;
    success = true;

end:
    uvec_foreach (Stat, &stats, stat) {
        ustring_deinit(&stat.item->name);
    };
    uvec_deinit(Stat, &stats);

    if (!success) log_error("Failed to compute stats.\n");
    return success;
}

int main(int argc, char *argv[]) {
    int exit_code = EXIT_FAILURE;

    UString path;
    Format format;
    CowlOntology *onto;

    if (!parse_args(argc, argv, &format, &path)) goto end;
    if (!load_ontology(path, &onto)) goto end;
    if (!write_stats(onto, format)) goto end;
    exit_code = EXIT_SUCCESS;

end:
#if __SANITIZE_ADDRESS__
    cowl_release(onto);
    cowl_deinit();
#endif

    return exit_code;
}
