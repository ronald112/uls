#include "uls.h"

void mx_add_xatr(char *path, char **result, int *indent) {
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

void mx_print_ifdog(char *path, char **result) {
    char xattr_name[1024] = "\0";
    ssize_t xattr = listxattr(path, xattr_name, 1024, XATTR_NOFOLLOW);
    int nmb = getxattr(path, xattr_name, NULL, 0, 1, XATTR_NOFOLLOW);

    if (xattr > 0) {
        char *temp = mx_itoa(nmb);
// printf("debug %d\n", mx_get_nmb_digits_int(nmb));
        *result = mx_addstr(*result, "\n\t");
        *result = mx_addstr(*result, xattr_name);
        *result = mx_addstr(*result, "\t");
        for (int i = mx_get_nmb_digits_int(nmb); i < 4; ++i,
        *result = mx_addstr(*result, " "));
        *result = mx_addstr(*result, temp);
        *result = mx_addstr(*result, " ");
        mx_strdel(&temp);
    }
}

