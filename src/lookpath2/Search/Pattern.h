#pragma once

#include <stddef.h>
#include <stdbool.h>
#include <regex.h>

#include <lookpath2/Search/SearchMethod.h>

struct Pattern {
    const char *str;
    size_t str_length;

    regex_t *str_regex;

    SearchMethod *find;
};

typedef void PatternModifier(struct Pattern *pattern);

int
pattern_init(
    struct Pattern *pattern,
    const char *pattern_str
);

void
pattern_destory(
    struct Pattern *pattern
);

PatternModifier use_look_search_method;

PatternModifier use_regex_search_method;
