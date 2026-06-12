#include <Account.h>
#include <Transaction.h>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace banking;
using ::testing::Return;
using ::testing::InSequence;

class MockAccount : public Account {
public:
    MockAccount(int id, int balance)
        : Account(id, balance)
    {
    }

    MOCK_CONST_METHOD0(id, int());
    MOCK_CONST_METHOD0(GetBalance, int());
    MOCK_METHOD1(ChangeBalance, void(int));
    MOCK_METHOD0(Lock, void());
    MOCK_METHOD0(Unlock, void());
};

TEST(Transaction, FeeCanBeChanged)
{
    Transaction transaction;

    EXPECT_EQ(transaction.fee(), 1);

    transaction.set_fee(10);

    EXPECT_EQ(transaction.fee(), 10);
}

TEST(Transaction, SameAccountThrows)
{
    Transaction transaction;
    Account from(1, 100);
    Account to(1, 200);

    EXPECT_THROW(transaction.Make(from, to, 50), std::invalid_argument);
}

TEST(Transaction, NonPositiveSumReturnsFalse)
{
    Transaction transaction;
    Account from(1, 100);
    Account to(2, 200);

    EXPECT_FALSE(transaction.Make(from, to, 0));
}

TEST(Transaction, NotEnoughMoneyReturnsFalse)
{
    Transaction transaction;
    transaction.set_fee(10);

    MockAccount from(1, 50);
    MockAccount to(2, 0);

    EXPECT_CALL(from, id()).WillOnce(Return(1));
    EXPECT_CALL(to, id()).WillOnce(Return(2));

    {
        InSequence sequence;

        EXPECT_CALL(from, Lock());
        EXPECT_CALL(to, Lock());
        EXPECT_CALL(from, GetBalance()).WillOnce(Return(50));
        EXPECT_CALL(from, Unlock());
        EXPECT_CALL(to, Unlock());
    }

    EXPECT_FALSE(transaction.Make(from, to, 100));
}

TEST(Transaction, MakeSuccess)
{
    Transaction transaction;
    transaction.set_fee(10);

    MockAccount from(1, 200);
    MockAccount to(2, 0);

    EXPECT_CALL(from, id()).WillOnce(Return(1));
    EXPECT_CALL(to, id()).WillOnce(Return(2));

    {
        InSequence sequence;

        EXPECT_CALL(from, Lock());
        EXPECT_CALL(to, Lock());
        EXPECT_CALL(from, GetBalance()).WillOnce(Return(200));
        EXPECT_CALL(from, ChangeBalance(-110));
        EXPECT_CALL(to, ChangeBalance(100));
        EXPECT_CALL(from, Unlock());
        EXPECT_CALL(to, Unlock());
    }

    EXPECT_TRUE(transaction.Make(from, to, 100));
}
