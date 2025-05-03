#include "../includes/db.h"
#include <iostream>

bool openDatabase(sqlite3** db, const char* filename) {
    int rc = sqlite3_open(filename, db);
    if (rc) {
        std::cerr << "Не удалось открыть базу данных: " << sqlite3_errmsg(*db) << std::endl;
        return false;
    }
    return true;
}

void closeDatabase(sqlite3* db) {
    sqlite3_close(db);
}
