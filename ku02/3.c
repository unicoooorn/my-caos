int call_func(int eax, int ebx, int ecx, int edx) {
    int res, ebp;
    asm("movl %%ebp, %0\n"
        "call func\n"
        "movl %%esi, %1\n"
        "movl %0, %%ebp\n"
        : "=m"(ebp), "=m"(res)
        : "a"(eax), "b"(ebx), "c"(ecx), "d"(edx)
        : "esi");
    return res;
}

void func(int eax, int ebx, int ecx, int edx) {

}

int main(){
    return 0;
}