#include "uls.h"

void mx_make_extra_catalog(t_main *info, char *link) {
    for (t_catalog *head = info->cat; head; head = head->c_next) {
        if (mx_strcmp("!!!", head->c_name) == 0) {
            mx_push_back(link, info->flag, head);
            head->dir_data = head->dir;
        }
        else if (head->c_next == NULL) {
            head->c_next = (t_catalog *)malloc(sizeof(t_catalog));
            mx_set_start_val_cat(head->c_next);
            head->c_next->c_next = NULL;
            head->c_next->is_dir = true;
            head->c_next->dir = NULL;
            head->c_next->dir_data = NULL;
            head->c_next->c_name = mx_strdup("!!!");
        }
    }
}

void mx_free_dir_data(t_catalog **cat) {
    mx_strdel(&(*cat)->c_name);
}

DIR *mx_opendir_info(t_main *info, t_catalog *cat, char *link) {
    DIR *dir;
    char *temp = mx_get_name_dir(info, link);
    errno = 0;

    if ((dir = opendir(link)) == NULL) {
        if (errno != ENOTDIR)
            perror(temp);
        free(cat->dir);
        cat->is_dir = errno == EACCES ? true : false;
        if (errno == ENOTDIR)
            mx_make_extra_catalog(info, cat->c_name);
        mx_strdel(&temp);
        return dir;
    }
    else {
        if (errno != 0)
            perror(temp);
        mx_strdel(&temp);
        return dir;
    }
}

// check if valid close
void mx_closedir_info(t_main *info, DIR *dir, char *link) {
    if (dir && closedir(dir) < 0) {
        char *temp = mx_strjoin(info->uls_name, link);

        errno = EBADF;
        perror(temp);
        exit(1);
    }
}

void mx_get_data_list(t_main *info, t_catalog *cat, char *link) {
    DIR *directoy = mx_opendir_info(info, cat, link);
    t_dir_data *list = cat->dir;
    struct dirent *temp = NULL;

    if (directoy && (temp = readdir(directoy))) {
        list->data = temp;
        mx_set_start_dir_data(list, cat, info);
    }
    while (directoy && (temp = readdir(directoy))) {
        list->next = (t_dir_data *)malloc(sizeof(t_dir_data));
        list = list->next;
        list->data = temp;
        mx_set_start_dir_data(list, cat, info);
    }
    mx_closedir_info(info, directoy, link);
}

