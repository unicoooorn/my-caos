#include <stdio.h>
#include <stdlib.h>

/*
Строка 22: лучше явно указать, что там unsigned (1103515245u и т.д.)
Строка 37: если аллоцировать память не удалось, надо вернуть NULL
см. указание к условию задачи: нужен глобальный объект RandomOperation, который
можно будет переиспользовать для каждого объекта RandomGenerator
Строка 34: можно не приводить явно к нужному типу
*/

typedef struct RandomOperations {
    void (*destroy)(void *);
    int (*next)(void *);
} RandomOperations;

typedef struct RandomGenerator {
    int cur;
    RandomOperations *ops;
} RandomGenerator;

enum RandomConsts { MULT = 1103515245u, INC = 12345u, MOD = 2147483648u };

static void destroy(RandomGenerator *rg) {
    free(rg);
}

static int next(RandomGenerator *r) {
    r->cur = (((unsigned int)r->cur * MULT) % MOD + INC) % MOD;
    return r->cur;
}

// без явного приведения варнинги
RandomOperations rops = {(void (*)(void *))destroy, (int (*)(void *))next};

RandomGenerator *random_create(int seed) {
    RandomGenerator *rg = calloc(1, sizeof(*rg));
    if (!rg) {
        return NULL;
    }
    rg->ops = &rops;
    rg->cur = seed;
    return rg;
}

int main(void) {
    RandomGenerator *rr = random_create(1234);
    for (int j = 0; j < 100; ++j) {
        printf("%d\n", rr->ops->next(rr));
    }
    rr->ops->destroy(rr);

    return 0;
}