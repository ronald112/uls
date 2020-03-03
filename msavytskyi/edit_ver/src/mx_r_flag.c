#include "uls.h"

// void mx_r_flag(t_main *info, t_catalog *cat, char *link) {
// 	// DIR *directoy = mx_opendir_info(info, cat, link);
// 	DIR *directoy = opendir(link);
// 	t_dir_data *list = cat->dir;
// 	struct dirent *temp = NULL;
// 	t_catalog *cat_local = NULL;
// 	t_catalog *head = NULL;
// 	printf("[[Debug]]\n");

// 	printf("%p\n", (void *)directoy);

// 	if (directoy && (temp = readdir(directoy))) {
//		put_data(temp, info, list, cat, link);
// 	// printf("[[Debug]] %s %p\n", link, (void*)list->buff_stat);
// 		if(MX_ISDIR(list->buff_stat->st_mode)) {
// 			cat_local = (t_catalog *)malloc(sizeof(t_catalog));
// 			cat_local->c_name = mx_strjoin(cat_local->c_name, link);
// 			cat_local->c_name = mx_strjoin(cat_local->c_name, "/");
// 			cat_local->c_name = mx_strjoin(cat_local->c_name, list->name);
// 			head = cat_local;
// 			cat_local->c_next = NULL;
// 	printf("!![[Debug]] %s\n", cat_local->c_name);
// 		}
// 	}
// 	while (directoy && (temp = readdir(directoy))) {
// 		list->next = (t_dir_data *)malloc(sizeof(t_dir_data));
// 		list = list->next;
// 		put_data(temp, info, list, cat, link);
// 		if(MX_ISDIR(list->buff_stat->st_mode)) {
// 			cat_local->c_next = (t_catalog *)malloc(sizeof(t_catalog));
// 			cat_local = cat_local->c_next;
// 			cat_local->c_name = mx_strjoin(cat_local->c_name, link);
// 			cat_local->c_name = mx_strjoin(cat_local->c_name, "/");
// 			cat_local->c_name = mx_strjoin(cat_local->c_name, list->name);
// 	printf("!!![[Debug]] %s\n", cat_local->c_name);
// 			cat_local->c_next = NULL;
// 		}
// 	}
// 	printf("[[Debug]]\n");
// 	mx_sort_cat_list(info->cat, info->flag);
// 	for(int i = 0; head; head = head->c_next) {
// 		printf("%d\n", i++);
// 		if(mx_strcmp(head->c_name, "./.") != 0 && mx_strcmp(head->c_name, "./..") != 0)
// 			mx_r_flag(info, head, head->c_name);
// 		printf("{{Debug}}%p\n", (void*)head->dir);
// 		mx_print_1(head, info->flag.is_a);
// 		printf("\n---------\n");
// 	}
// 	mx_closedir_info(info, directoy, link);
// }

void mx_init_local_info_a(t_dir_data *dir, t_main *info, char * link) {
    t_catalog *head = NULL;

	head = mx_create_list_of_catalog(info->am_dir);
	info->cat = head; // инициализация листа каталогов
	for (; head; dir = dir->next) {
		if (!dir->is_dir)
			continue;
		head->is_dir = true;
		head->am_data = 0;
		head->am_files = 0;
		head->size_of_block = 0;
		head->max_size_oflink = 0;
		head->max_size_ofdir = 0;
		head->max_lnght_namedir = 0;
		head->max_lnght_grpdir = 0;
		head->c_name = mx_strdup(link);
		if (mx_strcmp(head->c_name, "/") != 0)
			head->c_name = mx_strjoin_to_dst_malloc(head->c_name, "/");
		head->c_name = mx_strjoin_to_dst_malloc(head->c_name, dir->name);
		head->dir = (t_dir_data*)malloc(sizeof(t_dir_data));
		// printf("Writen %s\n", head->c_name);
		head = head->c_next;
	}
	// info->uls_name = mx_strdup("uls: ");
}

void mx_init_local_info(t_dir_data *dir, t_main *info, char * link) {
    t_catalog *head = NULL;

	head = mx_create_list_of_catalog(info->am_dir);
	info->cat = head; // инициализация листа каталогов
	for (; head; dir = dir->next) {
		if (!dir->is_dir)
			continue;
		head->is_dir = true;
		head->am_data = 0;
		head->am_files = 0;
		head->size_of_block = 0;
		head->max_size_oflink = 0;
		head->max_size_ofdir = 0;
		head->max_lnght_namedir = 0;
		head->max_lnght_grpdir = 0;
		head->c_name = mx_strdup(link);
		if (mx_strcmp(head->c_name, "/") != 0)
			head->c_name = mx_strjoin_to_dst_malloc(head->c_name, "/");
		head->c_name = mx_strjoin_to_dst_malloc(head->c_name, dir->name);
		head->dir_data = (t_dir_data*)malloc(sizeof(t_dir_data));
		// printf("Writen %s\n", head->c_name);
		head = head->c_next;
	}
	// info->uls_name = mx_strdup("uls: ");
}

void mx_get_error_for_R(t_main *info, t_catalog* cat) {
	char *error;

	if(errno == 0) {
		// mx_get_dir_data_from_dir(cat);
		
	}
	else {
		error = mx_strjoin(info->uls_name, cat->c_name);
		perror(error);
		mx_strdel(&error);
		errno = 0;
	}
}

void mx_r_flag(t_main *info, t_catalog *cat, char *link) {
	DIR *directoy = opendir(cat->c_name);
	t_dir_data *list;
	struct dirent *temp = NULL;
	int am_of_dir = 0;
	
	cat->dir_data = (t_dir_data *)malloc(sizeof(t_dir_data));
	list = cat->dir_data;
	cat->c_info = NULL;
	if(directoy == NULL) {
		if(errno != 0) {
			mx_printstr(cat->c_name);
			mx_printstr(":\n\n");
		}
		mx_get_error_for_R(info, cat);
		return;
	}
	if (directoy) {
		temp = readdir(directoy);
		temp = readdir(directoy);
		cat->am_data += 2;
	}
	if (directoy && (temp = readdir(directoy))) {
		list->is_dir = temp->d_type == 4;
		list->data = temp;
		list->name = mx_strdup(temp->d_name);
		list->path = mx_get_full_path(link, list->name);
		if (info->flag.is_l == true)
			mx_ladd_to_tdir(list, cat, info->flag);
		list->next = NULL;
		cat->am_data++;
		list->is_dir && cat->am_data > 2 ? am_of_dir++ : 0;
	}

	while (directoy && (temp = readdir(directoy))) {
		if (*temp->d_name == '.')
			continue;
		list->next = (t_dir_data *)malloc(sizeof(t_dir_data));
		list = list->next;
		list->is_dir = temp->d_type == 4;
		list->data = temp;
		list->name = mx_strdup(temp->d_name);
		list->path = mx_get_full_path(link, list->name);
		if (info->flag.is_l == true)
			mx_ladd_to_tdir(list, cat, info->flag);
		list->next = NULL;
		cat->am_data++;
		list->is_dir && cat->am_data > 2 ? am_of_dir++ : 0;
	}
	// mx_get_dir_data_from_dir(cat);
	if (am_of_dir != 0) {
		cat->c_info = (t_main *)malloc(sizeof(t_main));
		cat->c_info->am_dir = am_of_dir;
		cat->c_info->flag = info->flag;
		cat->c_info->uls_name = info->uls_name;
		cat->c_info->cat = NULL;
		cat->c_info->am_dir > 0 ? mx_init_local_info(cat->dir_data, cat->c_info, link) : (void)0;
		mx_sort_cat_list(cat->c_info->cat, info->flag);
	}
	else
		cat->c_info = NULL;
	printf("[][[][][][][%p]\n", (void*)cat->c_next);

		mx_sort_dir_list(cat->dir_data, info->flag);
		mx_printstr(cat->c_name);
		mx_printstr(":\n");
		mx_print_1(cat, info->flag.is_a);
		mx_printchar('\n');

		

	//*************************************
	t_catalog *tmp = cat->c_info ? cat->c_info->cat : NULL;
	
	for (; tmp && cat->c_info->am_dir != 0; tmp = tmp->c_next) {

// mx_sort_dir_list(cat->dir, info->flag);
		// mx_printstr(cat->c_name);
		// mx_printstr(":\n");
		// mx_print_1(cat, true);
		// mx_printchar('\n');

		errno = 0;
		mx_r_flag(cat->c_info, tmp, tmp->c_name);
		// if (errno == 0)
		// 	mx_sort_dir_list(cat->dir, info->flag);
		// mx_printstr(tmp->c_name);
		// mx_printstr(":\n");
		// // printf("{}{}{}}{}  %s\n", tmp->dir->name);
		// mx_print_1(tmp, true);
		
	}
	//***************************************

	// mx_closedir_info(info, directoy, link);
	closedir(directoy);
}

// void mx_r_flag(t_main *info, t_catalog *cat, char *link) {
// 	DIR *directoy = opendir(cat->c_name);
// 	t_dir_data *list = cat->dir;
// 	struct dirent *temp = NULL;
// 	int am_of_dir = 0;
	
// 	cat->c_info = NULL;
// 	if(directoy == NULL) {
// 		if(errno != 0) {
// 			mx_printstr(cat->c_name);
// 			mx_printstr(":\n\n");
// 		}
// 		mx_get_error_for_R(info, cat);
// 		return;
// 	}
// 	if (directoy && (temp = readdir(directoy))) {
// 		list->data = temp;
// 		list->name = mx_strdup(list->data->d_name);
// 		list->path = mx_get_full_path(cat->c_name, list->name);
// 		if (info->flag.is_l == true)
// 			mx_ladd_to_tdir(list, cat, info->flag);
// 		list->next = NULL;
// 		cat->am_data++;
// 	}
// 	while (directoy && (temp = readdir(directoy))) {
// 		list->next = (t_dir_data *)malloc(sizeof(t_dir_data));
// 		list = list->next;
// 		list->is_dir = temp->d_type == 4;
// 		list->data = temp;
// 		list->name = mx_strdup(temp->d_name);
// 		list->path = mx_get_full_path(link, list->name);
// 		if (info->flag.is_l == true)
// 			mx_ladd_to_tdir(list, cat, info->flag);
// 		list->next = NULL;
// 		cat->am_data++;
// 		list->is_dir && cat->am_data > 2 ? am_of_dir++ : 0;
// 	}
// 	mx_get_dir_data_from_dir(cat);
// 	if (am_of_dir != 0) {
// 		cat->c_info = (t_main *)malloc(sizeof(t_main));
// 		cat->c_info->am_dir = am_of_dir;
// 		cat->c_info->flag = info->flag;
// 		cat->c_info->uls_name = info->uls_name;
// 		cat->c_info->cat = NULL;
// 		cat->c_info->am_dir > 0 ? mx_init_local_info(cat->dir->next->next, cat->c_info, link) : (void)0;
// 		mx_sort_cat_list(cat->c_info->cat, info->flag);
// 	}
// 	else
// 		cat->c_info = NULL;

// 		mx_sort_dir_list(cat->dir, info->flag);
// 		mx_printstr(cat->c_name);
// 		mx_printstr(":\n");
// 		mx_print_1(cat, true);
// 		mx_printchar('\n');

		

// 	//*************************************
// 	t_catalog *tmp = cat->c_info ? cat->c_info->cat : NULL;
	
// 	for (; tmp && cat->c_info->am_dir != 0; tmp = tmp->c_next) {

// // mx_sort_dir_list(cat->dir, info->flag);
// 		// mx_printstr(cat->c_name);
// 		// mx_printstr(":\n");
// 		// mx_print_1(cat, true);
// 		// mx_printchar('\n');

// 		errno = 0;
// 		mx_r_flag(cat->c_info, tmp, tmp->c_name);
// 		// if (errno == 0)
// 		// 	mx_sort_dir_list(cat->dir, info->flag);
// 		// mx_printstr(tmp->c_name);
// 		// mx_printstr(":\n");
// 		// // printf("{}{}{}}{}  %s\n", tmp->dir->name);
// 		// mx_print_1(tmp, true);
		
// 	}
// 	//***************************************

// 	// mx_closedir_info(info, directoy, link);
// 	closedir(directoy);
// }

