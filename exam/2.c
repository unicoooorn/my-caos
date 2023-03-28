#include <dlfcn.h>
#include <gnu/lib-names.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char lib_name[32];
    char func_name[32];
    char arg_name[32];
    while (scanf("%s", lib_name) != EOF) {
        void *h = dlopen(lib_name, RTLD_LAZY);
        if (!scanf("%s", arg_name) || !scanf("%s", func_name)) {
            return 1;
        }
        if (arg_name[0] == 'i') {
            int (*func)(int) = dlsym(h, func_name);
            int arg;
            if (!scanf("%d", &arg)) {
                return 1;
            }
            printf("%d\n", (*func)(arg));
        } else if (arg_name[0] == 'f'){
            float (*func)(float) = dlsym(h, func_name);
            float arg;
            if (!scanf("%f", &arg)) {
                return 1;
            }
            printf("%.10g\n", (*func)(arg));
        }
    }
}
