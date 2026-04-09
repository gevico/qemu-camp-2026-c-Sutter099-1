#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LEN     50

typedef struct {
    char name[NAME_LEN];
    int score;
} Student;

Student students[MAX_STUDENTS];

void quick_sort(int left, int right) {
    int stack[64];
    int len = right - left + 1;

    int top = -1;
    stack[++top] = left;
    stack[++top] = right;

    while (top >= 0) {
        int right = stack[top--];
        int left = stack[top--];
        int i = left;
        int j = right;

        Student pivot = students[i];
        while (i < j) {
            while (i < j && students[j].score <= pivot.score)
                --j;
            students[i] = students[j];

            while (i < j && students[i].score >= pivot.score)
                ++i;
            students[j] = students[i];
        }
        students[i] = pivot;

        int left_len = i - left;
        int right_len = right - i;

        if (left_len < right_len) {
            if (right_len > 1) {
                stack[++top] = i + 1;
                stack[++top] = right;
            }
            if (left_len > 1) {
                stack[++top] = left;
                stack[++top] = i - 1;
            }
        } else {
            if (left_len > 1) {
                stack[++top] = left;
                stack[++top] = i - 1;
            }
            if (right_len > 1) {
                stack[++top] = i + 1;
                stack[++top] = right;
            }
        }
    }
}

int main(void) {
    FILE *file = fopen("03_students.txt", "r");
    if (!file) {
        printf("错误：无法打开文件 03_students.txt\n");
        return 1;
    }

    int n;
    fscanf(file, "%d", &n);

    if (n <= 0 || n > MAX_STUDENTS) {
        printf("学生人数无效：%d（应为 1-%d）\n", n, MAX_STUDENTS);
        fclose(file);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        fscanf(file, "%s %d", students[i].name, &students[i].score);
    }
    fclose(file);

    quick_sort(0, n - 1);

    // 输出结果
    printf("\n快速排序后按成绩从高到低排序的学生名单：\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", students[i].name, students[i].score);
    }

    return 0;
}
