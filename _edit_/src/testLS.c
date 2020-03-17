#include "uls.h"

char *mx_default(char *directory, int amount) {
	DIR *direct = opendir(directory);
	struct dirent *dir_read = NULL;
	char *flag_1 = NULL;

	if (amount > 0) {
		flag_1 = mx_strjoin(flag_1, directory);
		flag_1 = mx_strjoin(flag_1, ":\n");
	}
	while ((dir_read = readdir(direct)) != NULL) {
		if(mx_strcmp(dir_read->d_name, ".")
			&& mx_strcmp(dir_read->d_name, "..")){
			flag_1 = mx_strjoin(flag_1, dir_read->d_name);
			flag_1 = mx_strjoin(flag_1, "\t");
		}
	}
	closedir(direct);
	return flag_1;
}
