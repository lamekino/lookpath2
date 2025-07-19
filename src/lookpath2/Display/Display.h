#pragma once

#include <stdio.h>

#include <lookpath2/LabelStack/LabelStack.h>

typedef void Display(FILE *stream, const struct LabelStack *lstk);

Display display_tree;
Display display_paths;
