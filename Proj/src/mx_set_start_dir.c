#include "uls.h"

void mx_set_start_dir_data(t_dir_data *list, t_catalog *cat, t_main *info) {
    list->name = mx_strdup(list->data->d_name);
    list->path = mx_get_full_path(cat->c_name, list->name);
    if (info->flag.is_l == true)
        mx_ladd_to_tdir(list, cat, info->flag);
    list->next = NULL;
    cat->am_data++;
}
