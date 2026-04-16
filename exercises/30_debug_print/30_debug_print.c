#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>

#ifdef DEBUG_LEVEL

#if DEBUG_LEVEL == 1

#define DEBUG_PRINT(fmt, ...) \
    printf("DEBUG: func=%s, line=%d\n", __func__, __LINE__)

#elif DEBUG_LEVEL == 2

#define DEBUG_PRINT(fmt, ...)                                       \
do {                                                                \
    printf("DEBUG: func=%s, line=%d, ", __func__, __LINE__);        \
    printf(fmt, __VA_ARGS__);                                       \
    printf("\n");                                                   \
} while (0)

#elif DEBUG_LEVEL == 3

#define BT_BUF_SIZE 100
#define DEBUG_PRINT(fmt, ...)                                       \
do {                                                                \
    int nptrs;                                                      \
    void *buffer[BT_BUF_SIZE];                                      \
    char **strings;                                                 \
                                                                    \
    printf("DEBUG: func=%s, line=%d, ", __func__, __LINE__);        \
    printf(fmt, __VA_ARGS__);                                       \
    printf("\n");                                                   \
    nptrs = backtrace(buffer, BT_BUF_SIZE);                         \
    strings = backtrace_symbols(buffer, nptrs);                     \
                                                                    \
    for (size_t j = 0; j < nptrs; j++)                              \
        printf("%s\n", strings[j]);                                 \
                                                                    \
    free(strings);                                                  \
} while (0)
#endif
#else
#define DEBUG_PRINT(fmt, ...) do {} while (0)
#endif

void test() {
    int x = 42;
    DEBUG_PRINT("x=%d", x);
}

int main() {
    test();
    return 0;
}
