#include "uls.h"

void mx_add_filesize(off_t size, t_catalog *cat, char **result, bool flag) {
    char *temp = mx_ltoa(size);
    long long cnt = cat->max_size_ofdir - mx_get_nmb_digits_int(size);
    char *str_h = mx_change_size_h(size);

    if (cat->is_char_block == true) {
        cnt = cat->lng_max_minor + cat->lng_max_major + 3
              - mx_get_nmb_digits_int(size);
    }
    if (flag == true && cat->is_char_block == false)
        *result = mx_addstr(*result, str_h);
    else {
        for (; cnt > 0; cnt--)
            *result = mx_addstr(*result, " ");
        *result = mx_addstr(*result, temp);
    }
    mx_strdel(&str_h);
    mx_strdel(&temp);
}
