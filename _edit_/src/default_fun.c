#include "uls.h"

char *mx_check_name_valid(char *name, int index) {/* 1 - '\0'; 2 - '?'*/
    char *symb = name;

    for (; *name; name++) {
        if (*name == '\a' || *name == '\b' || *name == '\t' || *name == '\n'
            || *name == '\v' || *name == '\f' || *name == '\r')
            *name = index == 1 ? '\0' : '?';
    }
    return symb;
}

void mx_make_extra_catalog(t_main *info, char *link) {
    for (t_catalog *head = info->cat; head; head = head->c_next) {
        if (mx_strcmp("!!!", head->c_name) == 0) {
            mx_push_back(link, info->flag, head);
            head->dir_data = head->dir;
        }
        else if (head->c_next == NULL) {
            head->c_next = (t_catalog *)malloc(sizeof(t_catalog));
            head->c_next->c_next = NULL;
            head->c_next->is_dir = true;
            head->c_next->size_of_block = 0;
            head->c_next->max_size_oflink = 0;
            head->c_next->max_size_ofdir = 0;
            head->c_next->lng_max_minor = 0;
            head->c_next->lng_max_major = 0;
            head->c_next->max_length = 0;
            head->c_next->max_lnght_namedir = 0;
            head->c_next->max_lnght_grpdir = 0;
            head->c_next->is_char_block = false;
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
    char *temp = NULL;
    errno = 0;

    int i = mx_strlen(link) - 1;
    for (; link[i] != '/' && i > 1; --i);
    temp = mx_strjoin(info->uls_name, &link[i + 1]);

    if ((dir = opendir(link)) == NULL) {
        if (errno != ENOTDIR) {
            perror(temp);
        }
        free(cat->dir);
        cat->dir = NULL;
        cat->dir_data = NULL;
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
        list->name = mx_strdup(list->data->d_name);
        list->path = mx_get_full_path(link, list->name);
        if (info->flag.is_l == true)
            mx_ladd_to_tdir(list, cat, info->flag);
        list->next = NULL;
        cat->am_data++;
    }
    while (directoy && (temp = readdir(directoy))) {
        list->next = (t_dir_data *)malloc(sizeof(t_dir_data));
        list = list->next;
        list->data = temp;
        list->name = mx_strdup(temp->d_name);
        list->path = mx_get_full_path(link, list->name);
        if (info->flag.is_l == true)
            mx_ladd_to_tdir(list, cat, info->flag);
        list->next = NULL;
        cat->am_data++;
    }
    mx_closedir_info(info, directoy, link);
}

static int get_max_length(t_dir_data *dir) {
    int max = 0;
    t_dir_data *list = dir;

    while (list) {
        max = mx_strlen(list->name) >= max ? mx_strlen(list->name) : max;
        list = list->next;
    }
    return max;
}

void mx_count_line_for_print(t_main *info) {
    struct winsize w;
    int max_cols;
    int amount;
    t_dir_data *files;
    size_t width;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    width = !info->flag.is_tofile ? w.ws_col : MX_FILE_WS;
    for (t_catalog *head = info->cat; head; head = head->c_next) {				// проделываем для каждой дир, указан. в аргументах
        files = info->flag.is_a ? head->dir : head->dir_data;
        amount = info->flag.is_a ? head->am_data : head->am_files;
        head->lines_for_print = 0;										// обнуляем количество линий для дир
        head->max_length = get_max_length(files);										// находим макимально возможную длину названия файла в дир
        max_cols = (width / (8 - (head->max_length % 8) + head->max_length));				// высчитываем количество колонок
        max_cols = max_cols != 0 ? max_cols : 1;
        head->lines_for_print = max_cols != 0 ? amount / max_cols : 0;		// высчитвыаем количество линий
        if(head->lines_for_print == 0 || (amount % max_cols) != 0)							// доп проверка на линии
            head->lines_for_print++;
    }
}

void mx_count_line_for_print_R(t_main *info, t_catalog *head) {
    struct winsize w;
    int max_cols;
    int amount;
    t_dir_data *files;
    size_t width;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    width = !info->flag.is_tofile ? w.ws_col : MX_FILE_WS;
    files = info->flag.is_a ? head->dir : head->dir_data;
    amount = info->flag.is_a ? head->am_data : head->am_files;
    head->lines_for_print = 0;										// обнуляем количество линий для дир
    head->max_length = get_max_length(files);										// находим макимально возможную длину названия файла в дир
    max_cols = (width / (8 - (head->max_length % 8) + head->max_length));	// высчитываем количество колонок
    max_cols = max_cols != 0 ? max_cols : 1;
    head->lines_for_print = max_cols != 0 ? amount / max_cols : 0;		// высчитвыаем количество линий
    if(head->lines_for_print == 0 || (amount % max_cols) != 0)							// доп проверка на линии
        head->lines_for_print++;
}

void mx_print_default(t_catalog *cat) {
    t_catalog *head = cat;
    t_dir_data *list = head->dir_data;

    for (; head; head = head->c_next) {
        list = head->dir_data;
        // printf("%s:\n", head->c_name);
        while (list) {
            mx_printstr(list->name);
            mx_printstr("\t");
            list = list->next;
        }
    }
    mx_printchar('\n');
}

void mx_swap_dir(t_dir_data *a, t_dir_data *b) {
    struct dirent *tmp_data = a->data;
    char *tmp_name = a->name;
    struct stat *tmp_buff = a->buff_stat;
    int tmp_size_pwd = a->min_lnght_namedir;

    a->data = b->data;
    b->data = tmp_data;
    a->name = b->name;
    b->name = tmp_name;

    tmp_name = a->path;
    a->path = b->path;
    b->path = tmp_name;
    a->buff_stat = b->buff_stat;
    b->buff_stat = tmp_buff;
    a->min_lnght_namedir = b->min_lnght_namedir;
    b->min_lnght_namedir = tmp_size_pwd;
    tmp_size_pwd = a->min_lnght_grpdir;
    a->min_lnght_grpdir = b->min_lnght_grpdir;
    b->min_lnght_grpdir = tmp_size_pwd;
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

static void print_tab(t_catalog *cat, t_dir_data *data) {
    int tab = cat->max_length / 8 + 1;
    int extra = mx_strlen(data->name) / 8;

    for (int i = 0; i < (tab - extra); ++i)
        mx_printchar('\t');
}

void mx_print_cat(t_catalog *cat, t_main *info) {
    t_dir_data *dir = info->flag.is_a ? cat->dir : cat->dir_data;
    t_dir_data *tmp = dir;
    t_dir_data *temp = NULL;

    for (int i = 0; i < cat->lines_for_print && dir; i++, dir = dir->next) {
        tmp = dir;
        while(tmp) {
            info->flag.is_tofile ? mx_printstr(tmp->name)
                : mx_printstr(mx_check_name_valid(tmp->name, 2));
            temp = tmp;
            for (int j = 0; j < cat->lines_for_print && tmp; j++)
                tmp = tmp->next;
            if(tmp)
                print_tab(cat, temp);
        }
        mx_printchar('\n');
    }
}

void mx_print_1(t_catalog *cat, t_main *info) {
    t_dir_data *dir = dir = info->flag.is_a ? cat->dir : cat->dir_data;

    for (; dir; dir = dir->next){
        mx_printstr(mx_check_name_valid(dir->name, info->flag.is_tofile));
        mx_printchar('\n');
    }
}

void mx_print_R(t_main *info, t_catalog *head) {
    static int counter = 0;

    mx_count_line_for_print_R(info, head);
    if (counter != 0) {
        mx_printchar('\n');
        mx_printstr(head->c_name);
        mx_printstr(":\n");
    }
    if (info->flag.is_l == true) {
        if (info->flag.is_a == false && head->am_files != 0)
            mx_print_totalsize(head);
        else if (info->flag.is_a == true && head->am_data != 0)
            mx_print_totalsize(head);
        mx_print_lflag(head, info->flag);
    }
    else if (!info->flag.is_tofile) {
        info->flag.is_1 ? mx_print_1(head, info)
        : mx_print_cat(head, info);
    }
    else
        info->flag.is_C ? mx_print_cat(head, info)
        : mx_print_1(head, info);
    counter++;
}

void mx_print(t_main *info) {
    t_catalog *head = info->cat;

    mx_count_line_for_print(info);
    for (; head; head = head->c_next) {
        if (head->is_dir) {
            if (info->am_dir != 1 && mx_strcmp(head->c_name, "!!!") != 0) {
                mx_printstr(head->c_name);
                mx_printstr(":\n");
            }
            if (info->flag.is_l == true) {
                if (info->flag.is_a == false && head->am_files != 0)
                    mx_print_totalsize(head);
                else if (info->flag.is_a == true && head->am_data != 0)
                    mx_print_totalsize(head);
                mx_print_lflag(head, info->flag);
            }
            else if (!info->flag.is_tofile) {
                info->flag.is_1 ? mx_print_1(head, info)
                : mx_print_cat(head, info);
            }
            else
                info->flag.is_C ? mx_print_cat(head, info)
                : mx_print_1(head, info);
            if (info->am_dir != 1 && head->c_next)
                mx_printchar('\n');
        }
    }
}

// доделать переход с dir на dir_data
void mx_get_dir_data_from_dir(t_catalog *head) {
    t_dir_data *data = head->dir;
    int i = 0;

    for(; data && *(data->name) == '.'; i++, data = data->next);
    if (mx_strcmp(head->c_name, "!!!") != 0 && head->dir->next->next) {
        head->dir_data = data;
        head->am_files = head->am_data - i;
    }
}

void mx_switch_read_data(t_main *info, t_catalog *head) {
    if (info->flag.is_R) {
        if (info->flag.is_a)
            mx_r_flag_a(info, head, head->c_name);
        else
            mx_r_flag(info, head, head->c_name);
    }
    else
        mx_get_data_list(info, head, head->c_name);
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
            mx_switch_read_data(info, head);
        }
        if(head && head->dir && ((!info->flag.is_R && !info->flag.is_a)
                    || (info->flag.is_R && info->flag.is_a))) {
            mx_sort_dir_list(head->dir, info->flag);
            if (mx_strcmp(head->c_name, "!!!") != 0 && head->dir->next->next) {
                head->dir_data = head->dir->next->next;
                head->am_files = head->am_data - 2;
            }
            mx_get_dir_data_from_dir(head);
        }
    }
    // printf("{}{}{}{}{}{}\n");
    mx_sort_cat_list(info->cat, info->flag);
    // printf("{}{}{ %p }{}{}{}\n", (void *)info->cat->c_next);
    mx_del_node(info);
    // printf("{}{}{}{}{}{}\n");
    if (!info->flag.is_R)
        mx_print(info);
    // system("leaks -q uls");
    return errno == 0 ? 0 : 1;
}
