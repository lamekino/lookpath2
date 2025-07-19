#include <stdio.h>
#include <stdlib.h>

#include <lookpath2/App/ProcessArguments.h>
#include <lookpath2/App/LookPath.h>
#include <lookpath2/App/Usage.h>
#include <lookpath2/Display/Display.h>
#include <lookpath2/LabelStack/LabelStack.h>
#include <lookpath2/Search/Pattern.h>
#include <lookpath2/Settings/Settings.h>

int
main(
    int argc,
    char *argv[]
) {
    const char *env_path = getenv("PATH");

    struct Settings settings = {0};
    struct Pattern pattern = {0};
    struct LabelStack matches = {0};

    if (!env_path || !env_path[0]) {
        fprintf(stderr, "$PATH isn't defined!!!\n");
        settings.put_usage = stderr;
        goto FAIL;
    }

    if (
        settings_init(&settings) < 0
        || pattern_init(&pattern, NULL) < 0
        || lstk_init(&matches) < 0
    ) {
        fprintf(stderr, "failed to initialize\n");
        goto FAIL;
    }

    if (process_arguments(&pattern, &settings, argc, argv) < 0) {
        goto FAIL;
    }

    if (look_path(&matches, &pattern, env_path) < 0) {
        fprintf(stderr, "could not finish searching paths\n");
        goto FAIL;
    }

    settings.use_display(stdout, &matches);

    lstk_destory(&matches);
    pattern_destory(&pattern);
    return EXIT_SUCCESS;

FAIL:
    if (settings.put_usage) {
        usage(settings.put_usage, argv[0]);
    }

    lstk_destory(&matches);
    pattern_destory(&pattern);
    return settings.put_usage == stdout? EXIT_SUCCESS : EXIT_FAILURE;
}
