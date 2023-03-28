#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *perms_to_str(char *buf, size_t size, int perms) {
    enum {
        GROUP_BLOCK_SIZE = 4,
        MAX_RIGHTS_OFFS = 2,
        RIGHTS_TOTAL = 3,
        SUID_OFFS = 8,
        SGID_OFFS = 4,
        PERM_BASE = 8,
        CHARS_TOTAL = 9,
        SUID_MASK = 0b100,
        SGID_MASK = 0b010,
        STICKY_MASK = 0b001,
        READ_MASK = 0b100,
        WRITE_MASK = 0b010,
        EXEC_MASK = 0b001
    };

    if (size == 0) {
        return buf;
    }

    int other_perms = perms % PERM_BASE;
    int group_perms = perms % (PERM_BASE * PERM_BASE) / PERM_BASE;
    int user_perms =
        perms % (PERM_BASE * PERM_BASE * PERM_BASE) / (PERM_BASE * PERM_BASE);
    int flags = perms / (PERM_BASE * PERM_BASE * PERM_BASE);
    bool is_suid_set = flags & SUID_MASK;
    bool is_sgid_set = flags & SGID_MASK;
    bool is_sticky_set = flags & STICKY_MASK;
    char user_rights[RIGHTS_TOTAL + 1] = "---\0";
    char group_rights[RIGHTS_TOTAL + 1] = "---\0";
    char other_rights[RIGHTS_TOTAL + 1] = "---\0";
    const char PERMS_CHARS[3] = {'r', 'w', 'x'};

    for (int i = 0; i <= MAX_RIGHTS_OFFS; i++) {
        int rights_num = MAX_RIGHTS_OFFS - i;
        int rights_char = PERMS_CHARS[rights_num];
        user_rights[rights_num] = (((user_perms >> i) & 1) ? rights_char : '-');
        group_rights[rights_num] =
            (((group_perms >> i) & 1) ? rights_char : '-');
        other_rights[rights_num] =
            (((other_perms >> i) & 1) ? rights_char : '-');
    }

    /* В параметре perms обрабатываются младшие 12 бит, остальные биты
    игнорируются. SUID-бит отображается в позиции бита 'x' для владельца как
    символ 's' только в том случае, если SUID-бит установлен и установлен бит
    'x' для группы или для прочих пользователей. SGID-бит отображается в позиции
    бита 'x' для группы как символ 's' только в том случае, если SGID-бит
    установлен и установлен бит 'x' для прочих пользователей. Sticky-бит
    отображается в позиции бита 'x' для прочих пользователей как символ 't'
    только в том случае, если установлен sticky-бит, установлен бит 'w' для
    прочих пользователей и установлен бит 'x' для прочих пользователей.
    */

    if (is_suid_set &&
        ((EXEC_MASK & group_perms) || (EXEC_MASK & other_perms))) {
        user_rights[MAX_RIGHTS_OFFS] = 's';
    }

    if (is_sgid_set && (EXEC_MASK & other_perms)) {
        group_rights[MAX_RIGHTS_OFFS] = 's';
    }

    if (is_sticky_set && (WRITE_MASK & other_perms) &&
        (EXEC_MASK & other_perms)) {
        other_rights[MAX_RIGHTS_OFFS] = 't';
    }
    char res[GROUP_BLOCK_SIZE * RIGHTS_TOTAL];
    res[0] = '\0';
    snprintf(res, GROUP_BLOCK_SIZE * RIGHTS_TOTAL, "%s%s%s", user_rights,
             group_rights, other_rights);
    for (int i = 0; i < (size - 1 < CHARS_TOTAL ? size - 1 : CHARS_TOTAL);
         i++) {
        buf[i] = res[i];
    }
    buf[size - 1 > CHARS_TOTAL ? CHARS_TOTAL : size - 1] = '\0';
    return buf;
}

int main() {
    char kek[10];
    puts(perms_to_str(kek, 10, 0075));
    return 0;
}