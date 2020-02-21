#include "uls.h"

void mx_add_minor_major(char **result, dev_t dev, int max_digits) {
    char *nmb = mx_itoa(MX_MAJOR(dev));
    int nmb_delims = max_digits - mx_get_nmb_digits(MX_MINOR(dev));
    char *temp = mx_itoa(mx_get_nmb_digits(MX_MINOR(dev)));

    *result = mx_addstr(*result, " ");
    *result = mx_addstr(*result, temp);
    mx_strdel(&temp);
    *result = mx_addstr(*result, " ");
    *result = mx_addstr(*result, nmb);
    mx_strdel(&nmb);
    if (MX_MINOR(dev) > 255) {
        nmb = mx_get_hex_view(MX_MINOR(dev));
        *result = mx_addstr(*result, ", ");
    }
    else {
        nmb = mx_itoa(MX_MINOR(dev));
        *result = mx_addstr(*result, ", ");
        for (; nmb_delims > 0; nmb_delims--, *result = mx_addstr(*result, " "));
    }
    *result = mx_addstr(*result, nmb);
    mx_strdel(&nmb);
}
