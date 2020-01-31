#include "uls.h"

void mx_ladd_to_tdir(t_dir_data *list, t_catalog *cat) {
    list->buff_stat = (struct stat *)malloc(sizeof(struct stat));
    lstat(list->path, list->buff_stat);
    cat->size_of_block += list->buff_stat->st_blocks;

}
