#include "../includes/admin_menu.h"
#include <iostream>
#include <sqlite3.h>
#include <string>

void showAdminStats(sqlite3* db) {
    std::string query = "SELECT d.driver_id, d.full_name, COUNT(o.order_id), SUM(o.cargo_weight_kg), SUM(o.cost * 0.2) "
                        "FROM Drivers d LEFT JOIN Orders o ON d.driver_id = o.driver_id "
                        "GROUP BY d.driver_id;";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Ошибка выполнения запроса: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    std::cout << "\nСтатистика по водителям:\n";
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int driver_id = sqlite3_column_int(stmt, 0);
        const char* full_name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        int num_orders = sqlite3_column_int(stmt, 2);
        int total_weight = sqlite3_column_int(stmt, 3);
        double total_earnings = sqlite3_column_double(stmt, 4);

        std::cout << "Водитель: " << full_name << " (ID: " << driver_id << ")\n";
        std::cout << "Количество поездок: " << num_orders << "\n";
        std::cout << "Общая масса грузов: " << total_weight << " кг\n";
        std::cout << "Заработано: " << total_earnings << " руб.\n";
    }

    sqlite3_finalize(stmt);
}

void addNewDriver(sqlite3* db) {
    std::string full_name, category, username, password, address;
    int experience_years, birth_year;

    std::cout << "Введите полное имя водителя: ";
    std::cin.ignore(); // Очищаем буфер
    std::getline(std::cin, full_name);

    std::cout << "Введите категорию водителя: ";
    std::cin >> category;

    std::cout << "Введите опыт работы (в годах): ";
    std::cin >> experience_years;

    std::cout << "Введите год рождения водителя: ";
    std::cin >> birth_year;

    std::cout << "Введите адрес водителя: ";
    std::cin.ignore();
    std::getline(std::cin, address);

    std::cout << "Введите логин: ";
    std::cin >> username;

    std::cout << "Введите пароль: ";
    std::cin >> password;

    std::string query = "INSERT INTO Drivers (full_name, category, experience_years, birth_year, address, username, password) "
                        "VALUES ('" + full_name + "', '" + category + "', " + std::to_string(experience_years) + ", "
                        + std::to_string(birth_year) + ", '" + address + "', '" + username + "', '" + password + "');";

    char* errMsg;
    if (sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Ошибка добавления водителя: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Водитель успешно добавлен!\n";
    }
}

void addNewCar(sqlite3* db) {
    std::string car_number, brand;
    int initial_mileage, capacity_kg;

    std::cout << "Введите номер машины: ";
    std::cin >> car_number;

    std::cout << "Введите марку машины: ";
    std::cin >> brand;

    std::cout << "Введите пробег машины на момент приобретения: ";
    std::cin >> initial_mileage;

    std::cout << "Введите грузоподъемность машины (кг): ";
    std::cin >> capacity_kg;

    std::string query = "INSERT INTO Cars (car_number, brand, initial_mileage, capacity_kg) "
                        "VALUES ('" + car_number + "', '" + brand + "', " + std::to_string(initial_mileage) + ", "
                        + std::to_string(capacity_kg) + ");";

    char* errMsg;
    if (sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Ошибка добавления машины: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Машина успешно добавлена!\n";
    }
}

void addNewOrder(sqlite3* db) {
    int driver_id;
    std::string car_number, order_date;
    double distance_km, cost;
    int cargo_weight_kg;

    std::cout << "Введите ID водителя: ";
    std::cin >> driver_id;

    std::cout << "Введите номер машины: ";
    std::cin >> car_number;

    std::cout << "Введите дату заказа (YYYY-MM-DD): ";
    std::cin >> order_date;

    std::cout << "Введите расстояние (км): ";
    std::cin >> distance_km;

    std::cout << "Введите массу груза (кг): ";
    std::cin >> cargo_weight_kg;

    std::cout << "Введите стоимость перевозки: ";
    std::cin >> cost;

    std::string query = "INSERT INTO Orders (order_date, driver_id, car_number, distance_km, cargo_weight_kg, cost) "
                        "VALUES ('" + order_date + "', " + std::to_string(driver_id) + ", '" + car_number + "', "
                        + std::to_string(distance_km) + ", " + std::to_string(cargo_weight_kg) + ", " + std::to_string(cost) + ");";

    char* errMsg;
    if (sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Ошибка добавления заказа: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Заказ успешно добавлен!\n";
    }
}

void updateDriver(sqlite3* db) {
    int driver_id;
    std::string new_full_name, new_category;
    int new_experience_years;

    std::cout << "Введите ID водителя для обновления: ";
    std::cin >> driver_id;

    std::cout << "Введите новое полное имя: ";
    std::cin.ignore();
    std::getline(std::cin, new_full_name);

    std::cout << "Введите новую категорию водителя: ";
    std::cin >> new_category;

    std::cout << "Введите новый опыт работы (в годах): ";
    std::cin >> new_experience_years;

    std::string query = "UPDATE Drivers SET full_name = '" + new_full_name + "', category = '" + new_category + "', "
                        "experience_years = " + std::to_string(new_experience_years) + " WHERE driver_id = " + std::to_string(driver_id) + ";";

    char* errMsg;
    if (sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Ошибка обновления водителя: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Водитель успешно обновлен!\n";
    }
}

void deleteDriver(sqlite3* db) {
    int driver_id;

    std::cout << "Введите ID водителя для удаления: ";
    std::cin >> driver_id;

    std::string query = "DELETE FROM Drivers WHERE driver_id = " + std::to_string(driver_id) + ";";

    char* errMsg;
    if (sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Ошибка удаления водителя: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Водитель успешно удален!\n";
    }
}

void showAdminMenu(sqlite3* db) {
    int choice;
    do {
        std::cout << "\n=== Меню администратора ===\n";
        std::cout << "1. Статистика по водителям\n";
        std::cout << "2. Добавить нового водителя\n";
        std::cout << "3. Добавить новую машину\n";
        std::cout << "4. Добавить новый заказ\n";
        std::cout << "5. Обновить информацию о водителе\n";
        std::cout << "6. Удалить водителя\n";
        std::cout << "7. Выйти\n";
        std::cout << "Ваш выбор: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                showAdminStats(db);
                break;
            case 2:
                addNewDriver(db);
                break;
            case 3:
                addNewCar(db);
                break;
            case 4:
                addNewOrder(db);
                break;
            case 5:
                updateDriver(db);
                break;
            case 6:
                deleteDriver(db);
                break;
            case 7:
                std::cout << "Выход...\n";
                break;
            default:
                std::cout << "Неверный выбор.\n";
        }
    } while (choice != 7);
}
