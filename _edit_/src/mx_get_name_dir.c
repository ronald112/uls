#include "uls.h"

char *mx_get_name_dir(t_main *info, char *link) {
    int i = mx_strlen(link) - 1;

    for (; link[i] != '/' && i > 1; --i);
    temp = mx_strjoin(info->uls_name, &link[i + 1]);
}
