#include "uls.h"

void mx_swap_dir(t_dir_data *a, t_dir_data *b) {
    struct dirent *tmp_data = a->data;
    struct stat *tmp_buff = a->buff_stat;

    a->data = b->data;
    b->data = tmp_data;
    a->buff_stat = b->buff_stat;
    b->buff_stat = tmp_buff;
    mx_swap_char(a->name, b->name);
    mx_swap_char(a->path, b->path);
    mx_swap_ll((long long *)&a->min_lnght_namedir, (long long *)&b->min_lnght_namedir);
    mx_swap_ll((long long *)&a->min_lnght_grpdir, (long long *)&b->min_lnght_grpdir);
}

void mx_sort_dir_list(t_dir_data *start, t_flag flag) {
    int swapped = 1;
    t_dir_data *ptr1;
    t_dir_data *lptr = NULL;

    if (start == NULL || flag.is_f)
        return;
    while (swapped) {
        swapped = 0;
        ptr1 = start;
        while (ptr1->next != lptr) {
            if (mx_strcmp(ptr1->name, ptr1->next->name) > 0) {
                mx_swap_dir(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
}
