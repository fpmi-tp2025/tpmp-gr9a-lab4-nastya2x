# Минимальная версия CMake
cmake_minimum_required(VERSION 3.10)

# Название проекта
project(AutoParkApp)

# Установим стандарт C++
set(CMAKE_CXX_STANDARD 17)

# Указываем папки с исходными файлами
include_directories(includes)
include_directories(src)

# Указываем путь к заголовочным файлам Google Test
find_package(GTest REQUIRED)

# Указываем путь к библиотеке SQLite3
find_package(SQLite3 REQUIRED)

# Добавляем тесты
enable_testing()

# Создаем основной исполнимый файл
add_executable(autopark_app
    src/db.cpp
    src/admin_menu.cpp
    src/auth.cpp
    src/driver_menu.cpp
    src/main.cpp
)

# Линкуем приложение с SQLite3
target_link_libraries(autopark_app sqlite3)

# Добавляем тесты
add_executable(tests
    test/db_test.cpp
    test/admin_menu_test.cpp
    test/auth_test.cpp
    test/driver_menu_test.cpp
    src/db.cpp  # Включаем исходники в тесты
    src/admin_menu.cpp
    src/auth.cpp
    src/driver_menu.cpp
)

# Линкуем тесты с Google Test и SQLite3
target_link_libraries(tests GTest::GTest GTest::Main sqlite3)

# Добавляем тесты в CMake
add_test(NAME AllTests COMMAND tests)

# Можно указать, чтобы CMake автоматически запускал тесты
include(GoogleTest)
gtest_discover_tests(tests)
