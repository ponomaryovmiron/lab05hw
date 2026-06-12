#ifndef BANKING_TRANSACTION_H
#define BANKING_TRANSACTION_H

#include "Account.h"

namespace banking {

class Transaction {
public:
    Transaction();

    void set_fee(int fee);
    int fee() const;

    bool Make(Account& from, Account& to, int sum);

private:
    int fee_;
};

}

#endif
