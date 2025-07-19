#pragma once

#include <stdbool.h>
#include <stddef.h>

#define XM_ENUMERATE(xm) \
    xm,

#define FS_XMARCO(X) \
    X(FS_DISPLAY_PATHS) \
    X(FS_DISPLAY_TREE) \
    X(FS_SEARCH_LOOK) \
    X(FS_SEARCH_REGEX) \
    X(FS_SHOW_HELP)


enum FlagStrings {
    FS_XMARCO(XM_ENUMERATE)
    FLAG_STRINGS_COUNT
};

#define MAX_SFLAG_LENGTH 16
#define MAX_DESC_LENGTH 128

struct FlagInfo {
    const char sflag[MAX_SFLAG_LENGTH];
    const char desc[MAX_DESC_LENGTH];
    bool is_default;
};

bool
is_flag(
    const char *argp,
    enum FlagStrings fs
);

bool
is_default_flag(
    enum FlagStrings fstr
);


const char *
get_flag_short(
    enum FlagStrings fstr
);

const char *
get_flag_description(
    enum FlagStrings fstr
);
