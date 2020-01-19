#ifndef ULS_H
#define ULS_H

#include <dirent.h>
#include <errno.h>
#include "libmx.h"

typedef struct s_dir_data {
	struct dirent *data;
	char *name;
	struct s_dir_data *next;
} t_dir_data;

#endif
