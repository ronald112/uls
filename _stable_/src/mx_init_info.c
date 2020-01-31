#include "uls.h"

// инициализация инфо
void mx_init_info(char **argv, t_main *info) { 
    t_catalog *head = NULL;
	head = mx_create_list_of_catalog(info->am_dir);
	info->cat = head; // инициализация листа каталогов
	for (; head; head = head->c_next, argv++) {
		head->am_data = 0;
		head->am_files = 0;
		head->c_name = mx_strdup(*argv);
		head->dir = (t_dir_data*)malloc(sizeof(t_dir_data));
		// head->dir_data = (t_dir_data*)malloc(sizeof(t_dir_data));
	}
	info->uls_name = mx_strdup("uls: ");
}