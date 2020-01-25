#include "uls.h"

static t_dir_data *create_node(char *data) {
    t_dir_data *new_node = NULL;

    if (data && (new_node = (t_dir_data *)malloc(sizeof(t_dir_data)))) {
        new_node->name = mx_strdup(data);
        new_node->next = NULL;
    }
    return new_node;
}

static void push_back(t_dir_data **list, char *link) {
    t_dir_data *cur = NULL;

    printf("==========================\n");
    if (*list == NULL) {
        *list = create_node(link);
    }
    else {
        cur = *list;

        for (; cur->next != NULL; cur = cur->next);
        cur->next = create_node(link);
    }
}

void mx_make_extra_catalog(t_main *info, char *link) {
    t_catalog *head = info->cat;
    bool no_exist = true;

        printf("==========///=======\n");
    while (head) {
        if (mx_strcmp(head->c_name, "!!!") == 0) {
            push_back(&(head->dir), link);
            head->am_files++;
            head->dir_data = head->dir;
            no_exist = false;
        // printf("==========///=======\n");
            break;
        }
        head = head->c_next;
    }
    if (no_exist) {
        if(head == NULL) {
            info->cat = (t_catalog *)malloc(sizeof(t_catalog));
            head = info->cat;
        }
        else {
            head->c_next = (t_catalog *)malloc(sizeof(t_catalog));
            head = head->c_next;
        }
        head->c_name = mx_strdup("!!!");
        head->am_files = 1;
        head->dir = NULL;
        head->c_next = NULL;
        push_back(&(head->dir), link);
        head->dir_data = head->dir;
    }
}

// void mx_del_node()

DIR *mx_opendir_info(t_main *info, t_catalog *cat, char *link) {//-----------
    DIR *dir;
    // t_catalog *head = info->cat;
// printf("======%p====%s======\n", (void*)info->cat, info->cat->c_next->c_name);
    if ((dir = opendir(link)) == NULL) {
        char *temp = mx_strjoin(info->uls_name, link);

        if (errno != ENOTDIR)
            perror(temp);
        mx_strdel(&temp);
        free(cat->dir);
        cat->dir = NULL;
        cat->dir_data = NULL;
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

void mx_get_data_list(t_main *info, t_catalog *cat, char *link) {//-----------
    DIR *directoy = mx_opendir_info(info, cat, link);
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
    int max_cols;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    for (t_catalog *head = info->cat; head; head = head->c_next) {									// проделываем для каждой дир, указан. в аргументах
        head->lines_for_print = 0; 										// обнуляем количество линий для дир
        head->max_length = get_max_length(head->dir_data);										// находим макимально возможную длину названия файла в дир
        max_cols = (w.ws_col/(8 - (head->max_length % 8) + head->max_length));				// высчитываем количество колонок
        head->lines_for_print = head->am_files / max_cols;		// высчитвыаем количество линий
        if(head->lines_for_print == 0 || (head->am_files % max_cols) != 0)							// доп проверка на линии
            head->lines_for_print++;
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
        printf("%s:\n", head->c_name);
        while (list) {
            mx_printstr(list->name);
            mx_printstr("\t");
            list = list->next;
        }
    }
    mx_printchar('\n');
}

//=============================================================================
t_main *mx_init_info(int argc, char **argv) { // инициализация инфо
    t_main *info = (t_main*)malloc(sizeof(t_main));
    t_catalog *head = NULL;

    info->am_dir = argc == 1 ? 1 : argc - 1;
    head = mx_create_list_of_catalog(info->am_dir);
    info->cat = head; // инициализация листа каталогов
    for (int i = 1; head; head = head->c_next, i++) {
        head->am_data = 0;
        head->am_files = 0;
        head->c_name = mx_strdup(argv[i]);
        head->dir = (t_dir_data*)malloc(sizeof(t_dir_data));
        // head->dir_data = (t_dir_data*)malloc(sizeof(t_dir_data));
    }
    info->uls_name = mx_strdup("uls: ");
    return info;
}

//================= Sort Part ======================

void mx_swap_cat(t_catalog *a, t_catalog *b) { 
    t_dir_data *tmp_data = a->dir;
    char *tmp_name = a->c_name;
    int tmp = a->am_files;

    a->dir = b->dir;
    b->dir = tmp_data;

    tmp_data = a->dir_data;
    a->dir_data = b->dir_data;
    b->dir_data = tmp_data;

    a->c_name = b->c_name;
    b->c_name = tmp_name;

    a->am_files = b->am_files;
    b->am_files = tmp;

    tmp = a->am_data;
    a->am_data = b->am_data;
    b->am_data = tmp;
}

void mx_sort_cat_list(t_catalog *start) { 
    int swapped = 1;
    t_catalog *ptr1;
    t_catalog *lptr = NULL;

    if (start == NULL)
        return;
    while (swapped) { 
        swapped = 0;
        ptr1 = start;
        while (ptr1->c_next != lptr) { 
            if (mx_strcmp(ptr1->c_name, ptr1->c_next->c_name) > 0) {
                mx_swap_cat(ptr1, ptr1->c_next);
                swapped = 1;
            }
            ptr1 = ptr1->c_next;
        }
        lptr = ptr1;
    }
}



void mx_swap_dir(t_dir_data *a, t_dir_data *b) { 
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
                mx_swap_dir(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
}
//=============================================================================

static void print_tab(t_catalog *cat) {
    int am_tab = cat->max_length / 8;

    for (int i = 0; i < am_tab; ++i)
        mx_printchar('\t');
}

void mx_print(t_main *info) {
    t_catalog *head = info->cat;
    t_dir_data *tmp = NULL;

    for (int counter = 0; head; head = head->c_next, counter = 0) {
        if(info->am_dir != 1) {
            mx_printstr(head->c_name);
            mx_printstr(":\n");
        }
        for (int i = 1; i <= head->lines_for_print; ++i, tmp = head->dir_data) {
            for (int count = 1; tmp; tmp = tmp->next, count++) {
                if (counter % i == 0) {
                    mx_printstr(tmp->name);
                    print_tab(head);
                }
            }
            mx_printchar('\n');
        }
    }
}

int main(int argc, char *argv[]) {
    t_main *info = mx_init_info(argc, argv);
    t_catalog *head = info->cat;

    for (int i = 1; head; i++, head = head->c_next) {
        if (argc > 1/* && mx_strcmp(head->c_name, "!!!") != 0*/)
            mx_get_data_list(info, head, head->c_name);
        else if (argc == 1)
            mx_get_data_list(info, head, ".");
        if(head && head->dir) {
            // system("leaks -q uls");

        // printf("==========***=======\n");
            mx_sort_dir_list(head->dir);
            if (mx_strcmp(head->c_name, "!!!") != 0 && head->dir->next->next) {
                head->dir_data = head->dir->next->next;
                head->am_files = head->am_data - 2;
            }
        }
    }
    // printf("**********************\n");
    mx_sort_cat_list(info->cat);
    // printf("**********************\n");
    // printf("%s %s %p %d\n", info->cat->c_name, info->cat->c_next->c_name, (void*)info->cat->c_next->c_next, info->cat->am_files);
    mx_count_line_for_print(info);//*******************************************
    // printf("===============\n");
    // mx_print(info);
    mx_print_default(info->cat);//-----------info----------------
    // system("leaks -q uls");
    // system("ls");
    return 0;
}

///////////////////////////////////////////////////////////////////////////////

// #include <stdio.h>
// #include <time.h>
// #include <sys/stat.h>
// #include <string.h>
// #include <stdlib.h>
// int main() {
//     char *date;
//     int ret;
//     struct stat buf;
//     if ((ret = stat("Makefile", &buf))!=0) {
//         fprintf(stderr, "stat failure error .%d", ret);
//         abort();
//     }
//     date = asctime(localtime(&buf.st_ctime));
//     printf("\n %s\n", date);
//     printf("\n %d mode\n", buf.st_mode);
//     printf("\n %lld size\n", buf.st_size);
// }

///////////////////////////////////////////////////////////////////////////////

// #include <errno.h>
// #include <stdio.h>
// #include <string.h>
// #include <sys/stat.h>
// #include <sys/types.h>
// #include <time.h>
// #include <unistd.h>

// #define TIME_STRING_BUF 50

// /* Пользователь передает buf (минимальной длины TIME_STRING_BUF) вместо

//    использования статического для функции буфера, чтобы избежать применения

//    локальных статических переменных и динамической памяти. Никаких ошибок

//    происходить не должно, поэтому никакой проверки ошибок не делаем. */
// char *timeString (time_t t, char *buf) {
//     struct tm *local;
//     local = localtime(&t);
//     strftime(buf, TIME_STRING_BUF, "%c", local);
//     return buf;
// }


//  /* Отобразить всю информацию, полученную от lstat() по имени
//     файла как единственному параметру. */

// int statFile(const char *file) {
//     struct stat statbuf;
//     char timeBuf[TIME_STRING_BUF];

//     if (lstat(file, &statbuf)) {
//         fprintf(stderr, "не удалось lstat %s: %s ", file,
//         strerror(errno));
//         return 1;
//     }

//     printf("Имя файла : %s\n", file);
//     printf("На устройстве: старший %d младший %d Inode номер: %llu\n" , major(statbuf.st_dev), minor(statbuf.st_dev), statbuf.st_ino);
//     printf("Размер : %-101lld\nTип: %07o\nПрава доступа : %05o\n", statbuf.st_size, statbuf.st_mode & S_IFMT, statbuf.st_mode &~(S_IFMT));
//     printf("Владелец : %d Группа : %d\nКоличество ссылок : %d\n", statbuf.st_uid, statbuf.st_gid, statbuf.st_nlink);
//     printf("Время создания : %s\n", timeString(statbuf.st_ctime, timeBuf));
//     printf("Время модификации : %s\n", timeString(statbuf.st_mtime, timeBuf));
//     printf("Время доступа : %s\n", timeString (statbuf.st_atime, timeBuf));
//     return 0;
// }

// int main(int argc, const char **argv) {
//     int i;
//     int rc = 0 ;
// /* Вызвать statFile() для каждого имени файла,
// переданного в командной строке. */
//     for (i = 1; i < argc; i++) {
// /* Если statFile() сбоит, rc будет содержать не ноль.*/
//         rc |= statFile(argv[i]);
// /* это печатает пробел между позициями,
//    но не за последней */
//         if ((argc - i) > 1)
//             printf (" ");
//     }
//  return rc;
// }

///////////////////////////////////////////////////////////////////////////////

// int main(int argc, char *argv[])
// {
//     int a = 2;

//     // a <<= 2;

//     printf("%d\n", a|8);
//     return 0;
// }


//============Макросы типа===============
/*
* #define MX_ISDIR(mode) (((mode) & S_IFMT) == S_IFDIR)
* #define MX_ISCHR(mode) (((mode) & S_IFMT) == S_IFCHR)
* #define MX_ISBLK(mode) (((mode) & S_IFMT) == S_IFBLK)
* #define MX_ISFIFO(mode) (((mode) & S_IFMT) == S_IFFIFO)
* #define MX_ISLNK(mode) (((mode) & S_IFMT) == S_IFLNK)
* #define MX_ISSOCK(mode) (((mode) & S_IFMT) == S_IFSOCK)
**/


