
#ifndef STUDENT_H
#define STUDENT_H

#define MAX_NAME_LEN 50
#define MAX_SUBJECTS 5
#define MIN_SUBJECTS 3

typedef struct {
    char last_name[MAX_NAME_LEN];
    char first_name[MAX_NAME_LEN];
    char middle_name[MAX_NAME_LEN];
    int birth_year;
    char gender; // 'M' или 'F'
    int grades[MAX_SUBJECTS];
    int subjects_count;
} Student;

void print_student(const Student *student);
int compare_by_age(const Student *a, const Student *b);

#endif
