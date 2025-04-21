#ifndef DB_H
#define DB_H

#include <sqlite3.h>

bool openDatabase(sqlite3** db, const char* filename);
void closeDatabase(sqlite3* db);

#endif

