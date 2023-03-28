

int call_func(int eax, int ebx, int ecx, int edx) {
    int result;
    asm
    ("call func" 
    : "=S"(result) 
    : "a"(eax), "b"(ebx), "c" (ecx), "d"(edx)
    : "ebp"
    );
    return result;
}