#include "uls.h"

void mx_add_filesize(off_t size, t_catalog *cat, char **result, bool flag) {
    char *temp = mx_ltoa(size);
    long long cnt = 0;
    char *str_h = mx_change_size_h(size);

    // printf("size %lld\n", size);
    // if (size == 0)
    //     cnt = 1;
    // else {
        for (; size > 0; size /= 10, cnt++);
        cnt = cat->max_size_ofdir - cnt;
    // }
    // printf("debug1 %lld\n", cnt);
    if (cat->is_char_block == false && cnt == 0) {
        cnt = cat->lng_max_minor + cat->lng_max_major + 2;
    }
    if (flag == true)
        *result = mx_addstr(*result, str_h);
    else {
        for (; cnt > 0; cnt--)
            *result = mx_addstr(*result, " ");
        *result = mx_addstr(*result, temp);
    }
    mx_strdel(&str_h);
    mx_strdel(&temp);
}
