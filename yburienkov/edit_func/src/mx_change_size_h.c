#include "uls.h"

static char *add_kilobytes(off_t size, long long nmb) {
    long long cpy_digits = 0;
    char *temp_res = NULL;

    nmb /= 1024;
    cpy_digits = mx_get_nmb_digits_ll(nmb);
    temp_res = mx_ltoa(nmb);
    if (cpy_digits == 1) {
        char *temp_str = mx_ltoa((size % 1000) / 100);

        temp_res = mx_addstr(temp_res, ".");
        temp_res = mx_addstr(temp_res, temp_str);
        mx_strdel(&temp_str);
    }
    temp_res = mx_addstr(temp_res, "K");
    return temp_res;
}

static char *add_digits(char **result) {
    int nmb_digits = 5 - mx_strlen(*result);
    char *temp_res = NULL;

    for (; nmb_digits != 0; nmb_digits -= 1)
        temp_res = mx_addstr(temp_res, " ");
    temp_res = mx_addstr(temp_res, *result);
    mx_strdel(result);
    return temp_res;
}

char *mx_change_size_h(off_t size) {
    char *result = NULL;
    char *temp_res = NULL;
    long long nmb = size;

    if (nmb > 1023 && nmb < 1048577) {
        temp_res = add_kilobytes(size, nmb);
    }
    else if (nmb > 1048576) {
        nmb /= 1048576;
        temp_res = mx_ltoa(nmb);
        temp_res = mx_addstr(temp_res, "M");
    }
    else {
        temp_res = mx_ltoa(nmb);
        temp_res = mx_addstr(temp_res, "B");
    }
    temp_res = add_digits(&temp_res);
    result = mx_addstr(result, temp_res);
    mx_strdel(&temp_res);
    return result;
}
