#pragma once

#include <lookpath2/LabelStack/LabelStack.h>

struct Pattern;

int
look_path(
    struct LabelStack *result,
    const struct Pattern *pattern,
    const char *path_var
);
