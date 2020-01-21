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
} t_main;

#endif
