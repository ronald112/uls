#include "uls.h"

void mx_add_filesize(off_t size, t_catalog *cat, char **result, t_flag flag) {
    char *temp = mx_ltoa(size);
    long long cnt = 0;
    char *str_h = mx_change_size_h(size);

    if (size == 0)
        cnt = 1;
    for (; size != 0; size /= 10, cnt++);
    cnt = cat->max_size_ofdir - cnt;
    if (cnt < 0)
        cnt = cat->lng_max_minor + cat->lng_max_major + 2;
    
    if (flag.is_h == true
    && mx_strcmp("dev", &(cat->c_name[mx_strlen(cat->c_name) - 3])) != 0)
        *result = mx_addstr(*result, str_h);
    else {
        for (; cnt != 0; cnt--)
            *result = mx_addstr(*result, " ");
        *result = mx_addstr(*result, temp);
    }
    mx_strdel(&str_h);
    mx_strdel(&temp);
}
