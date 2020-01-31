#include "uls.h"

static char *get_permissions(mode_t mode) {    
    char *result = mx_strnew(12);

    result[0] = (mode & S_IFDIR) ? 'd' : '-';    
    result[1] = (mode & S_IRUSR) ? 'r' : '-';
    result[2] = (mode & S_IWUSR) ? 'w' : '-';
    result[3] = (mode & S_IXUSR) ? 'x' : '-';
    result[4] = (mode & S_IRGRP) ? 'r' : '-';
    result[5] = (mode & S_IWGRP) ? 'w' : '-';
    result[6] = (mode & S_IXGRP) ? 'x' : '-';
    result[7] = (mode & S_IROTH) ? 'r' : '-';
    result[8] = (mode & S_IWOTH) ? 'w' : '-';
    result[9] = (mode & S_IXOTH) ? 'x' : '-';
    result[10] = ' ';
    result[11] = ' ';
    return result;
}

static char *get_info(t_dir_data *dir) {

    char *result = get_permissions(dir->buff_stat->st_mode);
    
    
    
    return result;
}

void mx_print_lflag(t_catalog *catalog, t_flag flags) {
    char *temp = NULL;

    mx_printstr("total ");
    mx_printint(catalog->size_of_block);
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
