#include "uls.h"

static char *add_ch_symb_link(mode_t mode) {
    mode_t mode_cur = mode & S_IFMT;

    if (mode_cur == S_IFIFO)
        return "p";
    else if (mode_cur == S_IFCHR)
        return "c";
    else if (mode_cur == S_IFDIR)
        return "d";
    else if (mode_cur == S_IFBLK)
        return "b";
    else if (mode_cur == S_IFREG)
        return "-";
    else if (mode_cur == S_IFLNK)
        return "l";
    else if (mode_cur == S_IFSOCK)
        return "s";
    else
        return "?";
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

char *mx_get_permissions(mode_t mode) {
    char *result = NULL;

    result = mx_addstr(result, add_ch_symb_link(mode));
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
