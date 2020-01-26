#include "libmx.h"

static void max_int_chk(int *n, bool *flag) {
    if (n == -2147483648) {
        *n += 1;
        *flag = 1;
    }
    mx_printchar('-');
    *n *= -1;
}

static void final_print(int counter, int n, bool flag) {
    char arr[counter];

    for (int i = counter - 1; i >= 0; i--) {
        if (flag == 1) {
            arr[counter - 1] = 8;
            flag = 0;
        }
        else
            arr[i] = n % 10;
        n /= 10;
    }
    for (int i = 0; i < counter; i++)
        mx_printchar(arr[i] + 48);
}

static void final_calculations(int n, bool flag) {
    int copy = n;
    int counter = 0;

    while (copy != 0) {
        counter++;
        copy /= 10;
    }
    copy = n;
    final_print(counter, n, flag);
}

void mx_printint(int n) {
    bool flag = 0;

    if (n < 0) {
        max_int_chk(&n, &flag);
    }
    else if (n == 0)
        mx_printchar('0');
    else {
        final_calculations(n, flag);
    }
}
