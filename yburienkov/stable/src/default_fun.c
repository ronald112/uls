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

	if (closedir(directoy) < 0) {
		errno = EBADF;
		perror ("Program Error Test");
	}
	return dir;
}

void mx_print_default(t_dir_data *dir, int kol) {
	t_dir_data *list = dir;

	for (int i = 0; i < kol; i++, list = &dir[i]) {
		while (list) {
			mx_printstr(list->name);
			mx_printstr("\t");
			list = list->next;
		}
	}
}

int main(int argc, char *argv[]) {
	int am_dir = argc == 1 ? 1 : argc - 1;
	t_main *vars;
	vars->dir_data = (t_dir_data*)malloc(sizeof(t_dir_data) * am_dir);
	for (int i = 0; i < am_dir; ++i)
		dir[i].name = NULL;
	// t_dir_data dir[am_dir];
	for (int i = 0; i < am_dir; i++) {
		if (argc > 1)
			mx_get_data_list(&dir[i], argv[i + 1]);
		else if (argc == 1)
			mx_get_data_list(&dir[i], ".");
	}

	mx_printstr(dir->name);
	// printf("%d %s\n", am_dir, win);
	mx_print_default(dir, am_dir);
	system("leaks -q uls");
	// system("ls");
	return EXIT_SUCCESS;
}

// e2r2p4% ls .
// Makefile	inc		libmx		src		uls		uls.txt
// e2r2p4% ./uls .
// ..	..	inc	libmx	Makefile	src	uls	uls.txt
