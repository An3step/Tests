#include <stdio.h>
#include <stdlib.h>
#include "student.h"

void input_student(Student *student) {
    printf("Введите фамилию: ");
    scanf("%49s", student->last_name);
    
    printf("Введите имя: ");
    scanf("%49s", student->first_name);
    
    printf("Введите отчество: ");
    scanf("%49s", student->middle_name);
    
    printf("Введите год рождения: ");
    scanf("%d", &student->birth_year);
    
    printf("Введите пол (M/F): ");
    scanf(" %c", &student->gender);
}

void print_student_menu() {
    printf("\n=== Меню студента ===\n");
    printf("1. Добавить студента (autocommit)\n");
    printf("2. Добавить студента (transaction)\n");
    printf("3. Показать всех студентов\n");
    printf("4. Добавить оценку\n");
    printf("5. Показать оценки студента\n");
    printf("6. Показать все оценки\n");
    printf("7. Выход\n");
    printf("Выберите действие: ");
}
