#include "uls.h"

void mx_add_filesize(off_t size, t_catalog *cat, char **result) {
    char *temp = mx_itoa(size);
    char *num = mx_strjoin(" ", temp);
    long long cnt = 0;

    for (; size != 0; size /= 10, cnt++);
    cnt = cat->max_size_ofdir - cnt;
    for (; cnt != 0; cnt--)
        *result = mx_addstr(*result, " ");
    *result = mx_addstr(*result, num);
    *result = mx_addstr(*result, " ");

    mx_strdel(&num);
    mx_strdel(&temp);
}
