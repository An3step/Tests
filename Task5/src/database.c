#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    for(int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

bool init_db(sqlite3 **db) {
    int rc = sqlite3_open(DB_NAME, db);
    if(rc) {
        fprintf(stderr, "Не удалось открыть базу данных: %s\n", sqlite3_errmsg(*db));
        return false;
    }
    return true;
}

void close_db(sqlite3 *db) {
    sqlite3_close(db);
}

bool create_tables(sqlite3 *db) {
    char *err_msg = 0;
    const char *sql =
        "CREATE TABLE IF NOT EXISTS Students ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "last_name TEXT NOT NULL,"
        "first_name TEXT NOT NULL,"
        "middle_name TEXT NOT NULL,"
        "birth_year INTEGER NOT NULL,"
        "gender TEXT NOT NULL);"
        
        "CREATE TABLE IF NOT EXISTS Subjects ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT NOT NULL UNIQUE);"
        
        "CREATE TABLE IF NOT EXISTS Grades ("
        "student_id INTEGER NOT NULL,"
        "subject_id INTEGER NOT NULL,"
        "grade INTEGER NOT NULL,"
        "FOREIGN KEY(student_id) REFERENCES Students(id),"
        "FOREIGN KEY(subject_id) REFERENCES Subjects(id),"
        "PRIMARY KEY(student_id, subject_id));"
        
        "INSERT OR IGNORE INTO Subjects (name) VALUES "
        "('Математика'), ('Физика'), ('Химия'), "
        "('История'), ('Литература');";

    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "Ошибка SQL: %s\n", err_msg);
        sqlite3_free(err_msg);
        return false;
    }
    return true;
}

bool add_student_autocommit(sqlite3 *db, const Student *student) {
    char sql[512];
    sprintf(sql,
            "INSERT INTO Students (last_name, first_name, middle_name, birth_year, gender) "
            "VALUES ('%s', '%s', '%s', %d, '%c');",
            student->last_name, student->first_name, student->middle_name,
            student->birth_year, student->gender);

    char *err_msg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "Ошибка SQL: %s\n", err_msg);
        sqlite3_free(err_msg);
        return false;
    }
    return true;
}

bool add_student_transaction(sqlite3 *db, const Student *student) {
    char *err_msg = 0;
    
    // Начало транзакции
    int rc = sqlite3_exec(db, "BEGIN TRANSACTION;", 0, 0, &err_msg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "Ошибка начала транзакции: %s\n", err_msg);
        sqlite3_free(err_msg);
        return false;
    }

    char sql[512];
    sprintf(sql,
            "INSERT INTO Students (last_name, first_name, middle_name, birth_year, gender) "
            "VALUES ('%s', '%s', '%s', %d, '%c');",
            student->last_name, student->first_name, student->middle_name,
            student->birth_year, student->gender);

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "Ошибка SQL: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_exec(db, "ROLLBACK;", 0, 0, 0);
        return false;
    }

    // Фиксация транзакции
    rc = sqlite3_exec(db, "COMMIT;", 0, 0, &err_msg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "Ошибка коммита транзакции: %s\n", err_msg);
        sqlite3_free(err_msg);
        return false;
    }
    return true;
}

void print_students(sqlite3 *db) {
    const char *sql = "SELECT * FROM Students;";
    char *err_msg = 0;
    
    printf("\n=== Список студентов ===\n");
    int rc = sqlite3_exec(db, sql, callback, 0, &err_msg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "Ошибка SQL: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
    printf("=======================\n");
}

bool add_grade(sqlite3 *db, int student_id, int subject_id, int grade) {
    char sql[256];
    sprintf(sql,
            "INSERT OR REPLACE INTO Grades (student_id, subject_id, grade) "
            "VALUES (%d, %d, %d);",
            student_id, subject_id, grade);

    char *err_msg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "Ошибка SQL: %s\n", err_msg);
        sqlite3_free(err_msg);
        return false;
    }
    return true;
}

void print_grades(sqlite3 *db, int student_id) {
    char sql[256];
    sprintf(sql,
            "SELECT s.last_name, s.first_name, sub.name, g.grade "
            "FROM Grades g "
            "JOIN Students s ON g.student_id = s.id "
            "JOIN Subjects sub ON g.subject_id = sub.id "
            "WHERE g.student_id = %d;",
            student_id);

    char *err_msg = 0;
    printf("\n=== Оценки студента ===\n");
    int rc = sqlite3_exec(db, sql, callback, 0, &err_msg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "Ошибка SQL: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
    printf("======================\n");
}

void print_all_grades(sqlite3 *db) {
    const char *sql =
        "SELECT s.last_name, s.first_name, sub.name, g.grade "
        "FROM Grades g "
        "JOIN Students s ON g.student_id = s.id "
        "JOIN Subjects sub ON g.subject_id = sub.id "
        "ORDER BY s.last_name, s.first_name, sub.name;";

    char *err_msg = 0;
    printf("\n=== Все оценки ===\n");
    int rc = sqlite3_exec(db, sql, callback, 0, &err_msg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "Ошибка SQL: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
    printf("=================\n");
}
