#include "../includes/driver_menu.h"
#include <iostream>
#include <string>
#include <iomanip>

void listDriverOrders(sqlite3* db, int driver_id) {
    std::string start_date, end_date;
    std::cout << "Введите начальную дату (YYYY-MM-DD): ";
    std::cin >> start_date;
    std::cout << "Введите конечную дату (YYYY-MM-DD): ";
    std::cin >> end_date;

    const char* sql = R"(
        SELECT order_date, car_number, distance_km, cargo_weight_kg, cost
        FROM Orders
        WHERE driver_id = ? AND order_date BETWEEN ? AND ?
    )";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Ошибка подготовки запроса.\n";
        return;
    }

    sqlite3_bind_int(stmt, 1, driver_id);
    sqlite3_bind_text(stmt, 2, start_date.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, end_date.c_str(), -1, SQLITE_STATIC);

    std::cout << "\n=== Заказы ===\n";
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::cout << "Дата: " << sqlite3_column_text(stmt, 0)
                  << ", Машина: " << sqlite3_column_text(stmt, 1)
                  << ", Км: " << sqlite3_column_double(stmt, 2)
                  << ", Масса: " << sqlite3_column_int(stmt, 3)
                  << ", Стоимость: " << sqlite3_column_double(stmt, 4)
                  << std::endl;
    }

    sqlite3_finalize(stmt);
}

void showDriverCar(sqlite3* db, int driver_id) {
    const char* sql = R"(
        SELECT c.car_number, c.brand, c.initial_mileage, c.capacity_kg
        FROM Cars c
        JOIN Orders o ON o.car_number = c.car_number
        WHERE o.driver_id = ?
        LIMIT 1
    )";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Ошибка запроса машины.\n";
        return;
    }

    sqlite3_bind_int(stmt, 1, driver_id);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        std::cout << "\nВаша машина:\n";
        std::cout << "Номер: " << sqlite3_column_text(stmt, 0) << "\n";
        std::cout << "Марка: " << sqlite3_column_text(stmt, 1) << "\n";
        std::cout << "Пробег на момент покупки: " << sqlite3_column_int(stmt, 2) << "\n";
        std::cout << "Грузоподъемность: " << sqlite3_column_int(stmt, 3) << " кг\n";
    } else {
        std::cout << "Нет информации о машине.\n";
    }

    sqlite3_finalize(stmt);
}

void driverEarningsForPeriod(sqlite3* db, int driver_id) {
    std::string start_date, end_date;
    std::cout << "Введите начальную дату (YYYY-MM-DD): ";
    std::cin >> start_date;
    std::cout << "Введите конечную дату (YYYY-MM-DD): ";
    std::cin >> end_date;

    const char* sql = R"(
        SELECT SUM(cost * 0.2)
        FROM Orders
        WHERE driver_id = ? AND order_date BETWEEN ? AND ?
    )";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Ошибка запроса доходов.\n";
        return;
    }

    sqlite3_bind_int(stmt, 1, driver_id);
    sqlite3_bind_text(stmt, 2, start_date.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, end_date.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        std::cout << "Заработано за период: " << sqlite3_column_double(stmt, 0) << " у.е.\n";
    }

    sqlite3_finalize(stmt);
}

void showDriverMenu(sqlite3* db, int driver_id) {
    int choice;
    do {
        std::cout << "\n=== Меню водителя ===\n";
        std::cout << "1. Мои заказы за период\n";
        std::cout << "2. Моя машина\n";
        std::cout << "3. Доход за период\n";
        std::cout << "0. Выход\n";
        std::cout << "Выбор: ";
        std::cin >> choice;

        switch (choice) {
            case 1: listDriverOrders(db, driver_id); break;
            case 2: showDriverCar(db, driver_id); break;
            case 3: driverEarningsForPeriod(db, driver_id); break;
            case 0: std::cout << "Выход...\n"; break;
            default: std::cout << "Неверный выбор.\n";
        }
    } while (choice != 0);
}
