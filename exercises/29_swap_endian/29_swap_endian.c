#include <stdint.h>
#include <stdio.h>

uint32_t swap_endian(uint32_t num) {
    uint8_t *src, *dst;
    uint32_t ret;

    src = (uint8_t *)&num;
    dst = (uint8_t *)&ret;

    for (int i = 0; i < sizeof(uint32_t); ++i) {
        dst[i] = src[sizeof(uint32_t) - i - 1];
    }

    return ret;
}

int main(int argc, char* argv[]) {
    uint32_t num = 0x78563412;
    uint32_t swapped = swap_endian(num);
    printf("0x%08x -> 0x%08x\n", num, swapped);
    return 0;
}
