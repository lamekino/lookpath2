#include <stdio.h>

#include <lookpath2/App/Usage.h>
#include <lookpath2/App/FlagStrings.h>

#define TABS(k) (2 * (k)), ' '

void
usage(
    FILE *stream,
    const char *progname
) {
    enum FlagStrings fstr;

    fprintf(
        stream,
        "%s [PATTERN]\n"
        "%*csearches the directories in $PATH for [PATTERN]\n",
        progname,
        TABS(1)
    );

    for (fstr = 0; fstr < FLAG_STRINGS_COUNT; fstr++) {
        const char *desc = get_flag_description(fstr);
        const char *sflag = get_flag_short(fstr);

        fprintf(
            stream,
            "%*c%-8s: %s %s\n",
            TABS(2),
            sflag,
            desc,
            is_default_flag(fstr)? "(default)" : ""
        );
    }
}
