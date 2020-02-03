#include "uls.h"

void mx_add_grp(uid_t uid, char **result) {
    struct passwd *pwd = NULL;

    if ((pwd = getpwuid(uid)) != NULL)
        *result = mx_addstr(*result, pwd->pw_name);
    *result = mx_addstr(*result, " ");
    //else
        //printf(" %-8d", id);
}

void mx_add_pwd(gid_t gid, char **result) {
    struct group *grp = NULL;

    if ((grp = getgrgid(gid)) != NULL)
        *result = mx_addstr(*result, grp->gr_name);
    *result = mx_addstr(*result, " ");
}
