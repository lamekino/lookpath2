#pragma once

#include <lookpath2/Search/Pattern.h>

struct Settings;

int
process_arguments(
    struct Pattern *pattern,
    struct Settings *settings,
    int argc,
    char *argv[]
);
