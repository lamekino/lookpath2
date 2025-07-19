#include <stdbool.h>

#include <lookpath2/Search/SearchMethod.h>
#include <lookpath2/Search/Pattern.h>

bool
sm_look(
    const struct Pattern *pattern,
    const char *text
) {
    const char *a = pattern->str;
    const char *b = text;

    while (*a && *b) {
        if (*a++ != *b++) {
            return false;
        }
    }

    return *a == '\0';
}

bool
sm_regex(
    const struct Pattern *pattern,
    const char *text
) {
    return regexec(pattern->str_regex, text, 0, NULL, 0) == 0;
}
