#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LEN 50

typedef struct {
    char name[NAME_LEN];
    int score;
} Student;

Student students[MAX_STUDENTS];
Student temp[MAX_STUDENTS];

int min(int x, int y)
{
    return x < y ? x : y;
}

void merge_sort(int left, int right) {
    Student *a = students, *b = temp;
    int seg, start;
    int len = right + 1;

    for (seg = 1; seg < len; seg += seg) {
        for (start = 0; start < len; start += seg * 2) {
            int start1 = start, end1 = min(start1 + seg, len);
            int start2 = start + seg, end2 = min(start2 + seg, len);
            int k = start1;

            while (start1 < end1 && start2 < end2)
                b[k++] = a[start1].score > a[start2].score ? a[start1++] : a[start2++];
            while (start1 < end1)
                b[k++] = a[start1++];
            while (start2 < end2)
                b[k++] = a[start2++];
        }

        Student *_tmp = a;
        a = b;
        b = _tmp;
    }

    if (a != students) {
        for (int i = 0; i < len; ++i)
            b[i] = a[i];
    }
}

int main(void) {
    FILE *file = fopen("02_students.txt", "r");
    if (!file) {
        printf("错误：无法打开文件 02_students.txt\n");
        return 1;
    }

    int n;
    fscanf(file, "%d", &n);

    if (n <= 0 || n > MAX_STUDENTS) {
        printf("学生人数无效：%d\n", n);
        fclose(file);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        fscanf(file, "%s %d", students[i].name, &students[i].score);
    }
    fclose(file);

    merge_sort(0, n - 1);

    printf("\n归并排序后按成绩从高到低排序的学生名单：\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", students[i].name, students[i].score);
    }

    return 0;
}
