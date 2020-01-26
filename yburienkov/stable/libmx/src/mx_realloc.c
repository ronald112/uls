#include "libmx.h"

void *mx_realloc(void *ptr, size_t size) {
    if (size <= 0)
        return NULL;
    else {
        void *new_ptr = malloc(size);

        if (!new_ptr)
            return NULL;
        else if (!ptr)
            return new_ptr;
        else {
            size_t size_ptr = malloc_size(ptr);

            mx_memcpy(new_ptr, ptr, (size_ptr > size ? size : size_ptr));
            free(ptr);
            return new_ptr;
        }
    }
}
