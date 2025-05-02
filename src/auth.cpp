#include "../includes/auth.h"
#include <sqlite3.h>
#include <string>
#include <iostream>

int authenticate(sqlite3* db, const std::string& username, const std::string& password) {
    sqlite3_stmt* stmt;
    const char* sql = "SELECT driver_id FROM Drivers WHERE username = ? AND password = ?";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Ошибка подготовки запроса авторизации\n";
        return -1;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    int driver_id = -1;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        driver_id = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);
    return driver_id;
}
