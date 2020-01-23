#include "uls.h"

DIR *mx_opendir_info(t_main *info, char *link) {//-----------
    DIR *dir;

    if ((dir = opendir(link)) == NULL) {
        char *temp = mx_strjoin(info->uls_name, link);

        // errno = ENOENT;
        perror(temp);
        return dir;
    }
    else {
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

t_dir_data *mx_get_data_list(t_main *info, t_catalog *cat, char *link) {//-----------
    DIR *directoy = mx_opendir_info(info, link);
    t_dir_data *list = cat->dir;
    struct dirent *temp = NULL;

    if (directoy && (temp = readdir(directoy))) {
        list->data = temp;
        list->name = mx_strdup(temp->d_name);
        list->next = NULL;
        cat->am_data++;
    }
    while (directoy && (temp = readdir(directoy))) {
        list->next = (t_dir_data *)malloc(sizeof(t_dir_data));
        list = list->next;
        list->data = temp;
        list->name = mx_strdup(temp->d_name);
        list->next = NULL;
        cat->am_data++;
    }
    mx_closedir_info(info, directoy, link);
    return cat->dir;
}

//=============================================================================

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
    int max_length;
    int max_cols;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    for (t_catalog *head = info->cat; head; head = head->c_next) {									// проделываем для каждой дир, указан. в аргументах
        head->lines_for_print = 0; 										// обнуляем количество линий для дир
        max_length = get_max_length(head->dir_data);
        printf("max_length %d\n", max_length);												// находим макимально возможную длину названия файла в дир
        max_cols = (w.ws_col/(8 - (max_length % 8) + max_length));				// высчитываем количество колонок
        printf("max_cols %d\n", max_cols);
        head->lines_for_print = head->am_dir_data / max_cols;		// высчитвыаем количество линий
        printf("lines_for_print1 %d\n", head->lines_for_print);
        if(head->lines_for_print == 0 || (head->am_dir_data % max_cols) != 0)							// доп проверка на линии
            head->lines_for_print++;
        printf("lines_for_print2 %d\n", head->lines_for_print);
    }
}

//=============================================================================

t_catalog *mx_create_list_of_catalog(int amount) {
    t_catalog *head = (t_catalog *)malloc(sizeof(t_catalog));
    t_catalog *node = head;

    head->c_next = NULL;
    for(int i = 1; i < amount; i++) {
        node->c_next = (t_catalog *)malloc(sizeof(t_catalog));
        node = node->c_next;
        node->c_next = NULL;
    }
    return head;
}

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

//=============================================================================
t_main *mx_init_info(int argc) { // инициализация инфо
    t_main *info = (t_main*)malloc(sizeof(t_main));
    t_catalog *head = NULL;

    info->am_dir = argc == 1 ? 1 : argc - 1;
    head = mx_create_list_of_catalog(info->am_dir);
    info->cat = head; // инициализация листа каталогов
    for (; head; head = head->c_next) {
        head->am_data = 0;
        head->am_dir_data = 0;
        head->dir = (t_dir_data*)malloc(sizeof(t_dir_data));
        head->dir_data = (t_dir_data*)malloc(sizeof(t_dir_data));
    }
    info->uls_name = mx_strdup("uls: ");
    return info;
}

void mx_swap(t_dir_data *a, t_dir_data *b) { 
    struct dirent *tmp_data = a->data;
    char *tmp_name = a->name;

    a->data = b->data;
    b->data = tmp_data;
    a->name = b->name;
    b->name = tmp_name;
}

void mx_sort_dir_list(t_dir_data *start) { 
    int swapped = 1;
    t_dir_data *ptr1;
    t_dir_data *lptr = NULL;

    if (start == NULL)
        return;
    while (swapped) { 
        swapped = 0;
        ptr1 = start;
        while (ptr1->next != lptr) { 
            if (mx_strcmp(ptr1->name, ptr1->next->name) > 0) {
                mx_swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
}
//=============================================================================

int main(int argc, char *argv[]) {
    t_main *info = mx_init_info(argc); 
    t_catalog *head = info->cat;

    for (int i = 0; head; i++, head = head->c_next) {
        if (argc > 1)
            mx_get_data_list(info, head, argv[i + 1]);
        else if (argc == 1)
            mx_get_data_list(info, head, ".");
        mx_sort_dir_list(head->dir);
        if (head->dir->next->next) {
            head->dir_data->data = head->dir->next->next->data;
            head->dir_data->name = head->dir->next->next->name;
            head->dir_data->next = head->dir->next->next->next;
            head->am_dir_data = head->am_data;
        }
    }
    mx_count_line_for_print(info);//*******************************************
    mx_print_default(info->cat);//-----------info----------------
    // system("leaks -q uls");
    // system("ls");
    return 0;
}
