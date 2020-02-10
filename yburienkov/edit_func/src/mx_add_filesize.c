#include "uls.h"

void mx_add_filesize(off_t size, char **result) {
    char *temp = mx_ltoa(size);

    *result = mx_addstr(*result, temp);
    mx_strdel(&temp);
}
