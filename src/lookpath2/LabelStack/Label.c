#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <unistd.h>

#include <lookpath2/LabelStack/Label.h>

int
label_from_lb(
    struct Label *dest,
    const struct LabelBuilder *lb,
    size_t idx_start,
    size_t idx_count
) {
    struct Label init = (struct Label) {
        .str = strndup(lb->buffer, lb->buffer_length),
        .str_length = lb->cursor,
        .idx_start = idx_start,
        .idx_count = idx_count
    };

    if (!init.str) {
        return -1;
    }

    *dest = init;
    return 0;
}

static inline bool
is_valid_params(
    const struct LabelBuilder *lb,
    size_t write_length
) {
    if (lb->buffer_length <= lb->cursor) {
        return false;
    }

    if (lb->buffer_length - lb->cursor <= write_length) {
        return false;
    }

    return true;
}

static inline size_t
lb_remaining(
    struct LabelBuilder *lb
) {
    if (lb->buffer_length <= lb->cursor) {
        return 0;
    }

    return lb->buffer_length - lb->cursor;
}

int
lb_add_filepath(
    struct LabelBuilder *lb,
    const char *filepath,
    size_t filepath_length
) {
    if (!is_valid_params(lb, filepath_length)) {
        return -1;
    }

    memcpy(&lb->buffer[lb->cursor], filepath, filepath_length);

    lb->cursor += filepath_length;
    lb->buffer[lb->cursor] = '\0';

    return 0;
}

int
lb_add_linkinfo(
    struct LabelBuilder *lb,
    const char *filepath,
    size_t filepath_length
) {
    char linkbuf[PATH_MAX];
    ssize_t realpath_length = 0;

    realpath_length = readlink(filepath, &linkbuf[0], sizeof(linkbuf) - 1);
    if (errno == EINVAL) {
        return 0;
    }
    if (errno != 0) {
        return -1;
    }


    linkbuf[realpath_length] = '\0';
    snprintf(&lb->buffer[lb->cursor], lb_remaining(lb), " -> %s", linkbuf);

    return 0;
}
