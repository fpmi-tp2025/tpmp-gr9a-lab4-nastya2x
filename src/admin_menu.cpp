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

