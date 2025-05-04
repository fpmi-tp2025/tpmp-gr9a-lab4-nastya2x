BEGIN TRANSACTION;
CREATE TABLE IF NOT EXISTS "Cars" (
	"car_number"	TEXT,
	"brand"	TEXT NOT NULL,
	"initial_mileage"	INTEGER NOT NULL,
	"capacity_kg"	INTEGER NOT NULL CHECK("capacity_kg" > 0),
	PRIMARY KEY("car_number")
);
CREATE TABLE IF NOT EXISTS "Drivers" (
	"driver_id"	INTEGER,
	"full_name"	TEXT NOT NULL,
	"category"	TEXT NOT NULL,
	"experience_years"	INTEGER NOT NULL CHECK("experience_years" >= 1),
	"address"	TEXT,
	"birth_year"	INTEGER NOT NULL,
	"username"	TEXT NOT NULL UNIQUE,
	"password"	TEXT NOT NULL,
	PRIMARY KEY("driver_id")
);
CREATE TABLE IF NOT EXISTS "Orders" (
	"order_id"	INTEGER,
	"order_date"	DATE NOT NULL,
	"driver_id"	INTEGER NOT NULL,
	"car_number"	TEXT NOT NULL,
	"distance_km"	REAL NOT NULL CHECK("distance_km" >= 0),
	"cargo_weight_kg"	INTEGER NOT NULL CHECK("cargo_weight_kg" > 0),
	"cost"	REAL NOT NULL CHECK("cost" >= 0),
	PRIMARY KEY("order_id" AUTOINCREMENT),
	FOREIGN KEY("car_number") REFERENCES "Cars"("car_number"),
	FOREIGN KEY("driver_id") REFERENCES "Drivers"("driver_id")
);
INSERT INTO "Cars" VALUES ('A001','Volvo',150000,1500),
 ('A002','Mercedes',200000,1800),
 ('A003','BMW',120000,1400),
 ('A004','Audi',100000,1600),
 ('A005','Toyota',90000,1200),
 ('A006','Hyundai',110000,1300),
 ('A007','Kia',130000,1500),
 ('A008','Ford',140000,1700),
 ('A009','Nissan',160000,2000),
 ('A010','Chevrolet',170000,1800);
INSERT INTO "Drivers" VALUES (1,'Иванов Иван Иванович','A',5,'Москва, ул. Ленина 1',1985,'ivanov','1234'),
 (2,'Петров Петр Петрович','B',3,'Москва, ул. Горького 5',1990,'petrov','5678'),
 (3,'Сидоров Сидор Сидорович','C',7,'Москва, ул. Пушкина 10',1980,'sidorov','qwerty'),
 (4,'Кузнецов Николай Николаевич','A',4,'Москва, ул. Тверская 15',1987,'kuznetsov','password'),
 (5,'Михайлов Михаил Михайлович','B',2,'Москва, ул. Арбат 3',1992,'mikhailov','pass123'),
 (6,'Ковалев Александр Александрович','A',6,'Москва, ул. Сухаревская 2',1983,'kovalev','mypass'),
 (7,'Лебедев Владимир Владимирович','C',8,'Москва, ул. Чистопрудный 4',1979,'lebedev','admin'),
 (8,'Новиков Артем Артемович','B',3,'Москва, ул. Варварка 8',1991,'novikov','qwerty123'),
 (9,'Голубев Сергей Сергеевич','A',9,'Москва, ул. Бауманская 12',1978,'golubev','secret'),
 (10,'Федоров Дмитрий Дмитриевич','B',1,'Москва, ул. Неглинная 6',1994,'fedorov','root');
INSERT INTO "Orders" VALUES (1,'2025-04-01',1,'A001',120.0,500,1000.0),
 (2,'2025-04-02',2,'A002',150.0,800,1500.0),
 (3,'2025-04-03',3,'A003',180.0,1000,1800.0),
 (4,'2025-04-04',4,'A004',200.0,400,1200.0),
 (5,'2025-04-05',5,'A005',250.0,700,1400.0),
 (6,'2025-04-06',6,'A006',300.0,600,1300.0),
 (7,'2025-04-07',7,'A007',100.0,300,1100.0),
 (8,'2025-04-08',8,'A008',110.0,500,1150.0),
 (9,'2025-04-09',9,'A009',130.0,900,1600.0),
 (10,'2025-04-10',10,'A010',160.0,800,1500.0);
CREATE VIEW DriverEarnings AS
SELECT 
    d.driver_id,
    d.full_name,
    SUM(o.cost * 0.2) AS total_earnings
FROM Orders o
JOIN Drivers d ON o.driver_id = d.driver_id
GROUP BY d.driver_id, d.full_name;
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
COMMIT;
