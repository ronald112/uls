#include "uls.h"

static void add_ch_symb_link(char **result, char *path, mode_t mode) {
    char buff[256] = "\0";

    readlink(path, buff, 256);
    if (mode & S_IFDIR)
        *result = mx_addstr(*result, "d");
    else if ((mode & S_IFLNK) && mx_strlen(buff))
        *result = mx_addstr(*result, "l");
    else if (mode & S_IFCHR)
        *result = mx_addstr(*result, "c");
    else if (mode & S_IFBLK)
        *result = mx_addstr(*result, "b");
    //else if (mode & S_IFSOCK)
    //    *result = mx_addstr(*result, "s");
    else if (mode & S_IFIFO)
        *result = mx_addstr(*result, "p");
    else
        *result = mx_addstr(*result, "-");
}

static void add_last_bit_char(char **result, mode_t mode) {
    if (mode & S_IXOTH) {
        if ((mode & S_ISUID) || (mode & S_ISGID))
            *result = mx_addstr(*result, "s");
        else if (mode & S_ISVTX)
            *result = mx_addstr(*result, "t");
        else
            *result = mx_addstr(*result, "x");
    }
    else if ((mode & S_ISUID) || (mode & S_ISGID))
        *result = mx_addstr(*result, "S");
    else if (mode & S_ISVTX)
        *result = mx_addstr(*result, "T");
    else
        *result = mx_addstr(*result, "-");
}

char *mx_get_permissions(mode_t mode, char *path) {
    char *result = NULL;
    
    add_ch_symb_link(&result, path, mode);
    result = mx_addstr(result, (mode & S_IRUSR) ? "r" : "-");
    result = mx_addstr(result, (mode & S_IWUSR) ? "w" : "-");
    result = mx_addstr(result, (mode & S_IXUSR) ? "x" : "-");
    result = mx_addstr(result, (mode & S_IRGRP) ? "r" : "-");
    result = mx_addstr(result, (mode & S_IWGRP) ? "w" : "-");
    result = mx_addstr(result, (mode & S_IXGRP) ? "x" : "-");
    result = mx_addstr(result, (mode & S_IROTH) ? "r" : "-");
    result = mx_addstr(result, (mode & S_IWOTH) ? "w" : "-");
    add_last_bit_char(&result, mode);
    return result;
}
