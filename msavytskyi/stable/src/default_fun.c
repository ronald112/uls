#include "uls.h"

t_dir_data *mx_get_data_list(t_dir_data *dir, char *link) {
	DIR *directoy = opendir(link);
	t_dir_data *list = dir;
	struct dirent *temp = NULL;

	if ((temp = readdir(directoy))) {
		list->data = temp;
		list->name = mx_strdup(temp->d_name);
		list->next = NULL;
	}
	while ((temp = readdir(directoy))) {
		list->next = (t_dir_data*)malloc(sizeof(t_dir_data));
		list = list->next;
		list->data = temp;
		list->name = mx_strdup(temp->d_name);
		list->next = NULL;
	}
	closedir(directoy);
	return dir;
}

// int mx_count_line_for_print(t_dir_data *)

void mx_print_default(t_dir_data *dir, int kol) {
	t_dir_data *list = dir;

	for (int i = 0; i < kol; i++, list = &dir[i]) {
		while (list) {
			mx_printstr(list->name);
			mx_printstr("\t");
			list = list->next;
		}
	}
	mx_printchar('\n');
}

int main(int argc, char *argv[]) {
	int am_dir = argc == 1 ? 1 : argc - 1;
	t_main *info = (t_main*)malloc(sizeof(t_main));

	info->dir = (t_dir_data*)malloc(sizeof(t_dir_data) * am_dir);
	for (int i = 0; i < am_dir; i++) {
		if (argc > 1)
			mx_get_data_list(&(info->dir[i]), argv[i + 1]);
		else if (argc == 1)
			mx_get_data_list(&(info->dir[i]), ".");
	}
	mx_print_default(info->dir, am_dir);
	system("leaks -q uls");
	// system("ls");
	return 0;
}
