#include "uls.h"

// инициализация инфо
void mx_init_info(char **argv, t_main *info) {
    t_catalog *head = NULL;

	head = mx_create_list_of_catalog(info->am_dir);
	info->cat = head; // инициализация листа каталогов
	for (; head; head = head->c_next, argv++) {
		mx_set_start_val_cat(head);
		head->is_dir = true;
		head->c_name = mx_strdup(*argv);
		head->dir = (t_dir_data*)malloc(sizeof(t_dir_data));
		if(info->flag.is_R && !info->flag.is_a)
			head->dir_data = (t_dir_data *)malloc(sizeof(t_dir_data));
	}
}
