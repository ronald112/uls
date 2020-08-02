#include "uls.h"

void mx_add_xatr(char *path, char **result) {
    ssize_t xattr = listxattr(path, NULL, 0, XATTR_NOFOLLOW);
    acl_t acl = acl_get_file(path, ACL_TYPE_EXTENDED);

    if (xattr > 0)
        *result = mx_addstr(*result, "@");
    else if (acl == NULL)
        *result = mx_addstr(*result, " ");
    else
        *result = mx_addstr(*result, "+");
    acl_free(acl);
    acl = NULL;
}

static void get_xattr_vallen(char **res, char *tmp, long long size, bool flag) {
    for (int i = mx_strlen(tmp); i < size; ++i)
        *res = mx_addstr(*res, " ");
    *res = mx_addstr(*res, tmp);
    if (flag == true)
        *res = mx_addstr(*res, "B");
    *res = mx_addstr(*res, " ");
}

void mx_print_ifdog(char *path, char **result, long long size, bool flag) {
    ssize_t xattr_len = listxattr(path, NULL, 0, XATTR_NOFOLLOW);
    char *xattr_name = mx_strnew(xattr_len);
    xattr_len = listxattr(path, xattr_name, xattr_len, XATTR_NOFOLLOW);
    int vallen = 0;
    char *temp = NULL;
    char *key = xattr_name;

    while (xattr_len > 0) {
        *result = mx_addstr(*result, "\n\t");
        *result = mx_addstr(*result, key);
        *result = mx_addstr(*result, "\t");
        vallen = getxattr(path, key, NULL, 0, 1, XATTR_NOFOLLOW);
        temp = mx_itoa(vallen);
        get_xattr_vallen(result, temp, size, flag);
        mx_strdel(&temp);
        xattr_len -= mx_strlen(key) + 1;
        key += mx_strlen(key) + 1;
    }
    mx_strdel(&xattr_name);
}
