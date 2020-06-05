#include "uls.h"

static inline void check_write(t_info *info, char flag) {
    if (flag == 'l')
        info->write = mx_write_l;
    else if (flag == '1')
        info->write = mx_write_1;
    else if (flag == 'C' && info->write != mx_write_m)
        info->write = mx_write_C;
}

static inline void check_other(t_info *info, char flag) {
    if (flag == 'R' && info->filedir == 0)
        info->recursion = mx_recursion;
    else {
        info->recursion = mx_uls;
        info->filedir = 1;
    }
}

void mx_check_flags(t_info *info, t_vector *flags) {
    for (size_t i = 0; i < flags->size; ++i) {
        char flg = flags->arr[i];

        if ((flg == 'a' || flg == 'A') && info->read != mx_full)
            info->read = flg == 'A' ? mx_hidden : mx_full;
        else if (MX_WRITE(flg))
            check_write(info, flg);
        else if (flg == 'c')
            info->time_type = change;
        else if (flg == 'f' && info->cmp != NULL) {
            info->cmp = NULL;
            info->read = mx_full;
        }
        else if (MX_OTHER(flg))
            check_other(info, flg);
    }
}
