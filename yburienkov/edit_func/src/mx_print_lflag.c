#include "uls.h"

void mx_print_lflag(t_catalog *catalog, t_flag flags) {
    for (t_dir_data *dir = catalog->dir ? catalog->dir : catalog->dir_data;
    dir; dir = dir->next) {
        if (flags.is_a == false && dir->name[0] != '.') {
            printf("%s\n", dir->path);
        }
        else if (flags.is_a == true) {
            printf("%s\n", dir->path);
        }
    }
}
