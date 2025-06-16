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

static int print_row(void *data, int argc, char **argv, char **azColName) {
    for(int i = 0; i < argc; i++) {
        printf("%-20s", argv[i] ? argv[i] : "NULL");
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
        "gender TEXT NOT NULL,"
        "group_name TEXT NOT NULL,"
        "course INTEGER NOT NULL);"
        
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

static int count_callback(void *data, int argc, char **argv, char **azColName) {
    *(int*)data = atoi(argv[0]);
    return 0;
}

bool populate_sample_data(sqlite3 *db) {
    char *err_msg = 0;
    
    // Проверяем, есть ли уже данные
    const char *check_sql = "SELECT COUNT(*) FROM Students;";
    int count = 0;
    
    // Define a separate callback function instead of using a lambda
    
    int rc = sqlite3_exec(db, check_sql, count_callback, &count, &err_msg);
    
    if(rc != SQLITE_OK) {
        fprintf(stderr, "Ошибка SQL: %s\n", err_msg);
        sqlite3_free(err_msg);
        return false;
    }
    
    if(count > 0) return true; // Данные уже есть
    
    // Добавляем тестовых студентов
    const char *insert_sql =
        "INSERT INTO Students (last_name, first_name, middle_name, birth_year, gender, group_name, course) VALUES "
        "('Иванов', 'Иван', 'Иванович', 1999, 'M', 'ГР1', 1),"
        "('Петров', 'Петр', 'Петрович', 2000, 'M', 'ГР1', 1),"
        "('Сидоров', 'Сидор', 'Сидорович', 1998, 'M', 'ГР2', 1),"
        "('Кузнецов', 'Алексей', 'Николаевич', 2001, 'M', 'ГР2', 1),"
        "('Смирнов', 'Дмитрий', 'Олегович', 2000, 'M', 'ГР3', 1),"
        "('Иванова', 'Мария', 'Сергеевна', 2001, 'F', 'ГР1', 1),"
        "('Петрова', 'Анна', 'Владимировна', 1999, 'F', 'ГР1', 1),"
        "('Сидорова', 'Елена', 'Александровна', 2000, 'F', 'ГР2', 1),"
        "('Кузнецова', 'Ольга', 'Игоревна', 1998, 'F', 'ГР2', 1),"
        "('Смирнова', 'Татьяна', 'Дмитриевна', 2001, 'F', 'ГР3', 1),"
        "('Васильев', 'Василий', 'Васильевич', 1997, 'M', 'ГР4', 2),"
        "('Николаев', 'Николай', 'Николаевич', 1998, 'M', 'ГР4', 2),"
        "('Алексеев', 'Алексей', 'Алексеевич', 1999, 'M', 'ГР5', 2),"
        "('Дмитриев', 'Дмитрий', 'Дмитриевич', 1996, 'M', 'ГР5', 2),"
        "('Олегов', 'Олег', 'Олегович', 2000, 'M', 'ГР6', 2),"
        "('Васильева', 'Василиса', 'Васильевна', 1999, 'F', 'ГР4', 2),"
        "('Николаева', 'Наталья', 'Николаевна', 1998, 'F', 'ГР4', 2),"
        "('Алексеева', 'Александра', 'Алексеевна', 1997, 'F', 'ГР5', 2),"
        "('Дмитриева', 'Дарья', 'Дмитриевна', 1996, 'F', 'ГР5', 2),"
        "('Олегова', 'Ольга', 'Олеговна', 2000, 'F', 'ГР6', 2);"
        
        "INSERT INTO Grades (student_id, subject_id, grade) VALUES "
        "(1, 1, 5), (1, 2, 4), (1, 3, 5),"
        "(2, 1, 4), (2, 2, 4), (2, 3, 3),"
        "(3, 1, 5), (3, 2, 5), (3, 4, 5),"
        "(4, 1, 3), (4, 2, 3), (4, 5, 4),"
        "(5, 1, 4), (5, 3, 5), (5, 4, 4),"
        "(6, 1, 5), (6, 2, 5), (6, 5, 5),"
        "(7, 1, 4), (7, 3, 4), (7, 4, 5),"
        "(8, 1, 3), (8, 2, 4), (8, 5, 3),"
        "(9, 1, 5), (9, 3, 5), (9, 4, 5),"
        "(10, 1, 4), (10, 2, 4), (10, 3, 4),"
        "(11, 1, 5), (11, 2, 5), (11, 4, 5),"
        "(12, 1, 4), (12, 3, 4), (12, 5, 5),"
        "(13, 1, 3), (13, 2, 4), (13, 3, 3),"
        "(14, 1, 5), (14, 4, 5), (14, 5, 5),"
        "(15, 1, 4), (15, 2, 3), (15, 3, 4),"
        "(16, 1, 5), (16, 2, 5), (16, 4, 5),"
        "(17, 1, 4), (17, 3, 5), (17, 5, 4),"
        "(18, 1, 5), (18, 2, 5), (18, 3, 5),"
        "(19, 1, 3), (19, 4, 4), (19, 5, 3),"
        "(20, 1, 4), (20, 2, 4), (20, 3, 5);";

    rc = sqlite3_exec(db, insert_sql, 0, 0, &err_msg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "Ошибка SQL: %s\n", err_msg);
        sqlite3_free(err_msg);
        return false;
    }
    return true;
}

void print_oldest_students(sqlite3 *db) {
    const char *sql =
        "SELECT s.course, s.last_name, s.first_name, s.middle_name, s.birth_year, s.group_name "
        "FROM Students s "
        "WHERE s.course IN (1, 2) AND s.birth_year = ("
        "   SELECT MIN(birth_year) FROM Students WHERE course = s.course"
        ") "
        "ORDER BY s.course;";

    char *err_msg = 0;
    
    printf("\n=== Самые старшие студенты на 1 и 2 курсе ===\n");
    printf("%-10s%-20s%-20s%-20s%-15s%-10s\n",
           "Курс", "Фамилия", "Имя", "Отчество", "Год рождения", "Группа");
    
    int rc = sqlite3_exec(db, sql, print_row, 0, &err_msg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "Ошибка SQL: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
    printf("===============================================\n");
}

void print_top_students_by_course(sqlite3 *db) {
    const char *sql =
        "WITH CourseSums AS ("
        "   SELECT s.course, s.id, s.last_name, s.first_name, s.middle_name, SUM(g.grade) as total "
        "   FROM Students s "
        "   JOIN Grades g ON s.id = g.student_id "
        "   GROUP BY s.id"
        "), "
        "MaxScores AS ("
        "   SELECT course, id, last_name, first_name, middle_name, total "
        "   FROM CourseSums cs1 "
        "   WHERE total = (SELECT MAX(total) FROM CourseSums cs2 WHERE cs2.course = cs1.course)"
        "), "
        "CourseTotals AS ("
        "   SELECT course, SUM(total) as course_total "
        "   FROM CourseSums "
        "   GROUP BY course"
        ") "
        "SELECT m.course, m.last_name, m.first_name, m.middle_name, m.total, c.course_total "
        "FROM MaxScores m "
        "JOIN CourseTotals c ON m.course = c.course "
        "ORDER BY m.course;";

    char *err_msg = 0;
    
    printf("\n=== Лучшие студенты по курсам и сумма баллов ===\n");
    printf("%-10s%-20s%-20s%-20s%-15s%-15s\n",
           "Курс", "Фамилия", "Имя", "Отчество", "Сумма баллов", "Сумма по курсу");
    
    int rc = sqlite3_exec(db, sql, print_row, 0, &err_msg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "Ошибка SQL: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
    printf("===================================================\n");
}

void print_avg_grades_by_group_and_course(sqlite3 *db) {
    const char *sql =
        "SELECT s.course, s.group_name, ROUND(AVG(g.grade), 2) as avg_grade "
        "FROM Students s "
        "JOIN Grades g ON s.id = g.student_id "
        "GROUP BY s.course, s.group_name "
        "ORDER BY s.course, s.group_name;";

    char *err_msg = 0;
    
    printf("\n=== Средний балл по группам и курсам ===\n");
    printf("%-10s%-15s%-15s\n", "Курс", "Группа", "Средний балл");
    
    int rc = sqlite3_exec(db, sql, print_row, 0, &err_msg);
    if(rc != SQLITE_OK) {
        fprintf(stderr, "Ошибка SQL: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
    printf("======================================\n");
}
