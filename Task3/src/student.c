#include <stdio.h>
#include "student.h"

void print_student(const Student *student) {
    printf("Фамилия: %s\n", student->last_name);
    printf("Имя: %s\n", student->first_name);
    printf("Отчество: %s\n", student->middle_name);
    printf("Год рождения: %d\n", student->birth_year);
    printf("Пол: %c\n", student->gender);
    printf("Оценки: ");
    for (int i = 0; i < student->subjects_count; i++) {
        printf("%d ", student->grades[i]);
    }
    printf("\n\n");
}

int compare_by_age(const Student *a, const Student *b) {
    return a->birth_year - b->birth_year;
}
