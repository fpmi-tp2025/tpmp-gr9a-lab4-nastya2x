#ifndef ADMIN_MENU_H
#define ADMIN_MENU_H

#include <sqlite3.h>

void showAdminMenu(sqlite3* db);

void addNewDriver(sqlite3* db);

void addNewCar(sqlite3* db);

void addNewOrder(sqlite3* db);

void updateDriver(sqlite3* db);

void deleteDriver(sqlite3* db);

void showAdminStats(sqlite3* db);

#endif