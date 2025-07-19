#pragma once

#include <stddef.h>

struct Label;
struct LabelBuilder;

struct LabelStack {
    struct Label *labels;
    size_t labels_count;
    size_t labels_capacity;

    char **items;
    size_t items_count;
    size_t items_capacity;
};

int
lstk_init(
    struct LabelStack *lstk
);

void
lstk_destory(
    struct LabelStack *lstk
);

struct Label *
lstk_push_label(
    struct LabelStack *lstk,
    const struct LabelBuilder *lb,
    size_t start,
    size_t length
);

char **
lstk_push_item(
    struct LabelStack *lstk,
    const char *entry
);
