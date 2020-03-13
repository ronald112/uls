#include "uls.h"

bool mx_print_error_R(t_main *info, t_catalog *cat, DIR *directoy) {
	cat->c_info = NULL;
	if(directoy == NULL) {
		if(errno != 0) {
			mx_printchar('\n');
			mx_printstr(cat->c_name);
			mx_printstr(":\n");
		}
		mx_get_error_for_R(info, cat);
		return true;
	}
	return false;
}

void mx_setting_param_R(t_main *info, t_dir_data *list, t_catalog *cat,
	char *link, struct dirent *temp) {
	list->data = temp;
	list->name = mx_strdup(temp->d_name);
	list->path = mx_get_full_path(link, list->name);
	if (info->flag.is_l == true)
		mx_ladd_to_tdir(list, cat, info->flag);
	list->next = NULL;
	info->flag.is_a ? cat->am_data++ : cat->am_files++;
}

void mx_setting_cinfo_R(t_main *info, t_catalog *cat, t_dir_data *for_init,
	int am_of_dir, char *link) {
	cat->c_info = (t_main *)malloc(sizeof(t_main));
	cat->c_info->am_dir = am_of_dir;
	cat->c_info->flag = info->flag;
	cat->c_info->uls_name = info->uls_name;
	cat->c_info->cat = NULL;
	if (cat->c_info->am_dir > 0)
		info->flag.is_a ? mx_init_local_info_a(for_init, cat->c_info, link)
		: mx_init_local_info(for_init, cat->c_info, link);
	mx_sort_cat_list(cat->c_info->cat, info->flag);
}
