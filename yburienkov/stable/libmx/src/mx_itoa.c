#include "libmx.h"

// check if int = -2147483648
static void max_chk(int *number, bool *if_negative, bool *flag) {
    if (*number < 0) {
        *if_negative = 1;
        if (*number == -2147483648) {
            *number++;
            *flag = 1;
        }
        *number *= -1;
    }
}

// fill result string
static char *fill_char(int number, bool flag, bool if_negative, int counter) {
    char *arr = mx_strnew(counter + 1);

    if (if_negative == 1)
        arr[0] = '-';
    for (int i = counter - 1; i >= if_negative; i--) {
        if (flag == 1) {
            arr[counter - 1] = 8 + '0';
            flag = 0;
        }
        else
            arr[i] = (number % 10) + '0';
        number /= 10;
    }
    arr[counter + 1] = '\0';
    return arr;
}

// count digits and fill final string
static char *transfer_to_ascii(int number, bool flag, bool if_negative) {
    int copy = number;
    int counter = 0;

    while (copy != 0) {
        counter++;
        copy /= 10;
    }
    copy = number;
    if (if_negative == 1)
        counter++;
    return fill_char(number, flag, if_negative, counter);
}

// integer to ascii
char *mx_itoa(int number) {
    bool flag = 0;
    bool if_negative = 0;

    max_chk(&number, &if_negative, &flag);
    if (number == 0) {
        char *arr = mx_strnew(1);

        arr[0] = 0 + '0';
        return arr;
    }
    else {
        return transfer_to_ascii(number, flag, if_negative);
    }
}
