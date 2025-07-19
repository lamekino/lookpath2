#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <dirent.h>
#include <limits.h>

#include <lookpath2/App/LookPath.h>
#include <lookpath2/Search/Pattern.h>
#include <lookpath2/LabelStack/LabelStack.h>
#include <lookpath2/LabelStack/Label.h>

static int
look_directory(
    struct LabelStack *lstk,
    const struct Pattern *pattern,
    const char *path_name
) {
    struct dirent *entry = NULL;
    int label_count = 0;
    DIR *dir = opendir(path_name);

    if (!dir) {
        return -errno;
    }

    while ((entry = readdir(dir))) {
        const char *entry_name = entry->d_name;
        const size_t entry_length = strnlen(entry_name, FILENAME_MAX);

        if (entry_name[0] == '.') {
            continue;
        }

        if (!pattern->find(pattern, entry_name)) {
            continue;
        }

        if (!lstk_push_item(lstk, entry_name)) {
            closedir(dir);
            return -ENOMEM;
        }

        label_count++;
    }

    closedir(dir);
    return label_count;
}

int
look_path(
    struct LabelStack *result,
    const struct Pattern *pattern,
    const char *path_var
) {
    char dirname_buf[PATH_MAX];
    int fail_count = 0;
    size_t path_cursor = 0;

    while (path_var[path_cursor]) {
        const char *path_cur = &path_var[path_cursor];
        const size_t dirname_len = strcspn(path_cur, ":");
        const size_t label_start = result->items_count;

        int label_matches = 0;

        struct LabelBuilder dirlabel = {
            .buffer = &dirname_buf[0],
            .buffer_length = sizeof(dirname_buf)
        };

        if (lb_add_filepath(&dirlabel, path_cur, dirname_len) < 0) {
            fail_count += 1;
            goto INVALID_DIRNAME;
        }

        label_matches = look_directory(result, pattern, dirlabel.buffer);
        if (label_matches < 1) {
            fail_count += 1;
            goto INVALID_DIRNAME;
        }

        if (!lstk_push_label(result, &dirlabel, label_start, label_matches)) {
            return -ENOMEM;
        }

INVALID_DIRNAME:
        path_cursor += dirname_len;
        path_cursor += path_var[path_cursor] != '\0';
    }

    return fail_count;
}
