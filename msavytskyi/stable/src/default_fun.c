#include "uls.h"

t_dir_data *mx_get_data_list(t_main *info, int i, char *link) {//-----------
	DIR *directoy = opendir(link);
	t_dir_data *list = &(info->dir[i]);
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
	return &(info->dir[i]);
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

int mx_count_line_for_print(t_main *info) {
	struct winsize w;
	int max_length;
	int max_col;

	ioctl(0, TIOCGWINSZ, &w);
	for (int i = 0; i < info->am_dir; ++i) { 						// проделываем для каждой дир, указан. в аргументах
		info->lines_for_print[i] = 0; 								// обнуляем количество линий для дир
		max_length = get_max_length(&(info->dir[i]));				// находим макимально возможную длину названия файла в дир
		max_col = (w.ws_col/(8 - (max_length % 8) + max_length));	// высчитываем количество колонок
		printf("%d\n", max_col);
		info->lines_for_print[i] = info->am_data[i] / max_col;			// высчитвыаем количество линий
		if(info->am_data[i] % max_col != 0)							// доп проверка на линии
			info->lines_for_print[i]++;
		printf("%d\n", info->lines_for_print[i]);
	}

}

//=============================================================================

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

void mx_init_info(t_main *info) // инициализация инфо

int main(int argc, char *argv[]) {
	t_main *info = (t_main*)malloc(sizeof(t_main));

	info->am_dir = argc == 1 ? 1 : argc - 1;//----------info->am_dir-----------
	info->dir = (t_dir_data*)malloc(sizeof(t_dir_data) * info->am_dir);//------
	for (int i = 0; i < info->am_dir; i++) {//----------info->am_dir-----------
		if (argc > 1)
			mx_get_data_list(info, i, argv[i + 1]);//-------info->dir-----
		else if (argc == 1)
			mx_get_data_list(info, i, ".");//--------info->dir------------
	}
	mx_count_line_for_print(info);//*******************************************
	mx_print_default(info->dir, info->am_dir);//-----------info----------------
	system("leaks -q uls");
	// system("ls");
	return 0;
}
