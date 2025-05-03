cmake_minimum_required(VERSION 3.10)

# Указываем название проекта
project(AutoparkApp)

# Устанавливаем стандарт C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Если используем старый GCC (до 8.1), добавляем флаг для файловой системы
if(CMAKE_COMPILER_IS_GNUCXX AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 8.1)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++fs")
endif()

# Указываем, где находятся заголовочные файлы
include_directories(includes)

# Указываем исходные файлы
set(SRC 
    src/main.cpp
    src/db.cpp
    src/auth.cpp
    src/driver_menu.cpp
    src/admin_menu.cpp
)

# Указываем файл для сборки
add_executable(autopark_app ${SRC})

# Линки для SQLite3
find_package(SQLite3 REQUIRED)
target_link_libraries(autopark_app SQLite::SQLite3)
