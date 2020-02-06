#include "uls.h"

void mx_add_lastchange_time(const time_t time, char **result) {
    char *tmp_chr_time = ctime(&time);
    char *chr_time = mx_strnew(13);
    int j = 0;

    for (int i = 3; j <= 12; i++, j++)
        chr_time[j] = tmp_chr_time[i];
    *result = mx_addstr(*result, chr_time);
    *result = mx_addstr(*result, " ");
    mx_strdel(&chr_time);
}
