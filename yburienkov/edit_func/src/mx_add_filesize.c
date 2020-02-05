#include "uls.h"

void mx_add_filesize(off_t size, t_catalog *cat, char **result) {
    char *temp = mx_itoa(size);
    long long cnt = 0;
    // *result = mx_addstr(*result, "  ");
    for (; size != 0; size /= 10, cnt++);
    cnt = cat->max_size_ofdir - cnt;
    // printf("%lli %lli\n", cnt, cat->max_size_ofdir);
    for (; cnt != 0; cnt--)
        *result = mx_addstr(*result, " ");
    *result = mx_addstr(*result, temp);
    mx_strdel(&temp);
}
