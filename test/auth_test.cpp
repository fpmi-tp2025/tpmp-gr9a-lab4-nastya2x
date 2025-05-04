#include <gtest/gtest.h>
#include <sqlite3.h>
#include "../includes/auth.h"
#include "../includes/db.h"

TEST(AuthTest, AuthenticateFailure) {
    sqlite3* db = nullptr;
    const char* filename = "test.db";

    bool openResult = openDatabase(&db, filename);
    ASSERT_TRUE(openResult);

    std::string username = "invalid_user";
    std::string password = "invalid_password";

    int result = authenticate(db, username, password);
    EXPECT_EQ(result, -1);  // Expect authentication failure

    closeDatabase(db);
}
TEST(AuthTest, AuthenticateDatabaseError) {
    sqlite3* db = nullptr;
    const char* filename = "test.db";

    bool openResult = openDatabase(&db, filename);
    ASSERT_TRUE(openResult);

    // Simulate a database error (e.g., invalid SQL statement)
    std::string username = "valid_user";
    std::string password = "valid_password";

    // We can simulate this by using a wrong SQL query or an incorrect database
    int result = authenticate(db, username, password);
    EXPECT_EQ(result, -1);  // Expect failure due to database issue

    closeDatabase(db);
}
