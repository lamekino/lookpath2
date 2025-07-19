#include <stdio.h>

#include <lookpath2/Display/Printer.h>

#define USE_UNICODE 1

struct UseChars {
    const char *const last;
    const char *const rest;
};

static const struct UseChars tree_chars = {
#ifdef USE_UNICODE
    "└─ ", "├─ ",
#else
    "+- ", "|- ",
#endif
};

void
nop_label_printer(
    FILE *stream,
    const char *label
) {
    (void) stream;
    (void) label;
}

void
nop_item_printer(
    FILE *stream,
    const char *label,
    const char *item
) {
    (void) stream;
    (void) label;
    (void) item;
}

void
path_list_item_printer(
    FILE *stream,
    const char *label,
    const char *item
) {
    fprintf(stream, "%s/%s\n", label, item);
}

void
tree_label_printer(
    FILE *stream,
    const char *label
) {
    fprintf(stream, "%s:\n", label);
}

void
tree_item_printer(
    FILE *stream,
    const char *label,
    const char *item
) {
    (void) label;
    fprintf(stream, "%s%s\n", tree_chars.rest, item);
}

void
tree_last_item_printer(
    FILE *stream,
    const char *label,
    const char *item
) {
    (void) label;
    fprintf(stream, "%s%s\n", tree_chars.last, item);
}
