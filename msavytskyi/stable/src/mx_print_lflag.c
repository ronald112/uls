#include "uls.h"

static char *get_info(t_dir_data *dir, t_catalog *cat, t_flag flag) {
    char *result = mx_get_permissions(dir->buff_stat->st_mode);

    mx_add_xatr(dir->path, &result);
    mx_add_links(dir->buff_stat->st_nlink, cat, &result);
    mx_add_pwd(dir, cat, &result);
    mx_add_grp(dir, cat, &result);
    if (result[0] == 'c' || result[0] == 'b')
        mx_add_minor_major(&result, dir->buff_stat->st_rdev, cat);
    else
        mx_add_filesize(dir->buff_stat->st_size, cat, &result, flag.is_h);
    mx_add_lastchange_time(dir->buff_stat->st_mtimespec.tv_sec, &result);
    result = mx_addstr(result, dir->name);
    mx_add_hardlink(dir->path, &result);
    if (flag.is_dog == true)
        mx_print_ifdog(dir->path, &result, cat->max_size_ofdir, flag.is_h);
    return result;
}

static void chc_max_indents_ll(t_catalog *cat) {
    long long tmp_ds = cat->max_size_ofdir;
    long long tmp_ls = cat->max_size_oflink;

    for (cat->max_size_ofdir = 0; tmp_ds != 0;
    tmp_ds /= 10, cat->max_size_ofdir++);
    for (cat->max_size_oflink = 0; tmp_ls != 0;
    tmp_ls /= 10, cat->max_size_oflink++);
}

void mx_print_lflag(t_catalog *cat, t_flag flags) {
    char *temp = NULL;

    chc_max_indents_ll(cat);
    t_dir_data *dir = flags.is_a ? cat->dir : cat->dir_data;
    for (; dir; dir = dir->next) {
        temp = get_info(dir, cat, flags);
        mx_printstr(temp);
        mx_strdel(&temp);
        mx_printstr("\n");
    }
}
