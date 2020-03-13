#include "uls.h"

void mx_count_line_for_print(t_main *info) {
    struct winsize w;
    int max_cols = 0;
    int amount = 0;
    t_dir_data *files;
    size_t width = 0;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    width = !info->flag.is_tofile ? w.ws_col : MX_FILE_WS;
    for (t_catalog *head = info->cat; head; head = head->c_next) {				// проделываем для каждой дир, указан. в аргументах
        files = info->flag.is_a ? head->dir : head->dir_data;
        amount = info->flag.is_a ? head->am_data : head->am_files;
        head->lines_for_print = 0;										// обнуляем количество линий для дир
        head->max_length = mx_get_max_length(files);										// находим макимально возможную длину названия файла в дир
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
    head->max_length = mx_get_max_length(files);										// находим макимально возможную длину названия файла в дир
    max_cols = (width / (8 - (head->max_length % 8) + head->max_length));	// высчитываем количество колонок
    max_cols = max_cols != 0 ? max_cols : 1;
    head->lines_for_print = max_cols != 0 ? amount / max_cols : 0;		// высчитвыаем количество линий
    if(head->lines_for_print == 0 || (amount % max_cols) != 0)							// доп проверка на линии
        head->lines_for_print++;
}

