#include "uls.h"

void mx_print_totalsize(t_catalog *cat) {
    long long tmp_ds = cat->max_size_ofdir;
    long long tmp_ls = cat->max_size_oflink;

    mx_printstr("total ");
    mx_printull(cat->size_of_block);
    mx_printstr("\n");
    for (cat->max_size_ofdir = 0; tmp_ds != 0;
    tmp_ds /= 10, cat->max_size_ofdir++);
    for (cat->max_size_oflink = 0; tmp_ls != 0;
    tmp_ls /= 10, cat->max_size_oflink++);
}
