#include "uls.h"

static void chk_line_for_flags(char *argv, t_main *info) {
    printf("%s\n",argv[0]);
}

void mx_main_parse_fnc(int argc, char **argv, t_main *info) {
    if (argc < 2)
        mx_set_flags_false(info->flag);
    else {
        while (*argv) {
            if (*argv[0] != "-")
                break;
            chk_line_for_flags(argv, info);


        }
    }
}
