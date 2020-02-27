#include "uls.h"

void mx_add_xatr(char *path, char **result) {
    ssize_t xattr = listxattr(path, NULL, 0, XATTR_NOFOLLOW);
    acl_t acl = acl_get_file(path, ACL_TYPE_EXTENDED);

    if (xattr > 0) {
        *result = mx_addstr(*result, "@");
    }
    else if (acl == NULL)
        *result = mx_addstr(*result, " ");
    else
        *result = mx_addstr(*result, "+");
    acl_free(acl);
    acl = NULL;
}

// e2r11p9% ls -l@ /
// total 13
// drwxrwxr-x@ 46 root  admin         1472 Nov 20 16:33 Applications
// 	com.apple.FinderInfo	  32 
// drwxr-xr-x+ 63 root  wheel         2016 Aug  8  2019 Library
// drwxr-xr-x   2 root  wheel           64 Jan 28  2019 Network
// drwxr-xr-x@  5 root  wheel          160 Jan 16  2019 System
// 	com.apple.rootless	   0 
// drwxr-xr-x  48 root  admin         1536 Jan 14 12:00 Users
// drwxr-xr-x@  5 root  wheel          160 Feb 25 09:10 Volumes
// 	com.apple.FinderInfo	  32 
// drwxr-xr-x@ 37 root  wheel         1184 Jun  1  2019 bin
// 	com.apple.rootless	   0 
// drwxrwxr-t   2 root  admin           64 Jan 28  2019 cores
// dr-xr-xr-x   3 root  wheel         4451 Feb 25 09:05 dev
// drwx------  16 dojo  applications   512 Sep 30 10:19 dojo
// lrwxr-xr-x@  1 root  wheel           11 Jan 28  2019 etc -> private/etc
// 	com.apple.rootless	   0 
// dr-xr-xr-x   2 root  wheel            1 Feb 27 16:39 home
// -rw-r--r--   1 root  wheel          313 Aug 18  2018 installer.failurerequests
// dr-xr-xr-x   2 root  wheel            1 Feb 27 16:39 net
// drwxr-xr-x   6 root  wheel          192 Jan 28  2019 private
// drwxr-xr-x@ 64 root  wheel         2048 Jun  1  2019 sbin
// 	com.apple.rootless	   0 
// lrwxr-xr-x@  1 root  wheel           11 Jan 28  2019 tmp -> private/tmp
// 	com.apple.rootless	   0 
// drwxr-xr-x@  9 root  wheel          288 Jan 16  2019 usr
// 	com.apple.rootless	   0 
// lrwxr-xr-x@  1 root  wheel           11 Jan 28  2019 var -> private/var
// 	com.apple.rootless	   0 
// e2r11p9% ls -l@ /../dev

