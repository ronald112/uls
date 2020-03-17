#include "uls.h"

void mx_print_default(t_catalog *cat) {
    t_catalog *head = cat;
    t_dir_data *list = head->dir_data;

    for (; head; head = head->c_next) {
        list = head->dir_data;
        while (list) {
            mx_printstr(list->name);
            mx_printstr("\t");
            list = list->next;
        }
    }
    mx_printchar('\n');
}

void mx_print_tab(t_catalog *cat, t_dir_data *data) {
    int tab = cat->max_length / 8 + 1;
    int extra = mx_strlen(data->name) / 8;

    for (int i = 0; i < (tab - extra); ++i)
        mx_printchar('\t');
}

// TODO CHECK ?
void mx_print_cat(t_catalog *cat, t_main *info) {
    t_dir_data *dir = info->flag.is_a ? cat->dir : cat->dir_data;
    t_dir_data *tmp = dir;
    t_dir_data *temp = NULL;

    for (int i = 0; i < cat->lines_for_print && dir; i++) {
        tmp = dir;
        while(tmp) {
            info->flag.is_tofile ? mx_printstr(tmp->name)
            : mx_printstr(mx_check_name_valid(tmp->name, 2));
            temp = tmp;
            for (int j = 0; j < cat->lines_for_print && tmp; j++)
                tmp = tmp->next;
            if(tmp)
                mx_print_tab(cat, temp);
        }
        mx_printchar('\n');
        dir = dir->next;
    }
}

void mx_print_1(t_catalog *cat, t_main *info) {
    for (t_dir_data *dir = info->flag.is_a ? cat->dir : cat->dir_data;
         dir; dir = dir->next) {
        mx_printstr(mx_check_name_valid(dir->name, info->flag.is_tofile));
        mx_printchar('\n');
    }
}

void mx_print(t_main *info) {
    t_catalog *head = info->cat;

    mx_count_line_for_print(info);
    for (; head; head = head->c_next)
        if (head->is_dir) {
            if (info->am_dir != 1 && mx_strcmp(head->c_name, "!!!") != 0) {
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
            if (info->am_dir != 1 && head->c_next)
                mx_printchar('\n');
        }
}
