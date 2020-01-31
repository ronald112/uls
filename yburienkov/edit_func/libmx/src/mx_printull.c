#include "libmx.h"

static void max_int_case(long long *n, long long *rev) {
    if(*n < 0) {
        mx_printchar('-');
        *n = -(*n);
    }
    while (*n != 0) {
        *rev = *rev * 10 + *n % 10;
        *n /= 10;
    }
}

static void print_ull(long long rev, long long reserv) {
    while (rev != 0) {
        mx_printchar(rev % 10 + 48);
        rev /= 10;
    }
    while (reserv % 10 == 0) {
        reserv /= 10;
        mx_printchar('0');
    }
}

static void calculation(long long *n, long long *rev) {
    if (*n == 0) {
        mx_printchar('0');
        return;
    }
    if (*n != -9223372036854775807) {
        max_int_case(n, rev);
    }
    else {
        *rev = 7085774586302733229;
        mx_printchar('-');
    }
}

void mx_printull(long long n) {
    long long rev = 0;
    long long reserv = n;

    calculation(&n, &rev);
    print_ull(rev, reserv);
}
