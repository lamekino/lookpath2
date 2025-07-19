#pragma once

#include <stdio.h>

#include <lookpath2/Display/Display.h>

struct Settings {
    FILE *put_usage;
    Display *use_display;
};

typedef void SettingsModifier(struct Settings *settings);

int
settings_init(
    struct Settings *settings
);

SettingsModifier set_display_tree;

SettingsModifier set_display_path_list;

SettingsModifier set_show_usage;
