#include "uls.h"

static void chk_l1Cf_flags(char c, t_main *info) {
    if (c == 'l') {
        info->flag.is_l = true;
        info->flag.is_1 = false;
        info->flag.is_C = false;
    }
    else if (c == '1') {
        info->flag.is_l = false;
        info->flag.is_1 = true;
        info->flag.is_C = false;
    }
    else if (c == 'C') {
        info->flag.is_l = false;
        info->flag.is_1 = false;
        info->flag.is_C = true;
    }
    else if (c == 'f') {
        info->flag.is_f = true;
        info->flag.is_a = true;
        info->flag.is_dog = true;
        info->flag.is_1 = false;
    }
}

static void chk_line_for_flags(char *argv, t_main *info) {
    for (int i = 0; argv[i] != '\0'; ++i) {
        chk_l1Cf_flags(argv[i], info);
        if (argv[i] == 'a') {
            info->flag.is_a = true;
            info->flag.is_A = false;
        }
        else if (argv[i] == 'A')
            info->flag.is_A = true;
        if (argv[i] == 'R')
            info->flag.is_R = true;
        if (argv[i] == 'h')
            info->flag.is_h = true;
        if (argv[i] == '@')
            info->flag.is_dog = true;
    }
}

t_catalog *mx_main_parse_fnc(int *argc, char **argv, t_main *info) {
    argv++;
    mx_set_flags_false(info);
    if (*argc > 1) {
        while (*argv) {
            if (*argv[0] != '-')
                break;
            chk_line_for_flags(*argv, info);
            argv++;
            (*argc)--;
        }
    }
    info->am_dir = *argc == 1 ? 1 : *argc - 1;
    info->uls_name = mx_strdup("uls: ");
    mx_init_info(argv, info);
    return info->cat;
}
