# Схема базы данных

![Database Schema](https://github.com/user-attachments/assets/db599a2c-6278-440f-aa96-47278bd0ada1)

# Структура базы данных «Автопарк»

## Таблица `Cars`

Хранит информацию об автомобилях автопарка.

| Поле | Тип | Описание |
|------|-----|----------|
| `car_number` | TEXT (PK) | Номер автомобиля |
| `brand` | TEXT | Марка автомобиля |
| `initial_mileage` | INTEGER | Начальный пробег |
| `capacity_kg` | INTEGER | Грузоподъёмность (в кг), > 0 |

---

## Таблица `Drivers`

Хранит информацию о водителях.

| Поле | Тип | Описание |
|------|-----|----------|
| `driver_id` | INTEGER (PK) | Идентификатор водителя |
| `full_name` | TEXT | ФИО водителя |
| `category` | TEXT | Водительская категория |
| `experience_years` | INTEGER | Стаж (в годах), ≥ 1 |
| `address` | TEXT | Адрес |
| `birth_year` | INTEGER | Год рождения |
| `username` | TEXT | Уникальный логин |
| `password` | TEXT | Пароль |

---

## Таблица `Orders`

Хранит информацию о заказах на перевозку.

| Поле | Тип | Описание |
|------|-----|----------|
| `order_id` | INTEGER (PK, AUTOINCREMENT) | Идентификатор заказа |
| `order_date` | DATE | Дата оформления |
| `driver_id` | INTEGER (FK) | Водитель |
| `car_number` | TEXT (FK) | Автомобиль |
| `distance_km` | REAL | Расстояние (в км), ≥ 0 |
| `cargo_weight_kg` | INTEGER | Вес груза (в кг), > 0 |
| `cost` | REAL | Стоимость перевозки, ≥ 0 |

---

## Представление `DriverEarnings`

Представление рассчитывает заработок каждого водителя (20% от стоимости всех заказов):

```sql
CREATE VIEW DriverEarnings AS
SELECT 
    d.driver_id,
    d.full_name,
    SUM(o.cost * 0.2) AS total_earnings
FROM Orders o
JOIN Drivers d ON o.driver_id = d.driver_id
GROUP BY d.driver_id, d.full_name;
```

## Триггер check_cargo_weight

Запрещает добавление заказа, если масса груза превышает грузоподъёмность автомобиля:

```
CREATE TRIGGER check_cargo_weight
BEFORE INSERT ON Orders
FOR EACH ROW
BEGIN
    SELECT 
    CASE 
        WHEN (SELECT capacity_kg FROM Cars WHERE car_number = NEW.car_number) < NEW.cargo_weight_kg 
        THEN RAISE(ABORT, 'Масса груза превышает грузоподъёмность машины')
    END;
END;
```

---

## SQL-файл
Исходный SQL-файл со всеми таблицами, представлением и триггером можно найти здесь: [database.sql](https://github.com/fpmi-tp2025/tpmp-gr9a-lab4-nastya2x/blob/main/data/database.sql)