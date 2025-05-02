#ifndef AUTH_H
#define AUTH_H

#include <sqlite3.h>
#include <string>

int authenticate(sqlite3 *db, const std::string &username, const std::string &password);

#endif