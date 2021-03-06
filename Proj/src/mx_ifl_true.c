#include "uls.h"

// check and save max blok size
static void chk_max_size(long long *ds, long long *ls, nlink_t nls, off_t ods) {
    *ds = *ds > ods ? *ds : ods;
    *ls = *ls > nls ? *ls : nls;
}

static void chk_max_size_name(t_catalog *cat, t_dir_data *list) {
    struct passwd *pwd = getpwuid(list->buff_stat->st_uid);
    struct group *grp = getgrgid(list->buff_stat->st_gid);

    if (grp != NULL)
        list->min_lnght_grpdir = mx_strlen(grp->gr_name);
    else {
        char *temp = mx_itoa(list->buff_stat->st_gid);

        list->min_lnght_grpdir = mx_strlen(temp);
        mx_strdel(&temp);
    }
    chk_max_size(&cat->max_size_ofdir, &cat->max_size_oflink,
                 list->buff_stat->st_nlink, list->buff_stat->st_size);
    list->min_lnght_namedir = mx_strlen(pwd->pw_name);
    if (cat->max_lnght_namedir < list->min_lnght_namedir)
        cat->max_lnght_namedir = list->min_lnght_namedir;
    if (cat->max_lnght_grpdir < list->min_lnght_grpdir)
        cat->max_lnght_grpdir = list->min_lnght_grpdir;
}

static void set_max_size(t_dir_data *list, t_catalog *cat, t_flag flag) {
    if (flag.is_a == false && list->name[0] != '.') {
        chk_max_size_name(cat, list);
        mx_add_indens_minor_major(cat, list);
    }
    else if (flag.is_a == true) {
        chk_max_size_name(cat, list);
        mx_add_indens_minor_major(cat, list);
    }
}

static void add_sizedir_to_sizeblock(t_dir_data *list, t_catalog *cat,
                                     t_flag flag) {
    mode_t mode_cur = list->buff_stat->st_mode & S_IFMT;

    if (mode_cur == S_IFIFO)
        cat->is_char_block = true;
    else if (mode_cur == S_IFBLK)
        cat->is_char_block = true;
    if (flag.is_a == false && list->name[0] != '.')
        cat->size_of_block += list->buff_stat->st_blocks;
    else if (flag.is_a == true)
        cat->size_of_block += list->buff_stat->st_blocks;
}

void mx_ladd_to_tdir(t_dir_data *list, t_catalog *cat, t_flag flag) {
    list->buff_stat = (struct stat *)malloc(sizeof(struct stat));
    lstat(list->path, list->buff_stat);
    add_sizedir_to_sizeblock(list, cat, flag);
    set_max_size(list, cat, flag);
}
