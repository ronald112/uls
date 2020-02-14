#include "uls.h"

static char *get_info(t_dir_data *dir, t_catalog *cat) {
    char *result = mx_get_permissions(dir->buff_stat->st_mode, dir->path);

    mx_add_xatr(dir->path, &result);
    mx_add_links(dir->buff_stat->st_nlink, cat, &result);
    mx_add_pwd(dir, cat, &result);
    mx_add_grp(dir, cat, &result);
    mx_add_filesize(dir->buff_stat->st_size, cat, &result);
    mx_add_lastchange_time(dir->buff_stat->st_mtimespec.tv_sec, &result);
    result = mx_addstr(result, dir->name);
    mx_add_hardlink(dir->path, &result);
    return result;
}

void mx_print_lflag(t_catalog *cat, t_flag flags) {
    char *temp = NULL;

    for (t_dir_data *dir = cat->dir; dir; dir = dir->next) {
        if (flags.is_a == false && dir->name[0] != '.') {
            temp = get_info(dir, cat);
            mx_printstr(temp);
            mx_strdel(&temp);
            mx_printstr("\n");
        }
        else if (flags.is_a == true) {
            temp = get_info(dir, cat);
            mx_printstr(temp);
            mx_strdel(&temp);
            mx_printstr("\n");
        }
    }
}
