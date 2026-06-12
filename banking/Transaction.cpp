#include "Transaction.h"

#include <stdexcept>

namespace banking {

Transaction::Transaction()
    : fee_(1)
{
}

void Transaction::set_fee(int fee)
{
    fee_ = fee;
}

int Transaction::fee() const
{
    return fee_;
}

bool Transaction::Make(Account& from, Account& to, int sum)
{
    if (from.id() == to.id()) {
        throw std::invalid_argument("same account");
    }

    if (sum <= 0) {
        return false;
    }

    int total = sum + fee_;

    from.Lock();
    to.Lock();

    if (from.GetBalance() < total) {
        from.Unlock();
        to.Unlock();
        return false;
    }

    from.ChangeBalance(-total);
    to.ChangeBalance(sum);

    from.Unlock();
    to.Unlock();

    return true;
}

}
