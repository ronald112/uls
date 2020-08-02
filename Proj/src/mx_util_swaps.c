#include "uls.h"

void mx_swap_ll(long long *a, long long *b) {
    long long temp = *a;

    *a = *b;
    *b = temp;
}

void mx_swap_bool(bool *a, bool *b) {
    bool temp = *a;

    *a = *b;
    *b = temp;
}

void mx_swap_int(int *a, int *b) {
    int temp = *a;

    *a = *b;
    *b = temp;
}

void mx_swap_str(char **a, char **b) {
    char *temp = *a;

    *a = *b;
    *b = temp;
}
