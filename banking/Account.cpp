#include "Account.h"

#include <stdexcept>

namespace banking {

Account::Account(int id, int balance)
    : id_(id), balance_(balance), locked_(false)
{
}

int Account::id() const
{
    return id_;
}

int Account::GetBalance() const
{
    return balance_;
}

void Account::ChangeBalance(int diff)
{
    if (!locked_) {
        throw std::runtime_error("account is not locked");
    }

    balance_ += diff;
}

void Account::Lock()
{
    locked_ = true;
}

void Account::Unlock()
{
    locked_ = false;
}

bool Account::IsLocked() const
{
    return locked_;
}

}
