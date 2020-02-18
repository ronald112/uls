#include "uls.h"

void mx_r_flag(t_main *info, t_catalog *cat, char *link) {
	// DIR *directoy = mx_opendir_info(info, cat, link);
	DIR *directoy = opendir(link);
	t_dir_data *list = cat->dir;
	struct dirent *temp = NULL;
	t_catalog *cat_local = NULL;
	t_catalog *head = NULL;
	printf("[[Debug]]\n");

	printf("%p\n", (void *)directoy);

	if (directoy && (temp = readdir(directoy))) {
		put_data(temp, info, list, cat, link);
	// printf("[[Debug]] %s %p\n", link, (void*)list->buff_stat);
		if(MX_ISDIR(list->buff_stat->st_mode)) {
			cat_local = (t_catalog *)malloc(sizeof(t_catalog));
			cat_local->c_name = mx_strjoin(cat_local->c_name, link);
			cat_local->c_name = mx_strjoin(cat_local->c_name, "/");
			cat_local->c_name = mx_strjoin(cat_local->c_name, list->name);
			head = cat_local;
			cat_local->c_next = NULL;
	printf("!![[Debug]] %s\n", cat_local->c_name);
		}
	}
	while (directoy && (temp = readdir(directoy))) {
		list->next = (t_dir_data *)malloc(sizeof(t_dir_data));
		list = list->next;
		put_data(temp, info, list, cat, link);
		if(MX_ISDIR(list->buff_stat->st_mode)) {
			cat_local->c_next = (t_catalog *)malloc(sizeof(t_catalog));
			cat_local = cat_local->c_next;
			cat_local->c_name = mx_strjoin(cat_local->c_name, link);
			cat_local->c_name = mx_strjoin(cat_local->c_name, "/");
			cat_local->c_name = mx_strjoin(cat_local->c_name, list->name);
	printf("!!![[Debug]] %s\n", cat_local->c_name);
			cat_local->c_next = NULL;
		}
	}
	printf("[[Debug]]\n");
	mx_sort_cat_list(info->cat, info->flag);
	for(int i = 0; head; head = head->c_next) {
		printf("%d\n", i++);
		if(mx_strcmp(head->c_name, "./.") != 0 && mx_strcmp(head->c_name, "./..") != 0)
			mx_r_flag(info, head, head->c_name);
		printf("{{Debug}}%p\n", (void*)head->dir);
		mx_print_1(head, info->flag.is_a);
		printf("\n---------\n");
	}
	mx_closedir_info(info, directoy, link);
}
