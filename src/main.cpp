#include <iostream>
#include <string>
#include "../includes/db.h"
#include "../includes/auth.h"
#include "../includes/driver_menu.h"
#include "../includes/admin_menu.h"

// Главное меню
void showMainMenu() {
    std::cout << "\nДобро пожаловать в автопарк!\n";
    std::cout << "1. Войти как водитель\n";
    std::cout << "2. Войти как админ\n";
    std::cout << "3. Выход\n";
}

// Главная логика приложения
int main() {
    sqlite3* db;
    if (!openDatabase(&db, "data/autopark.sqlite")) return 1;

    int choice;
    do {
        showMainMenu();
        std::cout << "Ваш выбор: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                // Вход как водитель
                std::string username, password;
                std::cout << "=== Вход как водитель ===\n";
                std::cout << "Логин: ";
                std::cin >> username;
                std::cout << "Пароль: ";
                std::cin >> password;

                int driver_id = authenticate(db, username, password);
                if (driver_id == -1) {
                    std::cerr << "Ошибка авторизации.\n";
                    break;
                }

                // Меню водителя
                showDriverMenu(db, driver_id);
                break;
            }

            case 2: {
                // Вход как админ
                std::cout << "=== Меню администратора ===\n";
                showAdminMenu(db);
                break;
            }

            case 3:
                std::cout << "До свидания!\n";
                break;

            default:
                std::cout << "Неверный выбор.\n";
        }
    } while (choice != 3);

    closeDatabase(db);
    return 0;
}
