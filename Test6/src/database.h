#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <stdbool.h>

#define DB_NAME "students.db"
#define MAX_NAME_LEN 50
#define MAX_SUBJECTS 5
#define MIN_SUBJECTS 3
#define MAX_GROUP_LEN 10

typedef struct {
    int id;
    char last_name[MAX_NAME_LEN];
    char first_name[MAX_NAME_LEN];
    char middle_name[MAX_NAME_LEN];
    int birth_year;
    char gender; // 'M' или 'F'
    char group[MAX_GROUP_LEN];
    int course;
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
bool populate_sample_data(sqlite3 *db);

// Функции для запросов
void print_oldest_students(sqlite3 *db);
void print_top_students_by_course(sqlite3 *db);
void print_avg_grades_by_group_and_course(sqlite3 *db);

#endif
