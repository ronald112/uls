#ifndef ULS_H
#define ULS_H

#include <dirent.h>
#include <errno.h>
#include <sys/ioctl.h>
#include "libmx.h"



typedef struct s_dir_data {
    struct dirent *data;    // информация про файл/папку дирента
    char *name;             // имя файла или папки
    struct s_dir_data *next;// следующий файл/папка
} t_dir_data;

typedef struct s_catalog {
    // bool is_work;
    char *c_name;           // имя каталога
    t_dir_data *dir;        // все файлы в дир (1)
    t_dir_data *dir_data;   // файлы без . и .. (2)
    int am_files;           // количество (2)
    int am_data;            // количество (1)
    int lines_for_print;    // линии для принтинга
    int max_length;
    struct s_catalog *c_next;
} t_catalog;

typedef struct s_flag {
	bool is_a;
	bool is_l;
	bool is_C;
	bool is_1;
} t_flag;

typedef struct s_main {     //** структура, которая хранит массивом все каталоги, взятые из аргумента
    int am_dir;             // количество каталогов из аргумента
    char *uls_name;         // add char that keeps "uls: "
    t_catalog *cat;         // массив каталогов (директорик из аргумента)
    t_flag flag;
} t_main;

void mx_set_flags_false(t_flag flags);
void mx_main_parse_fnc(int argc, char **argv, t_main *info);

#endif
