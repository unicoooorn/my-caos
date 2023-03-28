#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int main(){
    uint32_t proc_info, ecx, edx;
    asm("mov $1, %%eax\n"
        "cpuid\n"
        "mov %%eax, %0\n"
        "mov %%ecx, %1\n"
        "mov %%edx, %2\n"
        :"=r"(proc_info), "=r"(ecx), "=r"(edx)
        :
        :"ebx"
    );
    uint32_t family_id = (proc_info << 20) >> 28;
    uint32_t model = (proc_info << 24) >> 28;
    uint32_t ext_family_id = (proc_info << 4) >> 24;
    uint32_t ext_model = (proc_info << 12) >> 28;
    if (0 == printf("family=%d model=%d ecx=0x%x edx=0x%x\n", 
        family_id != 15 ? family_id : ext_family_id + family_id, 
        family_id != 6 && family_id != 15 ? model : (ext_model << 4) + model, 
        ecx, 
        edx)) {
        return 1;
    }
}

