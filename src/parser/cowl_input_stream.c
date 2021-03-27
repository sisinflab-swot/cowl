/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_input_stream.h"
#include "cowl_raw_string.h"

static cowl_ret cowl_file_read(void *file, cowl_byte *buf, size_t count, size_t *read) {
    size_t const read_size = fread(buf, 1, count, file);
    if (read) *read = read_size;
    return count != read_size && ferror(file) ? COWL_ERR_IO : COWL_OK;
}

static cowl_ret cowl_file_close(void *file) {
    return fclose(file) == 0 ? COWL_OK : COWL_ERR_IO;
}

static cowl_ret cowl_raw_string_read(void *string, cowl_byte *buf, size_t count, size_t *read) {
    CowlRawString *raw_string = string;
    size_t const string_size = raw_string->length + 1;
    size_t const read_size = count < string_size ? count : string_size;
    memcpy(buf, raw_string->cstring, read_size);
    raw_string->cstring += read_size;
    if (read) *read = read_size;
    return COWL_OK;
}

static cowl_ret cowl_raw_string_free(void *string) {
    cowl_free(string);
    return COWL_OK;
}

cowl_ret cowl_input_stream_deinit(CowlInputStream *stream) {
    return stream->free ? stream->free(stream->ctx) : COWL_OK;
}

cowl_ret cowl_input_stream_read_bytes(CowlInputStream const *stream, cowl_byte *buf,
                                      size_t count, size_t *read) {
    return stream->read_bytes(stream->ctx, buf, count, read);
}

cowl_ret cowl_input_stream_from_path(CowlInputStream *stream, char const *path) {
    stream->description = path;

    FILE *in_file = fopen(path, "rb");
    cowl_ret ret;

    if (in_file) {
        stream->ctx = in_file;
        stream->read_bytes = cowl_file_read;
        stream->free = cowl_file_close;
        ret = COWL_OK;
    } else {
        ret = COWL_ERR_IO;
    }

    return ret;
}

cowl_ret cowl_input_stream_from_file(CowlInputStream *stream, FILE *file) {
    stream->ctx = file;
    stream->read_bytes = cowl_file_read;
    return COWL_OK;
}

cowl_ret cowl_input_stream_from_cstring(CowlInputStream *stream, char const *cstring,
                                        size_t length) {
    CowlRawString *raw_string = cowl_alloc(raw_string);
    cowl_ret ret;

    if (raw_string) {
        *raw_string = cowl_raw_string_init(cstring, length, false);
        stream->ctx = raw_string;
        stream->read_bytes = cowl_raw_string_read;
        stream->free = cowl_raw_string_free;
        ret = COWL_OK;
    } else {
        ret = COWL_ERR_MEM;
    }

    return ret;
}
