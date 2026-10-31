#include <string.h>
#include <stdio.h>
#include <dlfcn.h>

static int (*real_remove)(const char *) = NULL;
int remove(const char *path)
{
    if (real_remove == NULL) {
        real_remove = dlsym(RTLD_NEXT, "remove");
    }
    if (path != NULL && strstr(path, "PROTECT") != NULL) {
        return 0;
    }
    return real_remove(path);
}
