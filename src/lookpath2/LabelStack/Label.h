#pragma once

#include <stddef.h>

struct Label {
    char *str;
    size_t str_length;
    size_t idx_start;
    size_t idx_count;
};

struct LabelBuilder {
    char *buffer;
    size_t buffer_length;

    size_t cursor;
};

int
label_from_lb(
    struct Label *dest,
    const struct LabelBuilder *lb,
    size_t idx_start,
    size_t idx_count
);

int
lb_add_filepath(
    struct LabelBuilder *lb,
    const char *filepath,
    size_t filepath_length
);

int
lb_add_linkinfo(
    struct LabelBuilder *lb,
    const char *filepath,
    size_t filepath_length
);
