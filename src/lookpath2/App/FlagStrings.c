#include <assert.h>
#include <stdio.h>

#include <stdbool.h>
#include <string.h>

#include <lookpath2/App/FlagStrings.h>
#include <lookpath2/Debug/Assert.h>

const struct FlagInfo gbl_flag_info[FLAG_STRINGS_COUNT] = {
    [FS_DISPLAY_TREE] = {
        .sflag = "-t",
        .desc = "prints the matched filenames as trees",
        .is_default = true
    },
    [FS_DISPLAY_PATHS] = {
        .sflag = "-p",
        .desc = "lists the matched filenames as full paths"
    },
    [FS_SEARCH_LOOK] = {
        .sflag = "-l",
        .desc = "search by the substring prefix of filenames",
        .is_default = true
    },
    [FS_SEARCH_REGEX] = {
        .sflag = "-E",
        .desc = "enables searching by regex"
    },
    [FS_SHOW_HELP] = {
        .sflag = "-h",
        .desc = "show this help"
    }
};

#define NO_MISSING_FLAG_INFO_HELPER(xm) \
    (gbl_flag_info[xm].sflag[0]) && \
    (gbl_flag_info[xm].desc[0]) &&

#define NO_MISSING_FLAG_INFO(xm) \
    (xm(NO_MISSING_FLAG_INFO_HELPER) /*&&*/ 1)

static inline const struct FlagInfo *
get_flag_info(
    enum FlagStrings fstr
) {
    ASSERT(
        (0 <= fstr && fstr < FLAG_STRINGS_COUNT) ||
        !(__FILE__ "invalid fstr")
    );

    ASSERT(
        NO_MISSING_FLAG_INFO(FS_XMARCO) ||
        !(__FILE__ "missing flag info")
    );

    return &gbl_flag_info[fstr];
}

inline bool
is_flag(
    const char *argp,
    enum FlagStrings fstr
) {
    if (0 <= fstr && fstr < FLAG_STRINGS_COUNT) {
        const struct FlagInfo *sf = get_flag_info(fstr);

        if (strncmp(argp, sf->sflag, sizeof(sf->sflag)) == 0) {
            return true;
        }
    }

    return false;
}

inline bool
is_default_flag(
    enum FlagStrings fstr
) {
    return get_flag_info(fstr)->is_default;
}

inline const char *
get_flag_short(
    enum FlagStrings fstr
) {
    return &get_flag_info(fstr)->sflag[0];
}

inline const char *
get_flag_description(
    enum FlagStrings fstr
) {
    return &get_flag_info(fstr)->desc[0];
}
