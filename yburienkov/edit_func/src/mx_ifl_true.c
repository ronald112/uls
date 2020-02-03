#include "uls.h"

static void chk_max_size(long long *ds, long long *ls, nlink_t nls, off_t ods) {
    *ds = *ds > ods ? *ds : ods;
    *ls = *ls > nls ? *ls : nls;
}

static void chk_max_size_name(t_catalog *cat, t_dir_data *list) {
    struct passwd *pwd = NULL;

    chk_max_size(&cat->max_size_ofdir, &cat->max_size_oflink,
    list->buff_stat->st_nlink, list->buff_stat->st_size);
    pwd = getpwuid(list->buff_stat->st_uid);
    list->min_size_ofnamedir = mx_strlen(pwd->pw_name);
    printf("debug %s\n", pwd->pw_name);
    if (cat->max_size_ofnamedir < mx_strlen(pwd->pw_name)) {

        cat->max_size_ofnamedir = list->min_size_ofnamedir;
    }
}

static void set_max_size(t_dir_data *list, t_catalog *cat, t_flag flag) {
    if (flag.is_a == false && list->name[0] != '.')
        chk_max_size_name(cat, list);
    else if (flag.is_a == true)
        chk_max_size_name(cat, list);
}

void mx_ladd_to_tdir(t_dir_data *list, t_catalog *cat, t_flag flag) {
    list->buff_stat = (struct stat *)malloc(sizeof(struct stat));
    lstat(list->path, list->buff_stat);
    cat->size_of_block += list->buff_stat->st_blocks;
    set_max_size(list, cat, flag);
}
