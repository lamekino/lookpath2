#pragma once

#include <stdio.h>

typedef void LabelPrinter(FILE *stream, const char *label);
typedef void ItemPrinter(FILE *stream, const char *label, const char *item);

LabelPrinter nop_label_printer;
ItemPrinter nop_item_printer;

ItemPrinter path_list_item_printer;

LabelPrinter tree_label_printer;
ItemPrinter tree_item_printer;
ItemPrinter tree_last_item_printer;
