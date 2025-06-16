#include <stdio.h>
#include <stdlib.h>
#include "database.h"
#include "menu.h"

int main() {
    sqlite3 *db;
    
    if(!init_db(&db)) {
        return 1;
    }
    
    if(!create_tables(db)) {
        sqlite3_close(db);
        return 1;
    }
    
    run_menu(db);
    
    close_db(db);
    return 0;
}
