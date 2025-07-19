#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <lookpath2/LabelStack/LabelStack.h>
#include <lookpath2/LabelStack/Label.h>

static const size_t INIT_ITEMS_CAP = 63;
static const size_t INIT_LABELS_CAPACITY = 31;

static inline size_t
next_capacity(
    size_t length,
    size_t capacity
) {
    if (capacity < length) {
        return 2 * capacity + 1;
    }

    return capacity;
}

static inline void *
prepush(
    void *stkptr,
    size_t *length,
    size_t *capacity,
    size_t elem_size
) {
    const size_t cur_cap = *capacity;
    const size_t set_len = *length + 1;
    const size_t set_cap = next_capacity(set_len, cur_cap);

    if (cur_cap < set_cap) {
        stkptr = realloc(stkptr, set_cap * elem_size);
    }

    if (stkptr) {
        *length = set_len;
        *capacity = set_cap;
    }

    return stkptr;
}

int
lstk_init(
    struct LabelStack *lstk
) {
    struct LabelStack init = (struct LabelStack) {
        .items = malloc(INIT_ITEMS_CAP * sizeof(*init.items)),
        .items_capacity = INIT_ITEMS_CAP,

        .labels = malloc(INIT_LABELS_CAPACITY * sizeof(*init.labels)),
        .labels_capacity = INIT_LABELS_CAPACITY
    };

    if (!init.labels || !init.items) {
        free(init.labels);
        free(init.items);
        return -ENOMEM;
    }

    *lstk = init;
    return 0;
}

void
lstk_destory(
    struct LabelStack *lstk
) {
    while (lstk->items_count) {
        free(lstk->items[--lstk->items_count]);
    }

    while (lstk->labels_count) {
        free(lstk->labels[--lstk->labels_count].str);
    }

    free(lstk->labels);
    free(lstk->items);

    *lstk = (struct LabelStack) {0};
}

char **
lstk_push_item(
    struct LabelStack *lstk,
    const char *entry
) {
    const size_t slot = lstk->items_count;

    char *entry_copy = strndup(entry, FILENAME_MAX);
    void *next_items = prepush(
        lstk->items,
        &lstk->items_count,
        &lstk->items_capacity,
        sizeof(*lstk->items)
    );

    if (!entry_copy || !next_items) {
        free(entry_copy);
        free(next_items);
        return NULL;
    }

    lstk->items = next_items;
    lstk->items[slot] = entry_copy;

    return &lstk->items[slot];
}

struct Label *
lstk_push_label(
    struct LabelStack *lstk,
    const struct LabelBuilder *lb,
    size_t idx_start,
    size_t idx_count
) {
    struct Label insert = {0};
    const size_t slot = lstk->labels_count;

    void *next_labels = prepush(
        lstk->labels,
        &lstk->labels_count,
        &lstk->labels_capacity,
        sizeof(*lstk->labels)
    );

    if (
        !next_labels ||
        label_from_lb(&insert, lb, idx_start, idx_count) < 0
    ) {
        free(next_labels);
        return NULL;
    }

    lstk->labels = next_labels;
    lstk->labels[slot] = insert;

    return &lstk->labels[slot];
}
