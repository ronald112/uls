#include "uls.h"

static void swap_cat_ifl_true(t_catalog *a, t_catalog *b) {
    mx_swap_ll(&a->size_of_block, &b->size_of_block);
    mx_swap_ll(&a->max_size_ofdir, &b->max_size_ofdir);
    mx_swap_ll(&a->max_size_oflink, &b->max_size_oflink);
    mx_swap_ll((long long *)&a->max_lnght_namedir, (long long *)&b->max_lnght_namedir);
    mx_swap_ll((long long *)&a->max_lnght_grpdir, (long long *)&b->max_lnght_grpdir);
    mx_swap_ll((long long *)&a->lng_max_minor, (long long *)&b->lng_max_minor);
    mx_swap_ll((long long *)&a->lng_max_major, (long long *)&b->lng_max_major);
}

void mx_swap_cat(t_catalog *a, t_flag flag, t_catalog *b) {
    t_dir_data *tmp_data = a->dir;

    a->dir = b->dir;
    b->dir = tmp_data;
    tmp_data = a->dir_data;
    a->dir_data = b->dir_data;
    b->dir_data = tmp_data;
    mx_swap_ll((long long *)&a->am_files, (long long *)&b->am_files);
    mx_swap_ll((long long *)&a->am_data, (long long *)&b->am_data);
    mx_swap_bool(&a->is_dir, &b->is_dir);
    mx_swap_bool(&a->is_char_block, &b->is_char_block);
    mx_swap_char(a->c_name, b->c_name);
    if (flag.is_l == true)
        swap_cat_ifl_true(a, b);
}

void mx_sort_cat_list(t_catalog *start, t_flag flag) {
    int swapped = 1;
    t_catalog *ptr1;
    t_catalog *lptr = NULL;

    if (start == NULL || flag.is_f)
        return;
    while (swapped) {
        swapped = 0;
        ptr1 = start;
        while (ptr1->c_next != lptr) {
            if (mx_strcmp(ptr1->c_name, ptr1->c_next->c_name) > 0) {
                mx_swap_cat(ptr1, flag, ptr1->c_next);
                swapped = 1;
            }
            ptr1 = ptr1->c_next;
        }
        lptr = ptr1;
    }
}
