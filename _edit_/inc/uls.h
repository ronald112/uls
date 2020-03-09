#ifndef ULS_H
#define ULS_H

#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/acl.h>
#include <sys/xattr.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include "libmx.h"

#define MX_FILE_WS 81
#define MX_MINORBITS 24
#define MX_MINORMASK ((1U << MX_MINORBITS) - 1)
#define MX_MAJOR(dev) ((unsigned int) ((dev) >> MX_MINORBITS))
#define MX_MINOR(dev) ((unsigned int) ((dev) & MX_MINORMASK))

typedef struct s_dir_data {
    struct dirent *data;    // информация про файл/папку дирента
    int min_lnght_namedir;
    int min_lnght_grpdir;
    bool is_dir;
    char *name;             // имя файла или папки
    char *path;             // path to the file/dir
    struct stat *buff_stat; // stat buff
    struct s_dir_data *next;// следующий файл/папка
} t_dir_data;

typedef struct s_main t_main;

typedef struct s_catalog {
    t_main *c_info;
    blkcnt_t size_of_block;   // size of file/dir
    char *R_name;
    int max_lnght_namedir;
    int max_lnght_grpdir;
    long long max_size_ofdir;
    long long max_size_oflink;
    int lng_max_minor;
    int lng_max_major;
    bool is_dir;
    bool is_char_block;
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
    bool is_dog;
    bool is_h;
    bool is_f;
    bool is_R;
    bool is_A;
	bool is_a;
	bool is_l;
	bool is_C;
	bool is_1;
    bool is_tofile;
} t_flag;

typedef struct s_main {     //** структура, которая хранит массивом все каталоги, взятые из аргумента
    int am_dir;             // количество каталогов из аргумента
    char *uls_name;         // add char that keeps "uls: "
    t_catalog *cat;         // массив каталогов (директорик из аргумента)
    t_flag flag;
} t_main;

void mx_r_flag(t_main *info, t_catalog *cat, char *link);
void mx_r_flag_a(t_main *info, t_catalog *cat, char *link);

void mx_print_1(t_catalog *cat, bool a);
void mx_print_R(t_main *info, t_catalog *head);

void mx_get_dir_data_from_dir(t_catalog *head);
void mx_sort_cat_list(t_catalog *start, t_flag flag);
void mx_sort_dir_list(t_dir_data *dir, t_flag flag);

t_catalog *mx_main_parse_fnc(int *argc, char **argv, t_main *info);
void mx_set_flags_false(t_main *info);
t_catalog *mx_create_list_of_catalog(int amount);
void mx_init_info(char **argv, t_main *info);
void mx_print_lflag(t_catalog *catalog, t_flag flags);
char *mx_get_full_path(char *name, char *path);
void mx_ladd_to_tdir(t_dir_data *list, t_catalog *cat, t_flag flag);
char *mx_get_permissions(mode_t mode);

void mx_print_totalsize(t_catalog *cat);
void mx_add_xatr(char *path, char **result);
void mx_add_links(nlink_t link, t_catalog *cat, char **result);
void mx_add_pwd(t_dir_data *dir, t_catalog *cat, char **result);
void mx_add_grp(t_dir_data *dir, t_catalog *cat, char **result);
void mx_add_filesize(off_t size, t_catalog *cat, char **result, bool flag);
void mx_add_lastchange_time(time_t time, char **result);
void mx_add_hardlink(char *path, char **result);
void mx_add_minor_major(char **result, dev_t dev, t_catalog *cat);
void mx_add_indens_minor_major(t_catalog *cat, t_dir_data *list);
char *mx_change_size_h(off_t size);
void mx_print_ifdog(char *path, char **result, long long size, bool flag);

long long mx_get_remainder(long long nmb, long long divider,
                           long long accur);
int mx_get_nmb_digits_int(long long nmb);
long long mx_get_nmb_digits_ll(long long nmb);
char *mx_get_hex_view(int nmb);

#endif
