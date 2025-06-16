
#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <stdbool.h>

#define DB_NAME "students.db"
#define MAX_NAME_LEN 50
#define MAX_SUBJECTS 5
#define MIN_SUBJECTS 3

typedef struct {
    int id;
    char last_name[MAX_NAME_LEN];
    char first_name[MAX_NAME_LEN];
    char middle_name[MAX_NAME_LEN];
    int birth_year;
    char gender; // 'M' или 'F'
} Student;

typedef struct {
    int student_id;
    int subject_id;
    int grade;
} Grade;

// Функции работы с базой данных
bool init_db(sqlite3 **db);
void close_db(sqlite3 *db);
bool create_tables(sqlite3 *db);

// Функции для работы со студентами
bool add_student_autocommit(sqlite3 *db, const Student *student);
bool add_student_transaction(sqlite3 *db, const Student *student);
void print_students(sqlite3 *db);

// Функции для работы с оценками
bool add_grade(sqlite3 *db, int student_id, int subject_id, int grade);
void print_grades(sqlite3 *db, int student_id);
void print_all_grades(sqlite3 *db);

#endif
