#include <stdio.h>

#include <lookpath2/Display/Display.h>
#include <lookpath2/Display/Printer.h>
#include <lookpath2/LabelStack/LabelStack.h>
#include <lookpath2/LabelStack/Label.h>

static void
display_helper(
    FILE *stream,
    const struct LabelStack *lstk,
    LabelPrinter *const for_each_label,
    ItemPrinter *const for_each_item_before_last,
    ItemPrinter *const for_last_item
) {
    size_t i, j;

    for (i = 0; i < lstk->labels_count; i++) {
        const struct Label *label = &lstk->labels[i];
        const size_t label_end = label->idx_start + label->idx_count;

        for_each_label(stream, label->str);

        for (j = label->idx_start; j < label_end - 1; j++) {
            for_each_item_before_last(stream, label->str, lstk->items[j]);
        }

        for_last_item(stream, label->str, lstk->items[j]);
    }
}

#define display_impl(function_name, a_printer, b_printer, c_printer) \
    void \
    function_name( \
        FILE *stream, \
        const struct LabelStack *lstk \
    ) { \
        display_helper(stream, lstk, a_printer, b_printer, c_printer); \
    }

display_impl(
    display_tree,
    tree_label_printer,
    tree_item_printer,
    tree_last_item_printer
)

display_impl(
    display_paths,
    nop_label_printer,
    path_list_item_printer,
    path_list_item_printer
)
