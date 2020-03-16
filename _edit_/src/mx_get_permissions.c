#include "uls.h"

static char *add_ch_symb_link(mode_t mode) {
    switch (mode & S_IFMT) {
        case S_IFIFO:
            return "p";
        case S_IFCHR:
            return "c";
        case S_IFDIR:
            return "d";
        case S_IFBLK:
            return "b";
        case S_IFREG:
            return "-";
        case S_IFLNK:
            return "l";
        case S_IFSOCK:
            return "s";
        default:
            return "?";
    }
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
