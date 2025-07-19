#pragma once

#include <stdbool.h>

struct Pattern;

typedef bool SearchMethod(const struct Pattern *pattern, const char *text);

SearchMethod sm_look;

SearchMethod sm_regex;
