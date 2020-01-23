#ifndef ULS_H
#define ULS_H

#include <dirent.h>
#include <errno.h>
#include <sys/ioctl.h>
#include "libmx.h"

typedef struct s_dir_data {
	struct dirent *data;
	char *name;
	struct s_dir_data *next;
} t_dir_data;

typedef struct s_main {
	t_dir_data *dir;
	t_dir_data *dir_data;
	char *uls_name; // add char that keep "uls: "
	int am_dir;
	int *am_data;
	int *lines_for_print;
} t_main;

#endif
