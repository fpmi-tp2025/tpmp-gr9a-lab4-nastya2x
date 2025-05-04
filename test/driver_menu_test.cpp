#include <gtest/gtest.h>
#include <sqlite3.h>
#include "../includes/driver_menu.h"
#include "../includes/db.h"

TEST(DriverMenuTest, ListDriverOrdersSuccess) {
    sqlite3* db = nullptr;
    const char* filename = "test.db";

    bool openResult = openDatabase(&db, filename);
    ASSERT_TRUE(openResult);

    // Mock or simulate user input for dates
    std::string start_date = "2023-01-01";
    std::string end_date = "2023-12-31";

    // Assume the test database contains orders for the given driver_id and dates
    EXPECT_NO_THROW(listDriverOrders(db, 1));

    closeDatabase(db);
}
TEST(DriverMenuTest, ListDriverOrdersNoOrders) {
    sqlite3* db = nullptr;
    const char* filename = "test.db";

    bool openResult = openDatabase(&db, filename);
    ASSERT_TRUE(openResult);

    // Test with a driver_id that has no orders in the database for the given date range
    EXPECT_NO_THROW(listDriverOrders(db, 999));

    closeDatabase(db);
}
TEST(DriverMenuTest, ListDriverOrdersDatabaseError) {
    sqlite3* db = nullptr;
    const char* filename = "test.db";

    bool openResult = openDatabase(&db, filename);
    ASSERT_TRUE(openResult);

    // Simulate a database error (e.g., invalid SQL statement)
    std::string start_date = "2023-01-01";
    std::string end_date = "2023-12-31";

    EXPECT_THROW(listDriverOrders(db, 1), std::runtime_error);

    closeDatabase(db);
}
