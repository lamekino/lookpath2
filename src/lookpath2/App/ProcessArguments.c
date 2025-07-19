#include "lookpath2/Search/SearchMethod.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>

#include <lookpath2/App/FlagStrings.h>
#include <lookpath2/App/ProcessArguments.h>
#include <lookpath2/Debug/Assert.h>
#include <lookpath2/Search/Pattern.h>
#include <lookpath2/Settings/Settings.h>

SettingsModifier *const settings_callback[FLAG_STRINGS_COUNT] = {
    [FS_DISPLAY_TREE] = &set_display_tree,
    [FS_DISPLAY_PATHS] = &set_display_path_list,
    [FS_SHOW_HELP] = &set_show_usage
};

PatternModifier *const pattern_callback[FLAG_STRINGS_COUNT] = {
    [FS_SEARCH_LOOK] = &use_look_search_method,
    [FS_SEARCH_REGEX] = &use_regex_search_method
};

enum ProcessArgsErr {
    ERR_NONE_GIVEN = INT_MIN,
    ERR_INVALID_FLAG,
    ERR_PATTERN_MISSING,
    ERR_PATTREN_FAIL,
    ERR_SETTING_FAIL,
    ERR_REGEX_FAIL,

    ERR_NONE = 0
};

enum ProcessArgsErr
process_arguments_err(
    char ***argp,
    struct Pattern *pattern,
    struct Settings *settings,
    int argc,
    char *argv[]
) {
    if (argc <= 1) {
        return ERR_NONE_GIVEN;
    }

    for (*argp = &argv[1]; **argp; (*argp)++) {
        const char *arg = **argp;

        bool has_flag = false;
        SettingsModifier *modify_settings = NULL;
        PatternModifier *modify_pattern = NULL;

        enum FlagStrings fstr;

        for (fstr = 0; fstr < FLAG_STRINGS_COUNT && !has_flag; fstr++) {
            has_flag = is_flag(arg, fstr);
            modify_settings = settings_callback[fstr];
            modify_pattern = pattern_callback[fstr];
        }

        if (has_flag && modify_settings) {
            modify_settings(settings);
        }

        if (has_flag && modify_pattern) {
            modify_pattern(pattern);
        }

        if (has_flag) {
            continue;
        }

        if (arg[0] == '-') {
            return ERR_INVALID_FLAG;
        }

        if (pattern->str == NULL) {
            pattern->str = arg;
        }
    }

    if (pattern->str == NULL) {
        return ERR_PATTERN_MISSING;
    }

    if (pattern->str_regex) {
        if (regcomp(pattern->str_regex, pattern->str, REG_EXTENDED) != 0) {
            return ERR_REGEX_FAIL;
        }
    }

    return ERR_NONE;
}

int
process_arguments(
    struct Pattern *pattern,
    struct Settings *settings,
    int argc,
    char *argv[]
) {
    int rv = -1;
    char **argp = NULL;

    enum ProcessArgsErr err = process_arguments_err(
        &argp,
        pattern,
        settings,
        argc,
        argv
    );

    const char *lastarg = argp? *argp : argv[argc - 1];

    if (settings->put_usage) {
        return rv;
    }

    switch (err) {
    case ERR_NONE:
        rv = 0;
        break;
    case ERR_NONE_GIVEN:
        fprintf(stderr, "%s requires at least one argument.\n", argv[0]);
        settings->put_usage = stderr;
        break;
    case ERR_PATTERN_MISSING:
        fprintf(stderr, "no search pattern given.\n");
        settings->put_usage = stderr;
        break;
    case ERR_SETTING_FAIL: /* FIXME: bad error + feature creep */
        fprintf(stderr, "configuration error.\n");
        settings->put_usage = stderr;
        break;
    case ERR_REGEX_FAIL:
        fprintf(stderr, "failed to initialize regex.\n");
        break;
    case ERR_INVALID_FLAG:
        fprintf(stderr, "invalid argument '%s' given.\n", lastarg);
        settings->put_usage = stderr;
        break;
    case ERR_PATTREN_FAIL:
        fprintf(stderr, "failed to initialize pattern.\n");
        break;
    default:
        ASSERT(!(__FILE__ "invalid/unimplemented error code"));
        break;
    }

    return rv;
}
