#include <Account.h>

#include <gtest/gtest.h>
#include <stdexcept>

using namespace banking;

TEST(Account, ConstructorAndGetters)
{
    Account account(1, 100);

    EXPECT_EQ(account.id(), 1);
    EXPECT_EQ(account.GetBalance(), 100);
    EXPECT_FALSE(account.IsLocked());
}

TEST(Account, ChangeBalanceOnlyWhenLocked)
{
    Account account(2, 200);

    EXPECT_THROW(account.ChangeBalance(50), std::runtime_error);

    account.Lock();
    EXPECT_TRUE(account.IsLocked());

    account.ChangeBalance(50);
    EXPECT_EQ(account.GetBalance(), 250);

    account.Unlock();
    EXPECT_FALSE(account.IsLocked());
}
