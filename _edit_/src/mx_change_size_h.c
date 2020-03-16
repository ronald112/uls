#include "uls.h"

static char *add_megabytes(long long nmb) {
    char *temp_res = NULL;
    long long check = (nmb / mx_pow(10, mx_get_nmb_digits_int(nmb) - 2));
    char *temp_devide_by_ten = mx_ltoa(check % 10);

    temp_res = mx_ltoa(nmb / mx_pow(10, mx_get_nmb_digits_int(nmb) - 1));
    temp_res = mx_addstr(temp_res, ".");
    temp_res = mx_addstr(temp_res, temp_devide_by_ten);
    temp_res = mx_addstr(temp_res, "M");
    mx_strdel(&temp_devide_by_ten);
    return temp_res;
}

static long long change_remainder(off_t size, long long *nmb, long long div) {
    long long remainder[2] = {0};

    *nmb /= div;
    for (int i = 0; i < 2; ++i)
        remainder[i] = mx_get_remainder(size, div, i + 1);
    if (remainder[1] >= 5)
        remainder[0] += 1;
    if (remainder[0] == 10) {
        *nmb += 1;
        remainder[0] = 0;
    }
    return remainder[0];
}

static char *add_kilobytes(off_t size, long long nmb) {
    char *temp_res = NULL;
    long long remainder = change_remainder(size, &nmb, 1024);

    temp_res = mx_ltoa(nmb);
    if (mx_get_nmb_digits_ll(nmb) == 1) {
        char *temp_str = mx_ltoa(remainder);

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

    for (; nmb_digits > 0; --nmb_digits)
        temp_res = mx_addstr(temp_res, " ");
    temp_res = mx_addstr(temp_res, *result);
    mx_strdel(result);
    return temp_res;
}

char *mx_change_size_h(off_t size) {
    char *result = NULL;
    char *temp_res = NULL;
    long long nmb = size;

    if (nmb > 1048577)
        temp_res = add_megabytes(nmb);
    else if (nmb > 1023)
        temp_res = add_kilobytes(size, nmb);
    else {
        temp_res = mx_ltoa(nmb);
        temp_res = mx_addstr(temp_res, "B");
    }
    temp_res = add_digits(&temp_res);
    result = mx_addstr(result, temp_res);
    mx_strdel(&temp_res);
    return result;
}
