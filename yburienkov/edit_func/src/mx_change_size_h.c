#include "uls.h"

static long long change_remainder(off_t size, long long *nmb) {
    long long remainder[2] = {0};

    *nmb /= 1024;
    for (int i = 0; i < 2; ++i)
        remainder[i] = mx_get_remainder(size, 1024, i + 1);
    if (remainder[1] >= 5)
        remainder[0] += 1;
    if (remainder[0] == 10) {
        *nmb += 1;
        remainder[0] = 0;
    }
    return remainder[0];
}

static char *add_kilobytes(off_t size, long long nmb) {
    char *temp_res = NULL;
    long long remainder = change_remainder(size, &nmb);

    temp_res = mx_ltoa(nmb);
    if (mx_get_nmb_digits_ll(nmb) == 1) {
        char *temp_str = mx_ltoa(remainder);

        temp_res = mx_addstr(temp_res, ".");
        temp_res = mx_addstr(temp_res, temp_str);
        mx_strdel(&temp_str);
    }
    temp_res = mx_addstr(temp_res, "K");
    return temp_res;
}

static char *add_digits(char **result) {
    int nmb_digits = 5 - mx_strlen(*result);
    char *temp_res = NULL;

    for (; nmb_digits != 0; nmb_digits -= 1)
        temp_res = mx_addstr(temp_res, " ");
    temp_res = mx_addstr(temp_res, *result);
    mx_strdel(result);
    return temp_res;
}

char *mx_change_size_h(off_t size) {
    char *result = NULL;
    char *temp_res = NULL;
    long long nmb = size;

    if (nmb > 1023 && nmb < 1048577) {
        temp_res = add_kilobytes(size, nmb);
    }
    else {
        temp_res = mx_ltoa(nmb);
        temp_res = mx_addstr(temp_res, "B");
    }
    temp_res = add_digits(&temp_res);
    result = mx_addstr(result, temp_res);
    mx_strdel(&temp_res);
    return result;
}

// total 13
// drwxrwxr-x@ 46 root  admin         1472 Nov 20 16:33 Applications
// drwxr-xr-x+ 63 root  wheel         2016 Aug  8  2019 Library
// drwxr-xr-x   2 root  wheel           64 Jan 28  2019 Network
// drwxr-xr-x@  5 root  wheel          160 Jan 16  2019 System
// drwxr-xr-x  48 root  admin         1536 Jan 14 12:00 Users
// drwxr-xr-x@  5 root  wheel          160 Feb 25 09:10 Volumes
// drwxr-xr-x@ 37 root  wheel         1184 Jun  1  2019 bin
// drwxrwxr-t   2 root  admin           64 Jan 28  2019 cores
// dr-xr-xr-x   3 root  wheel         4451 Feb 25 09:05 dev
// drwx------  16 dojo  applications   512 Sep 30 10:19 dojo
// lrwxr-xr-x@  1 root  wheel           11 Jan 28  2019 etc -> private/etc
// dr-xr-xr-x   2 root  wheel            1 Feb 27 16:39 home
// -rw-r--r--   1 root  wheel          313 Aug 18  2018 installer.failurerequests
// dr-xr-xr-x   2 root  wheel            1 Feb 27 16:39 net
// drwxr-xr-x   6 root  wheel          192 Jan 28  2019 private
// drwxr-xr-x@ 64 root  wheel         2048 Jun  1  2019 sbin
// lrwxr-xr-x@  1 root  wheel           11 Jan 28  2019 tmp -> private/tmp
// drwxr-xr-x@  9 root  wheel          288 Jan 16  2019 usr
// lrwxr-xr-x@  1 root  wheel           11 Jan 28  2019 var -> private/var

// total 13
// drwxrwxr-x@ 46 root  admin          1.4K Nov 20 16:33 Applications
// drwxr-xr-x+ 63 root  wheel          2.0K Aug  8  2019 Library
// drwxr-xr-x   2 root  wheel           64B Jan 28  2019 Network
// drwxr-xr-x@  5 root  wheel          160B Jan 16  2019 System
// drwxr-xr-x  48 root  admin          1.5K Jan 14 12:00 Users
// drwxr-xr-x@  5 root  wheel          160B Feb 25 09:10 Volumes
// drwxr-xr-x@ 37 root  wheel          1.2K Jun  1  2019 bin
// drwxrwxr-t   2 root  admin           64B Jan 28  2019 cores
// dr-xr-xr-x   3 root  wheel          4.3K Feb 25 09:05 dev
// drwx------  16 dojo  applications   512B Sep 30 10:19 dojo
// lrwxr-xr-x@  1 root  wheel           11B Jan 28  2019 etc -> private/etc
// dr-xr-xr-x   2 root  wheel            1B Feb 27 16:39 home
// -rw-r--r--   1 root  wheel          313B Aug 18  2018 installer.failurerequests
// dr-xr-xr-x   2 root  wheel            1B Feb 27 16:39 net
// drwxr-xr-x   6 root  wheel          192B Jan 28  2019 private
// drwxr-xr-x@ 64 root  wheel          2.0K Jun  1  2019 sbin
// lrwxr-xr-x@  1 root  wheel           11B Jan 28  2019 tmp -> private/tmp
// drwxr-xr-x@  9 root  wheel          288B Jan 16  2019 usr
// lrwxr-xr-x@  1 root  wheel           11B Jan 28  2019 var -> private/var

// 2c2
// < drwxrwxr-x@ 46 root  admin          1.4K Nov 20 16:33 Applications
// ---
// > drwxrwxr-x@ 46 root  admin          1.0K Nov 20 16:33 Applications
// 6c6
// < drwxr-xr-x  48 root  admin          1.5K Jan 14 12:00 Users
// ---
// > drwxr-xr-x  48 root  admin          1.0K Jan 14 12:00 Users
// 8c8
// < drwxr-xr-x@ 37 root  wheel          1.2K Jun  1  2019 bin
// ---
// > drwxr-xr-x@ 37 root  wheel          1.0K Jun  1  2019 bin
// 10c10
// < dr-xr-xr-x   3 root  wheel          4.3K Feb 25 09:05 dev
// ---
// > dr-xr-xr-x   3 root  wheel          4.0K Feb 25 09:05 dev
// / 
// 2c2
// < -rw-r--r--   1 yburienkov  4242   1.3K Feb 21 11:46 Makefile
// ---
// > -rw-r--r--   1 yburienkov  4242   1.0K Feb 21 11:46 Makefile
// 4c4
// < drwxr-xr-x  78 yburienkov  4242   2.6K Feb 21 14:20 src
// ---
// > drwxr-xr-x  78 yburienkov  4242   2.0K Feb 21 14:20 src
// libmx/
