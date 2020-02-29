#include "uls.h"

int mx_get_nmb_digits(int nmb) {
    long long tmp_ls = nmb;

    if (nmb == 0)
        return 1;
    for (nmb = 0; tmp_ls != 0; tmp_ls /= 10, nmb++);
    return nmb;
}

char *mx_get_hex_view(int nmb) {
    char *nmb_char = mx_nbr_to_hex(nmb & 0xffffff);
    int nmb_digits = 0;
    char *result = mx_strnew(10);

    mx_memset(result, '0', 10);
    result[1] = 'x';
    for (int i = 10 - mx_strlen(nmb_char); i < 10; ++nmb_digits, ++i) {
        result[i] = nmb_char[nmb_digits];
    }
    mx_strdel(&nmb_char);
    return result;
}

void mx_add_indens_minor_major(t_catalog *cat, t_dir_data *list) {
    if (cat->lng_max_minor
    < mx_get_nmb_digits(MX_MINOR(list->buff_stat->st_rdev))
    && MX_MINOR(list->buff_stat->st_rdev) < 255) {
        cat->lng_max_minor =
        mx_get_nmb_digits(MX_MINOR(list->buff_stat->st_rdev));
    }
    if (cat->lng_max_major
    < mx_get_nmb_digits(MX_MAJOR(list->buff_stat->st_dev))) {
        cat->lng_max_major =
        mx_get_nmb_digits(MX_MAJOR(list->buff_stat->st_rdev));
    }
}