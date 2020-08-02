#include "uls.h"

void mx_print_R(t_main *info, t_catalog *head) {
    static int counter = 0;

    mx_count_line_for_print_R(info, head);
    if (counter != 0) {
        mx_printchar('\n');
        mx_printstr(head->c_name);
        mx_printstr(":\n");
    }
    if (info->flag.is_l == true)
        mx_start_lprint(head, info);
    else if (!info->flag.is_tofile)
        info->flag.is_1 ? mx_print_1(head, info)
        : mx_print_cat(head, info);
    else
        info->flag.is_C ? mx_print_cat(head, info)
        : mx_print_1(head, info);
    counter++;
}
