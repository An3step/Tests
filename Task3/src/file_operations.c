#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_operations.h"
#include "utils.h"

void add_student_to_file(const char *filename) {
    FILE *file = fopen(filename, "ab");
    if (!file) {
        file = fopen(filename, "wb");
        if (!file) {
            perror("Не удалось открыть файл");
            return;
        }
    }

    Student student;
    
    printf("Введите фамилию: ");
    safe_input(student.last_name, MAX_NAME_LEN);
    
    printf("Введите имя: ");
    safe_input(student.first_name, MAX_NAME_LEN);
    
    printf("Введите отчество: ");
    safe_input(student.middle_name, MAX_NAME_LEN);
    
    printf("Введите год рождения: ");
    scanf("%d", &student.birth_year);
    clear_input_buffer();
    
    printf("Введите пол (M/F): ");
    scanf("%c", &student.gender);
    clear_input_buffer();
    
    printf("Введите количество предметов (от %d до %d): ", MIN_SUBJECTS, MAX_SUBJECTS);
    scanf("%d", &student.subjects_count);
    clear_input_buffer();
    
    if (student.subjects_count < MIN_SUBJECTS || student.subjects_count > MAX_SUBJECTS) {
        printf("Некорректное количество предметов. Установлено значение по умолчанию: %d\n", MIN_SUBJECTS);
        student.subjects_count = MIN_SUBJECTS;
    }
    
    for (int i = 0; i < student.subjects_count; i++) {
        printf("Введите оценку по предмету %d: ", i + 1);
        scanf("%d", &student.grades[i]);
        clear_input_buffer();
    }
    
    fwrite(&student, sizeof(Student), 1, file);
    fclose(file);
    
    printf("Студент успешно добавлен!\n\n");
}

void print_all_students(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("Файл не существует или не может быть открыт.\n\n");
        return;
    }
    
    Student student;
    int count = 0;
    
    printf("\n=== Все студенты ===\n");
    while (fread(&student, sizeof(Student), 1, file) == 1) {
        print_student(&student);
        count++;
    }
    
    if (count == 0) {
        printf("В файле нет записей о студентах.\n");
    }
    
    fclose(file);
    printf("===================\n\n");
}

Student find_oldest_student(const char *filename) {
    FILE *file = fopen(filename, "rb");
    Student oldest, current;
    int first = 1;
    
    if (!file) {
        printf("Файл не существует или не может быть открыт.\n\n");
        exit(1);
    }
    
    while (fread(&current, sizeof(Student), 1, file) == 1) {
        if (first || compare_by_age(&current, &oldest) < 0) {
            oldest = current;
            first = 0;
        }
    }
    
    fclose(file);
    return oldest;
}
