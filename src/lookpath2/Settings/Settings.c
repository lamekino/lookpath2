#include <lookpath2/Settings/Settings.h>
#include <lookpath2/App/Usage.h>
#include <lookpath2/Display/Display.h>

int
settings_init(
    struct Settings *settings
) {
    struct Settings init = (struct Settings) {
        .use_display = &display_tree
    };

    *settings = init;
    return 0;
}

void
set_display_tree(
    struct Settings *settings
) {
    settings->use_display = display_tree;
}

void
set_display_path_list(
    struct Settings *settings
) {
    settings->use_display = display_paths;
}

void
set_show_usage(
    struct Settings *settings
) {
    settings->put_usage = stdout;
}
