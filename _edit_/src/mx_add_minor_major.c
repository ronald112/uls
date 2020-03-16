#include "uls.h"

static void set_minor(char *nmb, char **result, dev_t dev, t_catalog *cat) {
    int nmb_delims_todo = cat->lng_max_minor
                          - mx_get_nmb_digits_int(MX_MINOR(dev));

    if (MX_MINOR(dev) > 255) {
        nmb = mx_get_hex_view(MX_MINOR(dev));
        *result = mx_addstr(*result, ", ");
    }
    else {
        nmb = mx_itoa(MX_MINOR(dev));
        *result = mx_addstr(*result, ", ");
        for (; nmb_delims_todo > 0; nmb_delims_todo--)
            *result = mx_addstr(*result, " ");
    }
    *result = mx_addstr(*result, nmb);
    mx_strdel(&nmb);
}

void mx_add_minor_major(char **result, dev_t dev, t_catalog *cat) {
    char *nmb = mx_itoa(MX_MAJOR(dev));
    int nmb_digits = mx_get_nmb_digits_int(MX_MAJOR(dev));
    int nmb_delims_todo = cat->lng_max_major - nmb_digits;

    *result = mx_addstr(*result, " ");
    for (; nmb_delims_todo > 0; nmb_delims_todo--)
        *result = mx_addstr(*result, " ");
    *result = mx_addstr(*result, nmb);
    mx_strdel(&nmb);
    set_minor(nmb, result, dev, cat);
}
