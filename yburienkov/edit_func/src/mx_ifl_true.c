#include "uls.h"

static void chk_max_size(long long *ds, long long *ls, nlink_t nls, off_t ods) {
    *ds = *ds > ods ? *ds : ods;
    *ls = *ls > nls ? *ls : nls;
}

static void set_max_size(t_dir_data *list, t_catalog *cat, t_flag flag) {
    if (flag.is_a == false && list->name[0] != '.')
        chk_max_size(&cat->max_size_ofdir, &cat->max_size_oflink,
        list->buff_stat->st_nlink, list->buff_stat->st_size);
    else if (flag.is_a == true)
        chk_max_size(&cat->max_size_ofdir, &cat->max_size_oflink,
        list->buff_stat->st_nlink, list->buff_stat->st_size);
}

void mx_ladd_to_tdir(t_dir_data *list, t_catalog *cat, t_flag flag) {
    list->buff_stat = (struct stat *)malloc(sizeof(struct stat));
    lstat(list->path, list->buff_stat);
    cat->size_of_block += list->buff_stat->st_blocks;
    set_max_size(list, cat, flag);

}
