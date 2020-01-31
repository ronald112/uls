#include "uls.h"

static char *get_permissions(mode_t mode) {
    char *result = NULL;

    result = mx_addstr(result, (mode & S_IFDIR) ? "d" : "-");
    result = mx_addstr(result, (mode & S_IRUSR) ? "r" : "-");
    result = mx_addstr(result, (mode & S_IWUSR) ? "w" : "-");
    result = mx_addstr(result, (mode & S_IXUSR) ? "x" : "-");
    result = mx_addstr(result, (mode & S_IRGRP) ? "r" : "-");
    result = mx_addstr(result, (mode & S_IWGRP) ? "w" : "-");
    result = mx_addstr(result, (mode & S_IXGRP) ? "x" : "-");
    result = mx_addstr(result, (mode & S_IROTH) ? "r" : "-");
    result = mx_addstr(result, (mode & S_IWOTH) ? "w" : "-");
    result = mx_addstr(result, (mode & S_IXOTH) ? "x" : "-");
    return result;
}

static char *chk_xatr(char *path) {
    ssize_t xattr = listxattr(path, NULL, 0, XATTR_NOFOLLOW);
    acl_t acl = acl_get_file(path, ACL_TYPE_EXTENDED);
    char *result = NULL;

    if (xattr < 0)
        xattr = 0;
    else if (xattr > 0)
        result = mx_addstr(result, "@");
    else if (acl != NULL)
        result = mx_addstr(result, "+");
    else
        result = mx_addstr(result, " ");
    acl_free(acl);
    acl = NULL;
    return result;
}

static char *get_info(t_dir_data *dir) {
    char *result = get_permissions(dir->buff_stat->st_mode);
    char *xatr_res = chk_xatr(dir->path);
    
    result = mx_addstr(result, xatr_res);
    mx_strdel(&xatr_res);
    return result;
}

void mx_print_lflag(t_catalog *catalog, t_flag flags) {
    char *temp = NULL;

    mx_printstr("total ");
    mx_printull(catalog->size_of_block);
    mx_printstr("\n");
    for (t_dir_data *dir = catalog->dir ? catalog->dir : catalog->dir_data;
    dir; dir = dir->next) {
        if (flags.is_a == false && dir->name[0] != '.') {
            temp = get_info(dir);
            mx_printstr(temp);
            mx_strdel(&temp);
            mx_printstr("\n");
        }
        else if (flags.is_a == true) {
            temp = get_info(dir);
            mx_printstr(temp);
            mx_strdel(&temp);
            mx_printstr("\n");
        }
    }
}
