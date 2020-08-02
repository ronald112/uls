#include "uls.h"

void mx_push_back_dir(char *link, t_flag flag, t_catalog *cat) {
    t_dir_data *cur = NULL;
    t_dir_data **list = &cat->dir;

    if (*list == NULL) {
        *list = mx_create_node_dir(link, flag, cat);
    }
    else {
        cur = *list;
        for (; cur->next != NULL; cur = cur->next);
        cur->next = mx_create_node_dir(link, flag, cat);
    }
}

t_catalog *mx_free_dir_data(t_main *info, t_catalog **prev) {
    mx_strdel(&info->cat->c_name);
    info->cat = info->cat->c_next;
    free(prev);
    *prev = info->cat;
    return info->cat->c_next;
}

void mx_del_node(t_main *info) {
    t_catalog *prev = info->cat;
    t_catalog *list = info->cat->c_next ? info->cat->c_next : NULL;

    if (list && !info->cat->is_dir) {
        list = mx_free_dir_data(info, &prev);
        for (; prev && prev->c_next; list = prev->c_next)
            if (!list->is_dir) {
                mx_strdel(&list->c_name);
                prev->c_next = list->c_next;
                free(list);
            }
            else
                prev = prev->c_next;
    }
    else if (!prev->is_dir) {
        mx_strdel(&info->cat->c_name);
        free(prev);
        info->cat = NULL;
    }
}

t_dir_data *mx_create_node_dir(char *data, t_flag flag, t_catalog *cat) {
    t_dir_data *new_node = NULL;

    if (data && (new_node = (t_dir_data *)malloc(sizeof(t_dir_data)))) {
        new_node->name = mx_strdup(data);
        new_node->path = mx_get_full_path(".", new_node->name);
        if (flag.is_l == true)
            mx_ladd_to_tdir(new_node, cat, flag);
        new_node->next = NULL;
    }
    return new_node;
}
