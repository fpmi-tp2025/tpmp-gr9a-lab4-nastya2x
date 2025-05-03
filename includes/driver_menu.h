#ifndef DRIVER_MENU_H
#define DRIVER_MENU_H

#include <sqlite3.h>

void showDriverMenu(sqlite3* db, int driver_id);

void listDriverOrders(sqlite3* db, int driver_id);

void showDriverCar(sqlite3* db, int driver_id);

void driverEarningsForPeriod(sqlite3* db, int driver_id);

#endif
