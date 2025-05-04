#include <gtest/gtest.h>
#include <sqlite3.h>
#include "../includes/admin_menu.h"
#include "../includes/db.h"

TEST(AdminMenuTest, ShowAdminStatsSuccess) {
    sqlite3* db = nullptr;
    const char* filename = "test.db";

    bool openResult = openDatabase(&db, filename);
    ASSERT_TRUE(openResult);

    // Assuming we have a test database with some data in it
    EXPECT_NO_THROW(showAdminStats(db));

    closeDatabase(db);
}

TEST(AdminMenuTest, ShowAdminStatsNoData) {
    sqlite3* db = nullptr;
    const char* filename = "test.db";

    bool openResult = openDatabase(&db, filename);
    ASSERT_TRUE(openResult);

    // Assuming the test.db has no relevant data
    EXPECT_NO_THROW(showAdminStats(db));

    closeDatabase(db);
}
