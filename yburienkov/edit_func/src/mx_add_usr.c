#include "uls.h"

void mx_add_pwd(uid_t uid, char **result) {
    struct passwd *pwd = NULL;

    if ((pwd = getpwuid(uid)) != NULL)
        *result = mx_addstr(*result, pwd->pw_name);
    *result = mx_addstr(*result, "  ");
}

void mx_add_grp(gid_t gid, char **result) {
    struct group *grp = NULL;

    if ((grp = getgrgid(gid)) != NULL)
        *result = mx_addstr(*result, grp->gr_name);
    else {
        char *temp = mx_itoa(gid);

        *result = mx_addstr(*result, temp);
        mx_strdel(&temp);
    }
    *result = mx_addstr(*result, " ");
}
