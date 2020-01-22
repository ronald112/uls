#include "uls.h"

DIR *mx_opendir_info(t_main *info, char *link) {//-----------
    DIR *dir;

    if ((dir = opendir(link)) == NULL) {
        char *temp = mx_strjoin(info->uls_name, link);

        errno = ENOENT;
        perror(temp);
        exit(1);
    }
    else {
        return dir;
    }
}

// check if valid close
void mx_closedir_info(t_main *info, DIR *dir, char *link) {
    if (closedir(dir) < 0) {
        char *temp = mx_strjoin(info->uls_name, link);

        errno = EBADF;
        perror(temp);
        exit(1);
    }
}

t_dir_data *mx_get_data_list(t_main *info, int i, char *link) {//-----------
	DIR *directoy = mx_opendir_info(info, link);
	t_dir_data *list = info->cat[i].dir;
	struct dirent *temp = NULL;

	if ((temp = readdir(directoy))) {
		list->data = temp;
		list->name = mx_strdup(temp->d_name);
		list->next = NULL;
		info->cat[i].am_data++;
	}
	while ((temp = readdir(directoy))) {
		list->next = (t_dir_data*)malloc(sizeof(t_dir_data));
		list = list->next;
		list->data = temp;
		list->name = mx_strdup(temp->d_name);
		list->next = NULL;
		info->cat[i].am_data++;
	}
	mx_closedir_info(info, directoy, link);
	return info->cat[i].dir;
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
	int max_length;
	int max_col;

	ioctl(0, TIOCGWINSZ, &w);
	for (int i = 0; i < info->am_dir; ++i) { 						// проделываем для каждой дир, указан. в аргументах
		info->cat[i].lines_for_print = 0; 								// обнуляем количество линий для дир
		max_length = get_max_length(info->cat[i].dir_data);				// находим макимально возможную длину названия файла в дир
		max_col = (w.ws_col/(8 - (max_length % 8) + max_length));	// высчитываем количество колонок
		printf("%d\n", max_col);
		info->cat[i].lines_for_print = info->cat[i].am_dir_data / max_col;			// высчитвыаем количество линий
		if(info->cat[i].am_dir_data % max_col != 0)							// доп проверка на линии
			info->cat[i].lines_for_print++;
		printf("%d\n", info->cat[i].lines_for_print);
	}
}

//=============================================================================

void mx_print_default(t_catalog *cat, int kol) {
	t_dir_data *list = cat->dir_data;

	for (int i = 0; i < kol; i++, list = cat[i].dir_data) {
		while (list) {
			mx_printstr(list->name);
			mx_printstr("\t");
			list = list->next;
		}
	}
	mx_printchar('\n');
}

//=============================================================================
void mx_init_info(t_main *info, int argc) { 						// инициализация инфо
	info->am_dir = argc == 1 ? 1 : argc - 1;
	info->cat = (t_catalog*)malloc(sizeof(t_catalog) * info->am_dir); // инициализация массива каталогов
	for (int i = 0; i < info->am_dir; ++i) {
		info->cat[i].am_data = 0;
		info->cat[i].am_dir_data = 0;
		info->cat[i].dir = (t_dir_data*)malloc(sizeof(t_dir_data));
		info->cat[i].dir_data = (t_dir_data*)malloc(sizeof(t_dir_data));
	}
	info->uls_name = strdup("uls: ");
}

void mx_swap(t_dir_data *a, t_dir_data *b) { 
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
				mx_swap(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
}
//=============================================================================

int main(int argc, char *argv[]) {
	t_main *info = (t_main*)malloc(sizeof(t_main));

	mx_init_info(info, argc);
	for (int i = 0; i < info->am_dir; i++) {
		if (argc > 1)
			mx_get_data_list(info, i, argv[i + 1]);
		else if (argc == 1)
			mx_get_data_list(info, i, ".");
		mx_sort_dir_list(info->cat[i].dir);
		if (info->cat[i].dir->next->next) {
			info->cat[i].dir_data->data = info->cat[i].dir->next->next->data;
			info->cat[i].dir_data->name = info->cat[i].dir->next->next->name;
			info->cat[i].dir_data->next = info->cat[i].dir->next->next->next;
			info->cat[i].am_dir_data = info->cat[i].am_data;
		}
	}
	mx_count_line_for_print(info);//*******************************************
	mx_print_default(info->cat, info->am_dir);//-----------info----------------
	// system("leaks -q uls");
	// system("ls");
	return 0;
}
