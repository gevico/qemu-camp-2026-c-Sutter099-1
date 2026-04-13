#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1024

int parse_replace_command(const char* cmd, char** old_str, char** new_str) {
    if (cmd[0] != 's' || cmd[1] != '/') {
        return -1;
    }

    char *first, *second, *last;
    int len1, len2;

    first  = strchr(cmd, '/');
    second = strchr(first + 1, '/');
    last   = strchr(second + 1, '/');

    len1 = second - first;
    len2 = last - second;

    *old_str = malloc(len1);
    *new_str = malloc(len2);

    memcpy(*old_str, first + 1, len1);
    (*old_str)[len1 - 1] = '\0';
    memcpy(*new_str, second + 1, len2);
    (*new_str)[len2 - 1] = '\0';

    return 0;
}

void replace_first_occurrence(char* str, const char* old, const char* new) {
    char *replace, *head, *tail;
    int len_old = strlen(old);
    int len_new = strlen(new);
    int len_tail, len_head;

    replace = strstr(str, old);
    if (replace == NULL) {
        fprintf(stderr, "sub string not found\n");
        return;
    }

    head = str;
    tail = replace + len_old;
    len_head = replace - head;
    len_tail = strlen(str) - len_old - len_head;

    memmove(replace + len_new, tail, len_tail + 1); // terminator '\0'
    memmove(replace, new, len_new);
}

int main(int argc, char* argv[]) {
    const char* replcae_rules = "s/unix/linux/";

    char line[MAX_LINE_LENGTH] = {"unix is opensource. unix is free os."};

    char* old_str = NULL;
    char* new_str = NULL;
    
    if (parse_replace_command(replcae_rules, &old_str, &new_str) != 0) {
        fprintf(stderr, "Invalid replace command format. Use 's/old/new/'\n");
        return 1;
    }

    
    replace_first_occurrence(line, old_str, new_str);
    fputs(line, stdout);

    free(old_str);
    free(new_str);
    return 0;
}
