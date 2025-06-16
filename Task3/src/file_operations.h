#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include "student.h"

void add_student_to_file(const char *filename);
void print_all_students(const char *filename);
Student find_oldest_student(const char *filename);

#endif
