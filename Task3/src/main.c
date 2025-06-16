#include <stdio.h>
#include <stdlib.h>
#include "student.h"
#include "file_operations.h"
#include "utils.h"

#define FILENAME "students.dat"

int main() {
    int choice;
    
    do {
        print_menu();
        scanf("%d", &choice);
        clear_input_buffer();
        
        switch (choice) {
            case 1:
                add_student_to_file(FILENAME);
                break;
            case 2:
                print_all_students(FILENAME);
                break;
            case 3: {
                Student oldest = find_oldest_student(FILENAME);
                printf("\n=== Самый старший студент ===\n");
                print_student(&oldest);
                printf("============================\n");
                break;
            }
            case 4:
                printf("Выход из программы.\n");
                break;
            default:
                printf("Неверный выбор. Попробуйте снова.\n");
        }
    } while (choice != 4);
    
    return 0;
}
