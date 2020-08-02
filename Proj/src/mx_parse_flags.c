#include "uls.h"

static void print_usage(bool chk_flag, char illegel_opt) {
    if (chk_flag == 0) {
        mx_printerr("uls: illegal option -- ");
        mx_printerr(&illegel_opt);
        mx_printerr("\nusage: uls [-@ACRafhl1] [file ...]\n");
        exit(1);
    }
}

static bool chk_l1C_flags(char c, t_main *info) {
    bool chk_flag = 0;

    if ((c == 'l') && (chk_flag = 1)) {
        info->flag.is_l = true;
        info->flag.is_1 = false;
        info->flag.is_C = false;
    }
    else if ((c == '1') && (chk_flag = 1)) {
        info->flag.is_l = false;
        info->flag.is_1 = true;
        info->flag.is_C = false;
    }
    else if ((c == 'C') && (chk_flag = 1)) {
        info->flag.is_l = false;
        info->flag.is_1 = false;
        info->flag.is_C = true;
    }
    return chk_flag;
}

static bool chk_ARaf_flag(char c, t_main *info, bool chk_l1C) {
    bool chk_flag = chk_l1C;

    if ((c == 'a') && (chk_flag = 1)) {
        info->flag.is_a = true;
        info->flag.is_A = false;
    }
    else if ((c == 'A') && (chk_flag = 1))
        info->flag.is_A = true;
    if ((c == 'R') && (chk_flag = 1))
        info->flag.is_R = true;
    if ((c == 'f') && (chk_flag = 1)) {
        info->flag.is_f = true;
        info->flag.is_a = true;
        info->flag.is_C = false;
    }
    return chk_flag;
}

 // n, B, v
static void chk_line_for_flags(char *argv, t_main *info) {
    for (int i = 1; argv[i] != '\0'; ++i) {
        bool chk_flag = chk_l1C_flags(argv[i], info);

        chk_flag = chk_ARaf_flag(argv[i], info, chk_flag);
        if ((info->flag.is_l == true) && (argv[i] == 'h') && (chk_flag = 1))
            info->flag.is_h = true;
        if ((info->flag.is_l == true) && (argv[i] == '@') && (chk_flag = 1))
            info->flag.is_dog = true;
        print_usage(chk_flag, argv[i]);
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
