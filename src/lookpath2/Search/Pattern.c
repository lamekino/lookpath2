#include <string.h>
#include <regex.h>

#include <lookpath2/Search/Pattern.h>
#include <lookpath2/Search/SearchMethod.h>

/* bad idea :) */
static regex_t gbl_regex = {0};

int
pattern_init(
    struct Pattern *pattern,
    const char *pattern_str
) {
    struct Pattern init = (struct Pattern) {
        .str = pattern_str,
        .str_length = !pattern_str? 0 : strlen(pattern_str),
        .find = &sm_look
    };

    *pattern = init;
    return 0;
}

void
pattern_destory(
    struct Pattern *pattern
) {
    if (pattern->str_regex) {
        regfree(pattern->str_regex);
    }
}

void
use_look_search_method(
    struct Pattern *pattern
) {
    pattern->find = &sm_look;
}

void
use_regex_search_method(
    struct Pattern *pattern
) {
    pattern->find = &sm_regex;
    pattern->str_regex = &gbl_regex;
}
