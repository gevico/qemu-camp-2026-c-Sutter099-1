#include <stdio.h>
#include <string.h>

typedef enum {
    SPACE,
    WORD,
} char_type;

int main() {
    char str[]="Don't ask what your country can do for you, but ask what you can do for your country.";
    int wordCount = 0;
    int len = strlen(str);
    char_type last = SPACE;

    for (int i = 0; i < len; ++i) {
        if (str[i] == ' ') {
            if (last == WORD)
                wordCount++;
            last = SPACE;
        } else {
            last = WORD;
        }
    }

    if (last == WORD)
        wordCount++;

    printf("单词数量: %d\n", wordCount);
    
    return 0;
}
