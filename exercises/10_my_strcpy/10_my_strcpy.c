#include <stdio.h>
#include <string.h>

int main() {
    char source[] = "Hello, World! This is a test string for my_strcpy function.\n";
    char destination[101];
    
    int max_len = 101;
    int src_len = strlen(source);

    max_len = max_len < src_len ? max_len : src_len;
    memcpy(destination, source, max_len);
    
    printf("拷贝后的字符串: %s", destination);
    
    return 0;
}
