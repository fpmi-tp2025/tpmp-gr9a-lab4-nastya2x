#include <gtest/gtest.h>
#include <sqlite3.h>
#include "../includes/db.h"

TEST(DBTest, OpenDatabaseSuccess) {
    sqlite3* db = nullptr;
    const char* filename = "test.db";

    bool result = openDatabase(&db, filename);
    EXPECT_TRUE(result);
    EXPECT_NE(db, nullptr);
    closeDatabase(db);
}

TEST(DBTest, CloseDatabase) {
    sqlite3* db = nullptr;
    const char* filename = "test.db";

    bool openResult = openDatabase(&db, filename);
    EXPECT_TRUE(openResult);

    // Check if the database is opened successfully before closing
    EXPECT_NE(db, nullptr);

    closeDatabase(db);
}
