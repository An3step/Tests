#include <stdio.h>
#include <string.h>
#include "utils.h"

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void safe_input(char *str, int max_len) {
    fgets(str, max_len, stdin);
    str[strcspn(str, "\n")] = '\0'; // Удаляем символ новой строки
    clear_input_buffer();
}

void print_menu() {
    printf("\n=== Меню ===\n");
    printf("1. Добавить запись в файл\n");
    printf("2. Просмотреть все записи файла\n");
    printf("3. Найти самого старшего студента\n");
    printf("4. Выход\n");
    printf("Выберите действие: ");
}
