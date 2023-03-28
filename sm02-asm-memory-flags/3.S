.global partition
swap:
    // eax - X
    // ((%ebx), %ecx, 2) - Y
    xorw (%ebx, %edx, 2), %ax
    xorw %ax, (%ebx, %edx, 2)
    xorw (%ebx, %edx, 2), %ax
    ret

partition:
    // ebx - адрес начала массива int16_t
    // esi - количество элементов в массиве
    // edi - pivot

    // eax - текущий элемент
    // ecx - счётчик
    // edx - точка начала бОльшей части
    push %ebp
    xor %ecx, %ecx
    xor %edx, %edx
    xor %eax, %eax
loop:
    movw (%ebx, %ecx, 2), %ax   // ввели текущее число в eax
    
    cmpw %ax, %di
    jnz not_mid
// if mid
    mov %edx, %ebp
not_mid:
    cmp %ax, %di // сравнили с пивотом
    jl noswap   // если edi больше eax, то своп не нужен

// if swap
    call swap   // меняем местами значение в массиве после разделителя и eax
    mov %ax, (%ebx, %ecx, 2)   // записываем eax в 
    inc %edx    // 
noswap:
    inc %ecx
    cmpl %ecx, %esi
    jnz loop
    dec %edx
    mov (%ebx, %edx, 2), %cx
    mov %di, (%ebx, %edx, 2)
    mov %cx, (%ebx, %ebp, 2)
    pop %ebp
    ret

    