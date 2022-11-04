#define _GNU_SOURCE
#include <string.h>
#include <dlfcn.h>

typedef int (*remove_syscall)(const char* filename);

int remove(const char *filename) {
    remove_syscall system_remove = dlsym((void *)RTLD_NEXT, "remove");
    if (strstr(filename, "PROTECT") != NULL) return 0; // do noting
    return system_remove(filename);
}