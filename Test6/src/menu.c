#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "student.h"

void run_menu(sqlite3 *db) {
    int choice;
    
    do {
        print_menu();
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                print_oldest_students(db);
                break;
            case 2:
                print_top_students_by_course(db);
                break;
            case 3:
                print_avg_grades_by_group_and_course(db);
                break;
            case 4:
                printf("Выход из программы.\n");
                break;
            default:
                printf("Неверный выбор. Попробуйте снова.\n");
        }
    } while(choice != 4);
}
