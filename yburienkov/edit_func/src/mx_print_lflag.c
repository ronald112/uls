#include "uls.h"

static char *get_info(t_dir_data *dir, t_catalog *cat) {
    char *result = mx_get_permissions(dir->buff_stat->st_mode, dir->path);

    mx_add_xatr(dir->path, &result);
    mx_add_links(dir->buff_stat->st_nlink, cat, &result);
    mx_add_pwd(dir, cat, &result);
    mx_add_grp(dir, cat, &result);
    if (dir->buff_stat->st_rdev)
        mx_add_minor_major(&result, dir->buff_stat->st_rdev, cat->lng_max_minor);
    else
        mx_add_filesize(dir->buff_stat->st_size, cat, &result);
    //printf("debug filesize\n");
    mx_add_lastchange_time(dir->buff_stat->st_mtimespec.tv_sec, &result);
    //printf("debug time\n");
    result = mx_addstr(result, dir->name);
    //printf("debug name\n");
    mx_add_hardlink(dir->path, &result);
    return result;
}
/*
crw-------  1 root        wheel      19,   1 Feb 19 03:33 afsc_type5
crw-------  1 root        wheel      10,   0 Feb 19 03:33 auditpipe
crw-r--r--  1 root        wheel       9,   3 Feb 19 03:33 auditsessions
crw-------  1 root        wheel      20,   0 Feb 19 03:33 autofs
crw-------  1 root        wheel      32,   0 Feb 19 03:33 autofs_control
crw-rw-rw-  1 root        wheel      31,  42 Feb 19 03:33 autofs_homedirmounter
crw-rw-rw-  1 root        wheel      22,  42 Feb 19 03:33 autofs_notrigger
crw-rw-rw-  1 root        wheel      21, 0x00000470 Feb 19 03:33 autofs_nowait
crw-------  1 root        wheel      23,   0 Feb 19 03:33 bpf0
crw-------  1 root        wheel      23,   1 Feb 19 03:33 bpf1
crw-------  1 root        wheel      23,   2 Feb 19 03:33 bpf2
crw-------  1 root        wheel      23,   3 Feb 19 03:33 bpf3
crw-------  1 ronald1121  staff       0,   0 Feb 19 03:34 console
crw-rw-rw-  1 root        wheel      18,   1 Feb 19 03:33 cu.Bluetooth-Incoming-Port

crw-------  1 root        wheel     19, 1  Feb 19 03:33 afsc_type5
crw-------  1 root        wheel     10, 0  Feb 19 03:33 auditpipe
crw-r--r--  1 root        wheel     9, 3  Feb 19 03:33 auditsessions
crw-------  1 root        wheel     20, 0  Feb 19 03:33 autofs
crw-------  1 root        wheel     32, 0  Feb 19 03:33 autofs_control
crw-rw-rw-  1 root        wheel     31, 76  Feb 19 03:33 autofs_homedirmounter
crw-rw-rw-  1 root        wheel     22, 76  Feb 19 03:33 autofs_notrigger
crw-rw-rw-  1 root        wheel     21, 530  Feb 19 03:33 autofs_nowait
crw-------  1 root        wheel     23, 0  Feb 19 03:33 bpf0
crw-------  1 root        wheel     23, 1  Feb 19 03:33 bpf1
crw-------  1 root        wheel     23, 2  Feb 19 03:33 bpf2
crw-------  1 root        wheel     23, 3  Feb 19 03:33 bpf3


*/
void mx_print_lflag(t_catalog *cat, t_flag flags) {
    char *temp = NULL;
    long long tmp_ds = cat->max_size_ofdir;
    long long tmp_ls = cat->max_size_oflink;

    for (cat->max_size_ofdir = 0; tmp_ds != 0;
    tmp_ds /= 10, cat->max_size_ofdir++);
    for (cat->max_size_oflink = 0; tmp_ls != 0;
    tmp_ls /= 10, cat->max_size_oflink++);
    for (t_dir_data *dir = cat->dir; dir; dir = dir->next) {
        if (flags.is_a == false && dir->name[0] != '.') {
            temp = get_info(dir, cat);
            mx_printstr(temp);
            mx_strdel(&temp);
            mx_printstr("\n");
        }
        else if (flags.is_a == true) {
            temp = get_info(dir, cat);
            mx_printstr(temp);
            mx_strdel(&temp);
            mx_printstr("\n");
        }
    }
}
