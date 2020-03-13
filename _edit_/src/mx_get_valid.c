#include "uls.h"

// 1 - '\0'; 2 - '?'
char *mx_check_name_valid(char *name, int index) {
    char *symb = name;

    for (; *name; name++) {
        if (*name == '\a' || *name == '\b' || *name == '\t' || *name == '\n'
            || *name == '\v' || *name == '\f' || *name == '\r')
            *name = index == 1 ? '\0' : '?';
    }
    return symb;
}

int mx_get_max_length(t_dir_data *dir) {
    int max = 0;
    t_dir_data *list = dir;

    while (list) {
        max = mx_strlen(list->name) >= max ? mx_strlen(list->name) : max;
        list = list->next;
    }
    return max;
}
