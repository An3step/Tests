#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "student.h"

void run_menu(sqlite3 *db) {
    int choice;
    Student student;
    int student_id, subject_id, grade;
    
    do {
        print_student_menu();
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                input_student(&student);
                if(add_student_autocommit(db, &student)) {
                    printf("Студент успешно добавлен (autocommit режим)!\n");
                }
                break;
            case 2:
                input_student(&student);
                if(add_student_transaction(db, &student)) {
                    printf("Студент успешно добавлен (режим транзакции)!\n");
                }
                break;
            case 3:
                print_students(db);
                break;
            case 4:
                printf("Введите ID студента: ");
                scanf("%d", &student_id);
                printf("Введите ID предмета (1-5): ");
                scanf("%d", &subject_id);
                printf("Введите оценку: ");
                scanf("%d", &grade);
                if(add_grade(db, student_id, subject_id, grade)) {
                    printf("Оценка успешно добавлена!\n");
                }
                break;
            case 5:
                printf("Введите ID студента: ");
                scanf("%d", &student_id);
                print_grades(db, student_id);
                break;
            case 6:
                print_all_grades(db);
                break;
            case 7:
                printf("Выход из программы.\n");
                break;
            default:
                printf("Неверный выбор. Попробуйте снова.\n");
        }
    } while(choice != 7);
}
