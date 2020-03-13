#include "uls.h"

// доделать переход с dir на dir_data
static void get_dir_data_from_dir(t_catalog *head) {
    t_dir_data *data = head->dir;
    int i = 0;

    for(; data && *(data->name) == '.'; i++, data = data->next);
    if (mx_strcmp(head->c_name, "!!!") != 0 && head->dir->next->next) {
        head->dir_data = data;
        head->am_files = head->am_data - i;
    }
}

static void switch_read_data(t_main *info, t_catalog *head) {
    if (info->flag.is_R) {
        if (info->flag.is_a)
            mx_r_flag_a(info, head, head->c_name);
        else
            mx_r_flag(info, head, head->c_name);
    }
    else
        mx_get_data_list(info, head, head->c_name);
}

static void sort_dir_if_true(t_main *info, t_catalog *head) {
    if (head && head->dir && ((!info->flag.is_R && !info->flag.is_a)
    || (info->flag.is_R && info->flag.is_a))) {
        mx_sort_dir_list(head->dir, info->flag);
        if (mx_strcmp(head->c_name, "!!!") != 0 && head->dir->next->next) {
            head->dir_data = head->dir->next->next;
            head->am_files = head->am_data - 2;
        }
        get_dir_data_from_dir(head);
    }
}

int main(int argc, char *argv[]) {
    t_main *info = (t_main*)malloc(sizeof(t_main));
    t_catalog *head = mx_main_parse_fnc(&argc, argv, info);

    info->flag.is_tofile = !isatty(1);
    for (int i = 1; head; i++, head = head->c_next) {
        if (argc >= 1 && mx_strcmp(head->c_name, "!!!") != 0) {
            if (argc == 1) {
                mx_strdel(&head->c_name);
                head->c_name = ".";
            }
            sort_dir_if_true(info, head);
            switch_read_data(info, head);
        }
    }
    mx_sort_cat_list(info->cat, info->flag);
    mx_del_node(info);
    if (!info->flag.is_R)
        mx_print(info);
    // system("leaks -q uls");
    return errno == 0 ? 0 : 1;
}
