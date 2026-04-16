#include <stdio.h>

unsigned int gcd_asm(unsigned int a, unsigned int b) {
    unsigned int result;
    
    __asm__ volatile (
        "mov %1, %%eax\n\t"     // 将a存入eax
        "mov %2, %%ebx\n\t"     // 将b存入ebx
        
        ".L_loop:\n\t"
        "   cmp %%ebx, %%eax\n\t"
        "   je .L_done\n\t"
        "   ja .L_sub_a\n\t"
        "   sub %%eax, %%ebx\n\t"
        "   jmp .L_loop\n\t"
        
        ".L_sub_a:\n\t"
        "   sub %%ebx, %%eax\n\t"
        "   jmp .L_loop\n\t"    // 继续循环
        
        ".L_done:\n\t"
        "mov %%eax, %0"         // 将结果（eax）存入输出变量
        : "=r" (result)         // 输出操作数
        : "r" (a), "r" (b)      // 输入操作数
        : "eax", "ebx"          // 被修改的寄存器
    );
    
    return result;
}

int main(int argc, char* argv[]) {
    printf("%d\n", gcd_asm(12, 8));
    printf("%d\n", gcd_asm(7, 5));
    return 0;
}
